//-----------------------------------------------------------------------------
// Copyright 2018 Thiago Alves
// This file is part of the OpenPLC Software Stack.
//
// OpenPLC is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// OpenPLC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with OpenPLC.  If not, see <http://www.gnu.org/licenses/>.
//------
//
// This is the main file for the OpenPLC. It contains the initialization
// procedures for the hardware, network and the main loop
// Thiago Alves, Jun 2018
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#include "iec_types.h"
#include "ladder.h"

#define OPLC_CYCLE          50000000

extern int opterr;
//extern int common_ticktime__;
IEC_BOOL __DEBUG;

IEC_LINT cycle_counter = 0;

unsigned long __tick = 0;
pthread_mutex_t bufferLock; //mutex for the internal buffers
pthread_mutex_t logLock; //mutex for the internal log
uint8_t run_openplc = 1; //Variable para controlar la ejecucion de OpenPLC Runtime
uint8_t botton_run = 0;  //Variable para controlar la selecion on/off atraves de boton
unsigned char log_buffer[1000000]; //buffer muy grande para almacenar todos los logs
int log_index = 0;
int log_counter = 0;

//-----------------------------------------------------------------------------
// Funcion auxiliar: hace que el subproceso en ejecucion duerma durante un periodo
// en milisegundos
//-----------------------------------------------------------------------------
void sleep_until(struct timespec *ts, int delay)
{
    ts->tv_nsec += delay;
    if(ts->tv_nsec >= 1000*1000*1000)
    {
        ts->tv_nsec -= 1000*1000*1000;
        ts->tv_sec++;
    }
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, ts,  NULL);
}

//-----------------------------------------------------------------------------
// Funcion auxiliar: Hace que el hilo en ejecución duerma durante un periodo
// en milisegundos
//-----------------------------------------------------------------------------
void sleepms(int milliseconds)
{
	struct timespec ts;
	ts.tv_sec = milliseconds / 1000;
	ts.tv_nsec = (milliseconds % 1000) * 1000000;
	nanosleep(&ts, NULL);
}

//-----------------------------------------------------------------------------
// Funcion auxiliar: Registra mensajes y los imprime en la consola
//-----------------------------------------------------------------------------
void log(unsigned char *logmsg)
{
	
    pthread_mutex_lock(&logLock); //lock mutex

    printf("%s", logmsg);

    for (int i = 0; logmsg[i] != '\0'; i++)
    {
        log_buffer[log_index] = logmsg[i];
        log_index++;
        log_buffer[log_index] = '\0';
    }
    
    log_counter++;
    if (log_counter >= 1000)
    {
        /*Store current log on a file*/
        log_counter = 0;
        log_index = 0;
    }
    pthread_mutex_unlock(&logLock); //unlock mutex
}

//-----------------------------------------------------------------------------
// Hilo interactivo del servidor. Crea el servidor para escuchar los comandos de localhost
//-----------------------------------------------------------------------------
void *interactiveServerThread(void *arg)
{
    startInteractiveServer(43628);
}

//-----------------------------------------------------------------------------
// Comprueba si el pin está presente en uno de los vectores ignorados
//-----------------------------------------------------------------------------
bool pinNotPresent(int *ignored_vector, int vector_size, int pinNumber)
{
    for (int i = 0; i < vector_size; i++)
    {
        if (ignored_vector[i] == pinNumber)
            return false;
    }
    
    return true;
}

//-----------------------------------------------------------------------------
// Deshabilitar todas las salidas
//-----------------------------------------------------------------------------
void disableOutputs()
{
    //Deshabilita salidas digitales
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (bool_output[i][j] != NULL) *bool_output[i][j] = 0;
        }
    }
    
    //Deshabilita byte outputs
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        if (byte_output[i] != NULL) *byte_output[i] = 0;
    }
    
    //Deshabilita salidas analogicas
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        if (int_output[i] != NULL) *int_output[i] = 0;
    }
}

