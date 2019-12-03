/*
  ModbusSerial.cpp - Source for Modbus Serial Library
  Copyright (C) 2014 André Sarmento Barbosa

  https://github.com/andresarmento/modbus-arduino

  Mod. Radioelf http://radioelf.blogspot.com.es/

  El protocolo Modbus indica que para una velocidad en baudios superior a 19200
  debe usar 750 us como tiempo de espera entre caracteres y 1,75 ms para un retraso
  entre tramas.
  P.ej. 9600 baudios en un paquete de 11 bits es 9600/11 = 872 caracteres por segundo
  En milisegundos, esto será 872 caracteres por 1000ms. Entonces, para 1 carácter,
  1000ms / 872 caracteres es 1.14583ms por carácter y, finalmente, Modbus establece
  que un carácter entre caracteres debe ser 1.5 veces más largo que un carácter.
  Por lo tanto, 1.5T = 1.14583ms * 1.5 = 1.71875ms. Un retraso de trama es 3.5T.
   Por lo tanto, la fórmula es T1.5 (us) = (1000ms * 1000 (us) * 1.5 * 11bits) / baudios
  1000ms * 1000 (us) * 1.5 * 11bits = 16500000 se puede calcular como una constante

  if (baud > 19200)
  _t15 = 750;
  else
  _t15 = 16500000/baud; // 1T * 1.5 = T1.5

   El protocolo  modbus también indica que entre trama tiene que tener un retraso
   de espera de 3,5 veces por caracteres entre paquetes, esto no es exactamente lo
   mismo que el frameDelay implementado en esta biblioteca pero se beneficia de ella.
   La variable frameDelay se usa principalmente para garantizar que el último carácter sea
   transmitido sin truncamiento. Se elige un valor de 2 caracteres que
   debería ser suficiente sin mantener la línea del bus a nivel alto por mucho tiempo.
*/
#include "ModbusSerial.h"

ModbusSerial::ModbusSerial() {

}

bool ModbusSerial::setSlaveId(byte slaveId) {
  _slaveId = slaveId;
  return true;
}

byte ModbusSerial::getSlaveId() {
  return _slaveId;
}

bool ModbusSerial::config(HardwareSerial* port, long baud, int txPin, int DataLedPin) {
  this->_port = port;
  this->_txPin = txPin;
  this->_DataLedPin = DataLedPin;

  (*port).begin(baud, SERIAL_8N1);
  pinMode(DataLedPin, OUTPUT);
  digitalWrite(DataLedPin, LOW);
  pinMode(txPin, OUTPUT);
  digitalWrite(txPin, LOW);

  delay(2000);

  if (baud > 19200) {
    _t15 = 750;
    _t35 = 1750;
  } else {
    _t15 = 15000000 / baud; // 1T * 1.5 = T1.5
    _t35 = 35000000 / baud; // 1T * 3.5 = T3.5
  }
  return true;
}

bool ModbusSerial::receive(byte* frame) {

  byte address = frame[0];                //primer byte de la trama = address
  //Los últimos dos bytes = crc
  u_int crc = ((frame[_len - 2] << 8) | frame[_len - 1]);
  if (address != 0xFF && address != this->getSlaveId()) {//Comprobación esclavo
    return false;
  }
  //Comprobación CRC
  if (crc != this->calcCrc(_frame[0], _frame + 1, _len - 3)) {
    return false;
  }
  //PDU comienza después del primer byte
  //tamanyo de la trama PDU = framesize - address(1) - crc(2) (en total hay 3 bytes que NO pertenece a la trama PDU)
  this->receivePDU(frame + 1);
  //Sin respuesta del Broadcasts
  if (frame[0] == 0xFF) _reply = MB_REPLY_OFF; // ID =0xFF MB_REPLY_OFF->1
  digitalWrite(this->_DataLedPin, !digitalRead(this->_DataLedPin));
  return true;
}

bool ModbusSerial::send(byte* frame) {
  byte i;

  digitalWrite(this->_txPin, HIGH);
  delay(1);

  for (i = 0 ; i < _len ; i++) {
    (*_port).write(frame[i]);
  }

  (*_port).flush();
  delayMicroseconds(_t35);

  digitalWrite(this->_txPin, LOW);

}

bool ModbusSerial::sendPDU(byte* pduframe) {

  digitalWrite(this->_txPin, HIGH);
  delay(1);
  //Envío slaveId
  (*_port).write(_slaveId);

  //Envío PDU
  byte i;
  for (i = 0 ; i < _len ; i++) {
    (*_port).write(pduframe[i]);
  }
  //Envió CRC
  word crc = calcCrc(_slaveId, _frame, _len);
  (*_port).write(crc >> 8);
  (*_port).write(crc & 0xFF);

  (*_port).flush();
  delayMicroseconds(_t35);

  digitalWrite(this->_txPin, LOW);

}

void ModbusSerial::task() {
  _len = 0;

  while ((*_port).available() > _len)  {
    _len = (*_port).available();
    delayMicroseconds(_t15);
  }

  if (_len == 0) return;

  _frame = (byte*) malloc(_len);
  for (uint8_t i = 0 ; i < _len ; i++) _frame[i] = (*_port).read();

  if (this->receive(_frame)) {
    if (_reply == MB_REPLY_NORMAL) this->sendPDU(_frame); // RX tipo 3
    else if (_reply == MB_REPLY_ECHO) this->send(_frame); // RX tipo 2
  }
  free(_frame);
  _len = 0;
}

word ModbusSerial::calcCrc(byte address, byte* pduFrame, byte pduLen) {
  byte CRCHi = 0xFF, CRCLo = 0x0FF, Index;

  Index = CRCHi ^ address;
  CRCHi = CRCLo ^ _auchCRCHi[Index];
  CRCLo = _auchCRCLo[Index];

  while (pduLen--) {
    Index = CRCHi ^ *pduFrame++;
    CRCHi = CRCLo ^ _auchCRCHi[Index];
    CRCLo = _auchCRCLo[Index];
  }

  return (CRCHi << 8) | CRCLo;
}
