/*
    Modbus.cpp - Source for Modbus Base Library
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

*/
#include "Modbus.h"

Modbus::Modbus() {
  _regs_head = 0;
  _regs_last = 0;
}

TRegister* Modbus::searchRegister(word address) {
  TRegister *reg = _regs_head;
  //Finaliza si no hay registro configurado
  if (reg == 0) return (0);
  //escanear la lista vinculada hasta el final de la lista o hasta que se encuentre el registro.
  //return el puntero.
  do {
    if (reg->address == address) return (reg);
    reg = reg->next;
  } while (reg);
  return (0);
}

void Modbus::addReg(word address, word value) {
  TRegister *newreg;

  newreg = (TRegister *) malloc(sizeof(TRegister));
  newreg->address = address;
  newreg->value		= value;
  newreg->next		= 0;

  if (_regs_head == 0) {
    _regs_head = newreg;
    _regs_last = _regs_head;
  } else {
    //Asigna el siguiente puntero del último registro a newreg.
    _regs_last->next = newreg;
    //luego haga que temp sea el último registro de la lista.
    _regs_last = newreg;
  }
}

bool Modbus::Reg(word address, word value) {
  TRegister *reg;
  //buscar la dirección de registro
  reg = this->searchRegister(address);
  //si se encuentra, se asigna el valor de registro al nuevo valor
  if (reg) {
    reg->value = value;
    return true;
  } else
    return false;
}

word Modbus::Reg(word address) {
  TRegister *reg;
  reg = this->searchRegister(address);
  if (reg)
    return (reg->value);
  else
    return (0);
}

void Modbus::addHreg(word offset, word value) {
  this->addReg(offset + 40001, value);
}

bool Modbus::Hreg(word offset, word value) {
  return Reg(offset + 40001, value);
}

word Modbus::Hreg(word offset) {
  return Reg(offset + 40001);
}

void Modbus::addCoil(word offset, bool value) {
  this->addReg(offset + 1, value ? 0xFF00 : 0x0000);
}

void Modbus::addIsts(word offset, bool value) {
  this->addReg(offset + 10001, value ? 0xFF00 : 0x0000);
}

void Modbus::addIreg(word offset, word value) {
  this->addReg(offset + 30001, value);
}

bool Modbus::Coil(word offset, bool value) {
  return Reg(offset + 1, value ? 0xFF00 : 0x0000);
}

bool Modbus::Ists(word offset, bool value) {
  return Reg(offset + 10001, value ? 0xFF00 : 0x0000);
}

bool Modbus::Ireg(word offset, word value) {
  return Reg(offset + 30001, value);
}

bool Modbus::Coil(word offset) {
  if (Reg(offset + 1) == 0xFF00) {
    return true;
  } else return false;
}

bool Modbus::Ists(word offset) {
  if (Reg(offset + 10001) == 0xFF00) {
    return true;
  } else return false;
}

word Modbus::Ireg(word offset) {
  return Reg(offset + 30001);
}

void Modbus::receivePDU(byte* frame) {
  byte fcode  = frame[0];
  word field1 = (word)frame[1] << 8 | (word)frame[2];	// pasamos dos bytes a word
  word field2 = (word)frame[3] << 8 | (word)frame[4]; // pasamos dos bytes a word

  switch (fcode) {
    case MB_FC_WRITE_REG:                         	  // Función 6 ->Asignar a registro único
      //campo1 = reg, campo2 = valor
      this->writeSingleRegister(field1, field2);
      break;

    case MB_FC_READ_REGS:							                // Función 3 -> Lectura de bloque de registros del tipo holding
      //campo1 = startreg, campo2 = numregs
      this->readRegisters(field1, field2);
      break;

    case MB_FC_WRITE_REGS:							              // Función 16 -> Escribir bloque de registros contiguos
      //campo1 = startreg, campo2 = status
      this->writeMultipleRegisters(frame, field1, field2, frame[5]);
      break;

#ifndef USE_HOLDING_REGISTERS_ONLY
    case MB_FC_READ_COILS:							              // Función 1 -> Leer estado bobinas (Output)
      //campo1 = startreg, campo2 = numregs
      this->readCoils(field1, field2);
      break;

    case MB_FC_READ_INPUT_STAT:						            // Función 2 -> Leer estado de las entradas (Entradas discretas)
      //campo1 = startreg, campo2 = numregs
      this->readInputStatus(field1, field2);
      break;

    case MB_FC_READ_INPUT_REGS:						            // Función 4 -> Lectura de registros de entradas
      //campo1 = startreg, campo2 = numregs
      this->readInputRegisters(field1, field2);
      break;

    case MB_FC_WRITE_COIL:							              // Función 5 -> Escribir salida bobina
      //campo1 = reg, campo2 = status
      this->writeSingleCoil(field1, field2);
      break;

    case MB_FC_WRITE_COILS:							              // Función 15 -> Escritura múltiple a bobinas (Outputs)
      //campo1 = startreg, campo2 = numoutputs
      this->writeMultipleCoils(frame, field1, field2, frame[5]);
      break;

#endif
    default:
      this->exceptionResponse(fcode, MB_EX_ILLEGAL_FUNCTION);// Código de Función no admitido->1
  }
}