//-----------------------------------------------------------------------------
// Funciones especiales
//-----------------------------------------------------------------------------
void handleSpecialFunctions()
{
    //current time [%ML1024]
    struct tm *current_time;
    time_t rawtime;
    
    tzset();
    time(&rawtime);
    current_time = localtime(&rawtime);
    
    rawtime = rawtime - timezone;
    if (current_time->tm_isdst > 0) rawtime = rawtime + 3600;
        
    if (special_functions[0] != NULL) *special_functions[0] = rawtime;
    
    //number of cycles [%ML1025]
    cycle_counter++;
    if (special_functions[1] != NULL) *special_functions[1] = cycle_counter;
    
    //comm error counter [%ML1026]
    /* Implemented in modbus_master.cpp */

    //insert other special functions below
}

int main(int argc,char **argv)
{
    unsigned char log_msg[1000];	
    time_t mytime = time(NULL);
    char * time_str = ctime(&mytime);
    if (time_str[strlen(time_str)-1] == '\n')
		time_str[strlen(time_str)-1] = ' -';
    sprintf(log_msg, "%s %s", time_str, "OpenPLC pasando a modo RUN...\n");
    log(log_msg);
    
    //======================================================
    //                 PLC INITIALIZATION
    //======================================================
    time(&start_time);
    pthread_t interactive_thread;
    pthread_create(&interactive_thread, NULL, interactiveServerThread, NULL);
    config_init__();
    glueVars();

    //======================================================
    //               MUTEX INITIALIZATION
    //======================================================
    if (pthread_mutex_init(&bufferLock, NULL) != 0)
    {
        printf("Fallo al iniciar Mutex\n");
        exit(1);
    }

    //======================================================
    //              HARDWARE INITIALIZATION
    //======================================================
    initializeHardware();
    initializeMB();
    initCustomLayer();
    updateBuffersIn();
    updateCustomIn();
    updateBuffersOut();
    updateCustomOut();
    if (botton_run)
    {
		sprintf(log_msg, "Pulsador RUN activo\n");
		run_openplc = 1;
	}
	else
	{
		sprintf(log_msg, "Pulsador RUN NO activo\n");
		run_openplc = 0;
	}
	log(log_msg);

    //======================================================
    //          PERSISTENT STORAGE INITIALIZATION
    //======================================================
    glueVars();
    mapUnusedIO();
    readPersistentStorage();
    //pthread_t persistentThread;
    //pthread_create(&persistentThread, NULL, persistentStorage, NULL);

#ifdef __linux__
    //======================================================
    //              REAL-TIME INITIALIZATION
    //======================================================
    // Set our thread to real time priority
    struct sched_param sp;
    sp.sched_priority = 30;
    printf("Setting main thread priority to RT\n");
    if(pthread_setschedparam(pthread_self(), SCHED_FIFO, &sp))
    {
        printf("WARNING: Failed to set main thread to real-time priority\n");
    }

    // Lock memory to ensure no swapping is done.
    printf("Locking main thread memory\n");
    if(mlockall(MCL_FUTURE|MCL_CURRENT))
    {
        printf("WARNING: Failed to lock memory\n");
    }
#endif

	//gets the starting point for the clock
	printf("Getting current time\n");
	struct timespec timer_start;
	clock_gettime(CLOCK_MONOTONIC, &timer_start);

	//======================================================
	//                    MAIN LOOP
	//======================================================
	while(run_openplc)
	{
		//make sure the buffer pointers are correct and
		//attached to the user variables
		glueVars();
        
		updateBuffersIn(); //read input image
		if (botton_run ==0) 
		{
			run_openplc =0;
			break;
		}
		pthread_mutex_lock(&bufferLock); //lock mutex
		updateCustomIn();
        updateBuffersIn_MB(); //update input image table with data from slave devices
        handleSpecialFunctions();
		config_run__(__tick++); // execute plc program logic
		updateCustomOut();
        updateBuffersOut_MB(); //update slave devices with data from the output image table
		pthread_mutex_unlock(&bufferLock); //unlock mutex

		updateBuffersOut(); //write output image
        
		updateTime();

		sleep_until(&timer_start, common_ticktime__);
	}
    
    //======================================================
	//             SHUTTING DOWN OPENPLC RUNTIME
	//======================================================
    pthread_join(interactive_thread, NULL);
    printf("Deshabilitamos salidas\n");
    disableOutputs();
    updateCustomOut();
    updateBuffersOut();
	finalizeHardware();
    printf("Apagamos modo RUN en OpenPLC...\n");
    exit(0);
}
