/*
    Modbus.h - Header for Modbus Base Library
    Copyright (C) 2014 André Sarmento Barbosa

    https://github.com/andresarmento/modbus-arduino

    Mod. Radioelf http://radioelf.blogspot.com.es/
    
   Tipo de registro        Usar como         Acceso       Métodos de la biblioteca
     Bobina            Salida digital    Leer/escribir       addCoil(), Coil()
  registro Holding     Salida analógica  Leer/escribir       addHreg(), Hreg()
  Estado de entrada    Entrada digital   Solo lectura        addIsts(), Ists()
  Registro de entrada  Entrada analógica Solo lectura        addIreg(), Ireg()
  
  El estado de entrada a veces se denomina entrada discreta.
  Registro Holding  o simplemente registro también se usa para almacenar valores en el esclavo.
  Ejemplos de uso: 
    una salida/bobina se puede utilizar para controlar una lámpara o LED. 
    Un registro Holding para almacenar un contador o valor de un servomotor. 
    El estado de una entrada se puede usar con un interruptor 
    Un registro de entrada con un sensor de temperatura.

Codigos de funciones
Código [01] Read Coils
Leer bobinas, salidas digitales, con este Código el maestro le solicita al esclavo información
del estado de sus salidas digitales o estado de la bobina dle rele. 

Código [02] Read Discrete Inputs
Leer entradas discretas, con este Código el maestro le solicita al esclavo información
del estado de sus entradas, no importa el tipo de entrada que tenga. 

Código [03] Read Holding Register
Leer registros de retención, el maestro le indica al esclavo por medio de este Código que 
entregue información de una posición de memoria, este tipo de memorias son de lectura y 
escritura. Es quizá la función más importante del Protocolo Modbus pues por medio de estos
registros se puede obtener información de todo lo que ocurre en el equipo, es solamente 
mover  la información que se quiere compartir al registro de retención.

Código [04] Read Input Register
Leer registros de entrada, el maestro le indica al esclavo por medio de este Código que 
entregue información de una posición de memoria, este tipo de memorias son de sólo lectura.
Muchos equipos los utilizan para compartir información de sus entradas analógicas en caso de que las posean.
*/
#include <Arduino.h>

#ifndef MODBUS_H
#define MODBUS_H

#define MAX_REGS     32
#define MAX_FRAME   128

typedef unsigned int u_int;

enum {
    MB_FC_READ_COILS       = 0x01,        // Leer estado bobinas (Output) 0xxxx
    MB_FC_READ_INPUT_STAT  = 0x02,        // Leer estado de las entradas (Entradas discretas) 1xxxx
    MB_FC_READ_REGS        = 0x03,        // Lectura de bloque de registros del tipo holding 4xxxx
    MB_FC_READ_INPUT_REGS  = 0x04,        // Lectura de registros de entradas 3xxxx
    MB_FC_WRITE_COIL       = 0x05,        // Escribir salida bobina 0xxxx
    MB_FC_WRITE_REG        = 0x06,        // Asignar a registro único 4xxxx
    MB_FC_WRITE_COILS      = 0x0F,        // Escritura múltiple a bobinas (Outputs) 0xxxx
    MB_FC_WRITE_REGS       = 0x10,        // Escribir bloque de registros contiguos 4xxxx
};

// Código de excepciones (error)
enum {
    MB_EX_ILLEGAL_FUNCTION = 0x01,        // Código de función no admitido
    MB_EX_ILLEGAL_ADDRESS  = 0x02,        // La dirección de salida no existe
    MB_EX_ILLEGAL_VALUE    = 0x03,        // Valor de salida fuera de rango
    MB_EX_SLAVE_FAILURE    = 0x04,        // El dispositivo esclavo no puede procesar la solicitud
};

// Códigos del tipo de respuesta
enum {
    MB_REPLY_OFF    = 0x01,
    MB_REPLY_ECHO   = 0x02,
    MB_REPLY_NORMAL = 0x03,
};

typedef struct TRegister {
    word address;
    word value;
    struct TRegister* next;
} TRegister;

class Modbus {
    private:
        TRegister *_regs_head;
        TRegister *_regs_last;

        void readRegisters(word startreg, word numregs);
        void writeSingleRegister(word reg, word value);
        void writeMultipleRegisters(byte* frame,word startreg, word numoutputs, byte bytecount);
        void exceptionResponse(byte fcode, byte excode);

        void readCoils(word startreg, word numregs);
        void readInputStatus(word startreg, word numregs);
        void readInputRegisters(word startreg, word numregs);
        void writeSingleCoil(word reg, word status);
        void writeMultipleCoils(byte* frame,word startreg, word numoutputs, byte bytecount);


        TRegister* searchRegister(word addr);

        void addReg(word address, word value = 0);
        bool Reg(word address, word value);
        word Reg(word address);

    protected:
        byte *_frame;
        byte  _len;
        byte  _reply;
        void receivePDU(byte* frame);

    public:
        Modbus();

        void addHreg(word offset, word value = 0);
        bool Hreg(word offset, word value);
        word Hreg(word offset);

        void addCoil(word offset, bool value = false);
        void addIsts(word offset, bool value = false);
        void addIreg(word offset, word value = 0);

        bool Coil(word offset, bool value);
        bool Ists(word offset, bool value);
        bool Ireg(word offset, word value);

        bool Coil(word offset);
        bool Ists(word offset);
        word Ireg(word offset);
};

#endif //MODBUS_H