void Modbus::exceptionResponse(byte fcode, byte excode) {
  //Limpiar el búfer
  free(_frame);
  _len = 2;
  _frame = (byte *) malloc(_len);
  _frame[0] = fcode + 0x80;
  _frame[1] = excode;

  _reply = MB_REPLY_NORMAL;
}

void Modbus::readRegisters(word startreg, word numregs) {
  //Comprobar valor (numregs)
  if (numregs < 0x0001 || numregs > 0x007D) {
    this->exceptionResponse(MB_FC_READ_REGS, MB_EX_ILLEGAL_VALUE);
    return;
  }

  //Comprobar dirección
  if (!this->searchRegister(startreg + 40001)) {
    this->exceptionResponse(MB_FC_READ_REGS, MB_EX_ILLEGAL_ADDRESS);
    return;
  }
  //Limpiar búfer trama
  free(_frame);
  _len = 0;

  //calcular la longitud del mensaje de respuesta de consulta para
  //cada registro consultado incluyendo 2 bytes
  _len = 2 + numregs * 2;

  _frame = (byte *) malloc(_len);
  if (!_frame) {
    this->exceptionResponse(MB_FC_READ_REGS, MB_EX_SLAVE_FAILURE);
    return;
  }

  _frame[0] = MB_FC_READ_REGS;
  _frame[1] = _len - 2;                             //byte contador

  word val;
  word i = 0;
  while (numregs--) {
    //recuperar el valor del banco de registro para el registro actual
    val = this->Hreg(startreg + i);
    //escribir el byte alto del valor del registro
    _frame[2 + i * 2]  = val >> 8;
    //escribir el byte bajo del valor del registroe
    _frame[3 + i * 2] = val & 0xFF;
    i++;
  }

  _reply = MB_REPLY_NORMAL;
}

void Modbus::writeSingleRegister(word reg, word value) {
  //No es necesario verificar el valor ilegal (EX_ILLEGAL_VALUE) - porque usamos word (0x0000 - 0x0FFFF)
  //Verificar dirección y ejecutar (reg existe?)
  if (!this->Hreg(reg, value)) {
    this->exceptionResponse(MB_FC_WRITE_REG, MB_EX_ILLEGAL_ADDRESS);
    return;
  }

  //Verificar fallos
  if (this->Hreg(reg) != value) {
    this->exceptionResponse(MB_FC_WRITE_REG, MB_EX_SLAVE_FAILURE);
    return;
  }

  _reply = MB_REPLY_ECHO;
}

void Modbus::writeMultipleRegisters(byte* frame, word startreg, word numoutputs, byte bytecount) {
  //Comprobar valores
  if (numoutputs < 0x0001 || numoutputs > 0x007B || bytecount != 2 * numoutputs) {
    this->exceptionResponse(MB_FC_WRITE_REGS, MB_EX_ILLEGAL_VALUE);
    return;
  }

  //Comprobar dirección (startreg...startreg + numregs)
  for (int k = 0; k < numoutputs; k++) {
    if (!this->searchRegister(startreg + 40001 + k)) {
      this->exceptionResponse(MB_FC_WRITE_REGS, MB_EX_ILLEGAL_ADDRESS);
      return;
    }
  }

  //Limpiar el búfer _frame
  free(_frame);
  _len = 5;
  _frame = (byte *) malloc(_len);
  if (!_frame) {
    this->exceptionResponse(MB_FC_WRITE_REGS, MB_EX_SLAVE_FAILURE);
    return;
  }

  _frame[0] = MB_FC_WRITE_REGS;
  _frame[1] = startreg >> 8;
  _frame[2] = startreg & 0x00FF;
  _frame[3] = numoutputs >> 8;
  _frame[4] = numoutputs & 0x00FF;

  word val;
  word i = 0;
  while (numoutputs--) {
    val = (word)frame[6 + i * 2] << 8 | (word)frame[7 + i * 2];
    this->Hreg(startreg + i, val);
    i++;
  }

  _reply = MB_REPLY_NORMAL;
}

