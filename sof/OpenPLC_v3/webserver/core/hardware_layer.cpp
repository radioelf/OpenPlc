//-----------------------------------------------------------------------------
// Copyright 2015 Thiago Alves
//
// Based on the LDmicro software by Jonathan Westhues
// This file is part of the OpenPLC Software Stack.
// http://cq.cx/ladder.pl
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
// This file is the hardware layer for the OpenPLC. If you change the platform
// where it is running, you may only need to change this file. All the I/O
// related stuff is here. 
//
// MOd. Radioelf 2019 para Raspberry Zero
// Básicamente proporciona funciones para leer y escribir.
// a los buffers internos de OpenPLC para actualizar el estado de E/S.
// Radioelf 2019
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>
//#include <wiringPiI2C.h>
#include <pthread.h>

#include "ladder.h"
#include "custom_layer.h"

#if !defined(ARRAY_SIZE)
    #define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif

#define MAX_INPUT 		8
#define MAX_OUTPUT 		8

int rtc = 0;
int eeprom = 0;

/*****************CONFIGURACION PINES ENTRADS Y SALISA********************
* Informacion de pines de la RaspberryPi es: http://pinout.xyz
* Los buffers de abajo funcionan como una mascara interna, para que
* OpenPLC puede acceder a cada pin secuencialmente
****************************************************************/
//inBufferPinMask: mascara de pines que se usaran como entradas por OpenPLC 
int inBufferPinMask[MAX_INPUT] = { 0, 2, 3, 21, 22, 23, 24, 25 };

//outBufferPinMask: mascara de pines que se usaran como salidas por OpenPLC 
int outBufferPinMask[MAX_OUTPUT] =	{ 1, 4, 5, 11, 26, 27, 28, 29 };

//pin entrada run/stop
int RUN = 31;

//pin salida indicacion led run/stop 
int LED = 30;
//-----------------------------------------------------------------------------
// Rutina es llamada por la rutina principal de OpenPLC cuando se esta inicializando.
// Los procedimientos de inicializaci0n del hardware deberian estar aqui.
//-----------------------------------------------------------------------------
void initializeHardware()
{
	wiringPiSetup();
	//piHiPri(99);                                                                          // prioridad
	
	//configuramos pines de entrada
	for (int i = 0; i < MAX_INPUT; i++)
	{
	    if (pinNotPresent(ignored_bool_inputs, ARRAY_SIZE(ignored_bool_inputs), i))
	    {
		    pinMode(inBufferPinMask[i], INPUT);
		    pullUpDnControl(inBufferPinMask[i], PUD_DOWN); 									// pull down habilitado (reposo a 0)
	    }
	}
	
	//configuramos pin pulsador Run como entrada
	pullUpDnControl(RUN, PUD_DOWN); 
	pinMode(RUN, INPUT);
	
	//configuramos pines de salida
	for (int i = 0; i < MAX_OUTPUT; i++)
	{
	    if (pinNotPresent(ignored_bool_outputs, ARRAY_SIZE(ignored_bool_outputs), i))
	    	pinMode(outBufferPinMask[i], OUTPUT);
	}
	
	//configuramos pin led como salida y senyal run apagada
	pinMode(LED, OUTPUT);
	digitalWrite (LED, false);
	
}

//-----------------------------------------------------------------------------
// Esta rutina es llamada por la rutina principal de OpenPLC cuando se esta finalizando.
//-----------------------------------------------------------------------------
void finalizeHardware()
{
	digitalWrite (LED, false);
	for (int i = 0; i < MAX_OUTPUT; i++)
	{
	  	digitalWrite (outBufferPinMask[i], false);
	}
	
}

//-----------------------------------------------------------------------------
// Esta funcion es llamada por el OpenPLC en un bucle. Los buffers internos deben
// actualizarse para mostrar el estado real de los pines de entrada. El semaforo buffer_lock
// debe usarse para proteger el acceso a los buffers en un entorno de subprocesos.
//-----------------------------------------------------------------------------
void updateBuffersIn()
{
	pthread_mutex_lock(&bufferLock); 		//semaforo bloqueado

	//ENTRADAS
	for (int i = 0; i < MAX_INPUT; i++)
	{
	    if (pinNotPresent(ignored_bool_inputs, ARRAY_SIZE(ignored_bool_inputs), i))
    		if (bool_input[i/8][i%8] != NULL) *bool_input[i/8][i%8] = digitalRead(inBufferPinMask[i]);
	}	

	botton_run = digitalRead(RUN);  	// obtenemos el estado de la entrada del pulsador run/stop

	pthread_mutex_unlock(&bufferLock); 	//semaforo desbloqueado
}

//-----------------------------------------------------------------------------
// Esta funcion es llamada por el OpenPLC en un bucle. Los buffers internos deben
// actualizarse para mostrar el estado real de los pines de salida. El mutex buffer_lock
// debe usarse para proteger el acceso a los buffers en un entorno de subprocesos.
//-----------------------------------------------------------------------------
void updateBuffersOut()
{
	pthread_mutex_lock(&bufferLock); //semaforo bloqueado

	//SALIDAS
	for (int i = 0; i < MAX_OUTPUT; i++)
	{
	    if (pinNotPresent(ignored_bool_outputs, ARRAY_SIZE(ignored_bool_outputs), i))
    		if (bool_output[i/8][i%8] != NULL) digitalWrite(outBufferPinMask[i], *bool_output[i/8][i%8]);
	}
	
	digitalWrite (LED, run_openplc);
	
	pthread_mutex_unlock(&bufferLock); //semaforo desbloqueado
}
