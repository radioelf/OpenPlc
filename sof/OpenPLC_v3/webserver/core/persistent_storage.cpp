//-----------------------------------------------------------------------------
// Copyright 2019 Thiago Alves
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
// This file is responsible for the persistent storage on the OpenPLC
// Thiago Alves, Jun 2019
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "ladder.h"

//-----------------------------------------------------------------------------
// Funcion principal para el hilo. Deberia crear un bufer para los datos de persistente
// comparelos con los datos reales y vuelva a escribir en el archivo persistente
// si los datos han cambiado
//-----------------------------------------------------------------------------
void startPstorage()
{
    unsigned char log_msg[1000];
	IEC_UINT persistentBuffer[BUFFER_SIZE];

    //Read initial buffers into persistent struct
	pthread_mutex_lock(&bufferLock); //lock mutex
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		if (int_memory[i] != NULL) persistentBuffer[i] = *int_memory[i];
	}
	pthread_mutex_unlock(&bufferLock); //unlock mutex
    
    //Perform the first write
    if (access("persistent.file", F_OK) == -1) 
    {
        sprintf(log_msg, "Crear archivo de almacenamiento persistente\n");
        log(log_msg);
    }
    
    FILE *ps = fopen("persistent.file", "w"); //if file already exists, it will be overwritten
    if (ps == NULL)
    {
        sprintf(log_msg, "Almacenamiento persistente: error al crear un archivo de memoria persistente!\n");
        log(log_msg);
        return 0;
    }

    if (fwrite(persistentBuffer, sizeof(IEC_INT), BUFFER_SIZE, ps) < BUFFER_SIZE)
    {
        sprintf(log_msg, "Almacenamiento persistente: error al escribir en el archivo de memoria persistente!\n");
        log(log_msg);
        return 0;
    }
    fclose(ps);
    
    //Run the main thread
	while (run_pstorage)
	{
        
        //Verify if persistent buffer is outdated
		bool bufferOutdated = false;
		pthread_mutex_lock(&bufferLock); //lock mutex
		for (int i = 0; i < BUFFER_SIZE; i++)
		{
			if (int_memory[i] != NULL)
			{
				if (persistentBuffer[i] != *int_memory[i])
				{
					persistentBuffer[i] = *int_memory[i];
					bufferOutdated = true;
				}
			}
		}
		pthread_mutex_unlock(&bufferLock); //unlock mutex

        //If buffer is outdated, write the changes back to the file
		if (bufferOutdated)
		{
			FILE *fd = fopen("persistent.file", "w"); //if file already exists, it will be overwritten
			if (fd == NULL)
			{
                sprintf(log_msg, "Persistent Storage: Error creating persistent memory file!\n");
                log(log_msg);
				return 0;
			}

			if (fwrite(persistentBuffer, sizeof(IEC_INT), BUFFER_SIZE, fd) < BUFFER_SIZE)
			{
                sprintf(log_msg, "Persistent Storage: Error writing to persistent memory file!\n");
                log(log_msg);
				return 0;
			}
			fclose(fd);
		}

		sleepms(pstorage_polling*1000);
	}
}

//-----------------------------------------------------------------------------
// Esta funcion lee el contenido de persistent.file en OpenPLC internal
// Se debe llamarse cuando OpenPLC se esta inicializando. Si el almacenamiento persistente
// esta deshabilitado, el archivo persistent.file no se encontrara 
//-----------------------------------------------------------------------------
int readPersistentStorage()
{
    unsigned char log_msg[1000];
	FILE *fd = fopen("persistent.file", "r");
	if (fd == NULL)
	{
        sprintf(log_msg, "Advertencia: archivo de almacenamiento persistente no encontrado\n");
        log(log_msg);
		return 0;
	}

	IEC_INT persistentBuffer[BUFFER_SIZE];

	if (fread(persistentBuffer, sizeof(IEC_INT), BUFFER_SIZE, fd) < BUFFER_SIZE)
	{
        sprintf(log_msg, "Almacenamiento persistente: error al intentar leer el archivo persistente.!\n");
        log(log_msg);
		return 0;
	}
	fclose(fd);
    
    sprintf(log_msg, "Almacenamiento persistente: lectura de archivos persistentes en buffers locales\n");
    log(log_msg);
    
	pthread_mutex_lock(&bufferLock); //lock mutex
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		if (int_memory[i] != NULL) *int_memory[i] = persistentBuffer[i];
	}
	pthread_mutex_unlock(&bufferLock); //unlock mutex
}