#ifndef USE_HOLDING_REGISTERS_ONLY
void Modbus::readCoils(word startreg, word numregs) {
  //Comprobar valores (numregs)
  if (numregs < 0x0001 || numregs > 0x07D0) {
    this->exceptionResponse(MB_FC_READ_COILS, MB_EX_ILLEGAL_VALUE);
    return;
  }

  // Comprobar dirección
  // Marque solo startreg. Es esto correcto?
  // Cuando verifico todos los registros en el rango, recibo errores en ScadaBR
  // Creo que ScadaBR solicita más de uno en la solicitud individual
  // cuando tienes mas de un punto de datos configurado desde el mismo tipo.
  if (!this->searchRegister(startreg + 1)) {
    this->exceptionResponse(MB_FC_READ_COILS, MB_EX_ILLEGAL_ADDRESS);
    return;
  }

  //Limpiamos búfer trama
  free(_frame);
  _len = 0;

  // Obtener la longitud del mensaje = tipo de Función, y recuento de bytes
  // para cada grupo de 8 registros, la longitud del mensaje aumenta en 1
  _len = 2 + numregs / 8;
  if (numregs % 8) _len++;                                //Incrementar en 1 a la longitud del mensaje

  _frame = (byte *) malloc(_len);
  if (!_frame) {
    this->exceptionResponse(MB_FC_READ_COILS, MB_EX_SLAVE_FAILURE);
    return;
  }

  _frame[0] = MB_FC_READ_COILS;
  _frame[1] = _len - 2;                                     //byte contador (_len - código de Función y recuento de bytes)

  byte bitn = 0;
  word totregs = numregs;
  word i;
  while (numregs--) {
    i = (totregs - numregs) / 8;
    if (this->Coil(startreg))
      bitSet(_frame[2 + i], bitn);
    else
      bitClear(_frame[2 + i], bitn);
    //incrementar el bit del indice
    bitn++;
    if (bitn == 8) bitn = 0;
    //incrementar el registro
    startreg++;
  }

  _reply = MB_REPLY_NORMAL;
}

void Modbus::readInputStatus(word startreg, word numregs) {
  //Comprobar el registro (numregs)
  if (numregs < 0x0001 || numregs > 0x07D0) {
    this->exceptionResponse(MB_FC_READ_INPUT_STAT, MB_EX_ILLEGAL_VALUE);
    return;
  }

  //Comprobar la dirección
  if (!this->searchRegister(startreg + 10001)) {
    this->exceptionResponse(MB_FC_READ_COILS, MB_EX_ILLEGAL_ADDRESS);
    return;
  }

  //Borrar trama búfer
  free(_frame);
  _len = 0;

  // Obtener la longitud del mensaje = tipo de Función, y recuento de bytes
  // para cada grupo de 8 registros, la longitud del mensaje aumenta en 1
  _len = 2 + numregs / 8;
  if (numregs % 8) _len++;                          //Incrementar en 1 a la longitud del mensaje
  _frame = (byte *) malloc(_len);
  if (!_frame) {
    this->exceptionResponse(MB_FC_READ_INPUT_STAT, MB_EX_SLAVE_FAILURE);
    return;
  }

  _frame[0] = MB_FC_READ_INPUT_STAT;
  _frame[1] = _len - 2;

  byte bitn = 0;
  word totregs = numregs;
  word i;
  while (numregs--) {
    i = (totregs - numregs) / 8;
    if (this->Ists(startreg))
      bitSet(_frame[2 + i], bitn);
    else
      bitClear(_frame[2 + i], bitn);
    //incrementar el bit del indice
    bitn++;
    if (bitn == 8) bitn = 0;
    //incrementar el registr
    startreg++;
  }

  _reply = MB_REPLY_NORMAL;
}

