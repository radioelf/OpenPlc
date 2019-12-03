/* 
    Copyright (C) 2019  Radioelf  http://radioelf.blogspot.com.es/

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef EEPROM_H
#define EEPROM_H

#include <EEPROM.h>

union double_Byte {
  double    datoF;
  uint8_t  datoB[4];
} unionFB;

//********************************************************************************************
// Programación EEPROM
//--------------------------------------------------------------------------------------------
void EepromTx(uint8_t Mem) {
  switch (Mem)  {
    case 0:
      EEPROM.update(1, ID);
      break;
    case 1:
      unionFB.datoF = factor_V;
      EEPROM.update(2, unionFB.datoB[0]);
      EEPROM.update(3, unionFB.datoB[1]);
      EEPROM.update(4, unionFB.datoB[2]);
      EEPROM.update(5, unionFB.datoB[3]);
      break;
    case 2:
      unionFB.datoF = factor_C;
      EEPROM.update(6, unionFB.datoB[0]);
      EEPROM.update(7, unionFB.datoB[1]);
      EEPROM.update(8, unionFB.datoB[2]);
      EEPROM.update(9, unionFB.datoB[3]);
      break;
  }
}
//********************************************************************************************
// Leer EEPROM
//--------------------------------------------------------------------------------------------
void EepromRx(uint8_t Mem) {
  switch (Mem)  {
    case 0:
      ID =  EEPROM.read(1);
      break;
    case 1:
      unionFB.datoB[0] =  EEPROM.read(2);
      unionFB.datoB[1] =  EEPROM.read(3);
      unionFB.datoB[2] =  EEPROM.read(4);
      unionFB.datoB[3] =  EEPROM.read(5);
      factor_V = unionFB.datoF;
      break;
    case 2:
      unionFB.datoB[0] =  EEPROM.read(6);
      unionFB.datoB[1] =  EEPROM.read(7);
      unionFB.datoB[2] =  EEPROM.read(8);
      unionFB.datoB[3] =  EEPROM.read(9);
      factor_C = unionFB.datoF;
      break;
  }
}
#endif