void Modbus::readInputRegisters(word startreg, word numregs) {
  //Comprobar valor (numregs)
  if (numregs < 0x0001 || numregs > 0x007D) {
    this->exceptionResponse(MB_FC_READ_INPUT_REGS, MB_EX_ILLEGAL_VALUE);
    return;
  }

  //Comprobar dirección
  if (!this->searchRegister(startreg + 30001)) {
    this->exceptionResponse(MB_FC_READ_COILS, MB_EX_ILLEGAL_ADDRESS);
    return;
  }

  //Limpiar el búfer trama
  free(_frame);
  _len = 0;

  // calcular la longitud del mensaje de la respuesta de consulta
  // para cada registro consultado agregando 2 bytes
  _len = 2 + numregs * 2;

  _frame = (byte *) malloc(_len);
  if (!_frame) {
    this->exceptionResponse(MB_FC_READ_INPUT_REGS, MB_EX_SLAVE_FAILURE);
    return;
  }

  _frame[0] = MB_FC_READ_INPUT_REGS;
  _frame[1] = _len - 2;
  word val;
  word i = 0;
  while (numregs--) {
    //recuperar el valor del banco de registro para el registro actual
    val = this->Ireg(startreg + i);
    //escriba el byte alto del valor del registro
    _frame[2 + i * 2]  = val >> 8;
    //escriba el byte bajo del valor del registro
    _frame[3 + i * 2] = val & 0xFF;
    i++;
  }

  _reply = MB_REPLY_NORMAL;
}

void Modbus::writeSingleCoil(word reg, word status) {
  //Comprobar valor (status)
  if (status != 0xFF00 && status != 0x0000) {
    this->exceptionResponse(MB_FC_WRITE_COIL, MB_EX_ILLEGAL_VALUE);
    return;
  }

  //Comprobar dirección y ejecutar (reg existe?)
  if (!this->Coil(reg, (bool)status)) {
    this->exceptionResponse(MB_FC_WRITE_COIL, MB_EX_ILLEGAL_ADDRESS);
    return;
  }

  //Comprobar dirección (startreg ... startreg + numregs)
  if (this->Coil(reg) != (bool)status) {
    this->exceptionResponse(MB_FC_WRITE_COIL, MB_EX_SLAVE_FAILURE);
    return;
  }
  _reply = MB_REPLY_ECHO;
}

void Modbus::writeMultipleCoils(byte* frame, word startreg, word numoutputs, byte bytecount) {
  //Comprobar valor
  word bytecount_calc = numoutputs / 8;
  if (numoutputs % 8) bytecount_calc++;
  if (numoutputs < 0x0001 || numoutputs > 0x07B0 || bytecount != bytecount_calc) {
    this->exceptionResponse(MB_FC_WRITE_COILS, MB_EX_ILLEGAL_VALUE);
    return;
  }

  //Comprobar dirección (startreg ... startreg + numregs)
  for (int k = 0; k < numoutputs; k++) {
    if (!this->searchRegister(startreg + 1 + k)) {
      this->exceptionResponse(MB_FC_WRITE_COILS, MB_EX_ILLEGAL_ADDRESS);
      return;
    }
  }

  //Limpiar el búfer trama
  free(_frame);
  _len = 5;
  _frame = (byte *) malloc(_len);
  if (!_frame) {
    this->exceptionResponse(MB_FC_WRITE_COILS, MB_EX_SLAVE_FAILURE);
    return;
  }

  _frame[0] = MB_FC_WRITE_COILS;
  _frame[1] = startreg >> 8;
  _frame[2] = startreg & 0x00FF;
  _frame[3] = numoutputs >> 8;
  _frame[4] = numoutputs & 0x00FF;

  byte bitn = 0;
  word totoutputs = numoutputs;
  word i;
  while (numoutputs--) {
    i = (totoutputs - numoutputs) / 8;
    this->Coil(startreg, bitRead(frame[6 + i], bitn));
    //incrementar el índice de bits
    bitn++;
    if (bitn == 8) bitn = 0;
    //incrementar el registro
    startreg++;
  }

  _reply = MB_REPLY_NORMAL;
}
#endif
