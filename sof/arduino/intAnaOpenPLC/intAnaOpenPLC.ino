/* Control entradas analógicas 0-10V/4-20mA gestión a traves de Modbus/RS485 para OpenPLC

  Function Code OpenPLC
  [02] Discrete Inputs (%IX100.0)
  [03] Holding Registers - Read (%IW100)
  [04] Input Registers (%IW100)
  [15] Coils (%QX100.0)
  [16] Holding Registers - Write (%QW100)

  TX OpenPLC ->01 04 00 00 00 08 F1 CC
  ID 1, función (04) de leer registros entradas, de la dirección de inicio 0, leer 08 registros (0-7), CRC F1 CC
  Modbus Read Analog Input Registers FC=04
  RX Modbus 6+3

  ID   Function Code  Data Address  Registers Requested  CRC
  1        04          00 00 00             08           F1CC
                      30001 + 1
  TX Modbus arduino->OpenPLC
  01 04 10 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 55 2c
  ID 1, función (04) de leer registros entradas, 16 bytes (cada registro esta compuesto de 2 bytes)

  ID   Function Code           2 bytes  Data            CRC
  1        04         00000000000000000000000000000000  552c

  8 analog intput (%IW100 - %IW107)

  La ganacia del la entrada ADC se pueden cambiar a través de la siguiente
  funciones, pero se tiene que tener cuidado de no superar nunca VDD + 0,3 V,
  La configuración de estos valores de forma incorrecta puede destruir el ADC!
  ADS1115 (15 bits + bit sing, de 0 a 32.767)

  ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 0.1875mV
  ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 0.125mV *
  ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 0.0625mV
  ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.03125mV
  ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.015625mV
  ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.0078125mV
  ------------------------------------------------------------------------------

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

#include <Adafruit_ADS1015.h>           // https://github.com/adafruit/Adafruit_ADS1X15

//ModBus puerto
#define BAUD        19200

#define pinTxRs485  2                   // pin RE/SDHN RS485
#define pinRUN      7                   // pin estado RUN/STOP
#define pinLedRun   11                  // pin indicación modo RUN/STOP
#define pinLedData  10                  // pin indicación modo datos RS485

uint8_t ID = 1;                         // ID para el bus RS485
uint8_t trama [128];                    // longitud de la trama RS485
double factor_V = 2.17675F;             // 0 V =0 10V =65535
double factor_C = 2.18116F;             // 4mA =0 20mA =65535
String inputString = "";

#include "Modbus.h"                     // https://github.com/andresarmento/modbus-arduino
#include "ModbusSerial.h"
#include "Eeprom.h"

// Modbus Objeto
ModbusSerial modbus;
// ADS1115 tensón - intensidad objeto
Adafruit_ADS1115 ads1115_V (0x48);
Adafruit_ADS1115 ads1115_C (0x49);

//******************************************************************
// Configuración
//******************************************************************
void setup() {
  pinMode(pinTxRs485, OUTPUT);
  pinMode(pinLedRun, OUTPUT);
  pinMode(pinRUN, INPUT);

  digitalWrite(pinTxRs485, LOW);
  digitalWrite(pinLedRun, LOW);

  inputString.reserve(8);

  //Config Modbus Serial (puerto, velocidad, pin rs485 tx)
  modbus.config(&Serial, BAUD, pinTxRs485, pinLedData);           // 115200

  delay (200);
  Wire.begin();
  // Ganacias para ADS de las salidas de voltaje +/- 4.096V  1 bit = 0.125mV
  ads1115_V.setGain(GAIN_ONE);
  ads1115_V.begin();
  // Ganacias para ADS de las salidas de corriente +/- 4.096V  1 bit = 0.125mV
  ads1115_C.setGain(GAIN_ONE);
  ads1115_C.begin();

  if (EEPROM.read(0) != 128) {
    EEPROM.update(0, 128);
    ID = 1;
    factor_V = 2.17675F;
    factor_C = 2.18116F;
    EepromTx(0);
    EepromTx(1);
    EepromTx(2);
  }
  EepromRx(0);                                                    // Leemos la configuración de la EEPROM
  EepromRx(1);
  EepromRx(2);

  modbus.setSlaveId(ID);
  for (uint8_t i = 0; i < 8; ++i) {
    modbus.addIreg(i);                                            // Registros modbus 0, 1, 2, 3, 4, 5, 6 y 7
    i < 4 ? modbus.Ireg((i), ReadADS1115_0_10(i)) : modbus.Ireg((i), ReadADS1115_4_20(i - 4));
    delay (20);
  }
}

bool STOP = true;
uint32_t ts = 0;
//******************************************************************
// Main
//******************************************************************
void loop() {
  while (!digitalRead (pinRUN)) {                                 // OpenPLC en RUN?
    Stop_Config();                                                // NO, menú configuración
    uint8_t Cont = 0;
    do {
      delay (20);
    } while (!digitalRead (pinRUN) && Cont++ < 100);              // Espera...
  }
  if (STOP == true) {
    digitalWrite(pinTxRs485, LOW);
    digitalWrite(pinLedRun, HIGH);
    STOP = false;
  }
  do {
    modbus.task();
    if ((millis () - ts) >= 200){
      // Obtenemos el estado de las entradas analógicas 0-10V y 4-20mA
      modbus.Ireg((0), ReadADS1115_0_10(0));                    // Pasamos el valor leido al registro Iref 0
      modbus.Ireg((1), ReadADS1115_0_10(1));                    // Pasamos el valor leido al registro Iref 1
      modbus.Ireg((2), ReadADS1115_0_10(2));                    // Pasamos el valor leido al registro Iref 2
      modbus.Ireg((3), ReadADS1115_0_10(3));                    // Pasamos el valor leido al registro Iref 3
      modbus.Ireg((4), ReadADS1115_4_20(0));                    // Pasamos el valor leido al registro Iref 4
      modbus.Ireg((5), ReadADS1115_4_20(1));                    // Pasamos el valor leido al registro Iref 5
      modbus.Ireg((6), ReadADS1115_4_20(2));                    // Pasamos el valor leido al registro Iref 6
      modbus.Ireg((7), ReadADS1115_4_20(3));                    // Pasamos el valor leido al registro Iref 7
      ts = millis();
    }
  } while (digitalRead (pinRUN));
}

//******************************************************************
// Leemos valor analógico del ADS de tensión y calculamos valor para OpenPLC
//******************************************************************
uint16_t ReadADS1115_0_10(byte channel) {
  int16_t x = ads1115_V.readADC_SingleEnded(channel);
  if (x < 5) return uint16_t(0);
  if (x > 30107) x = 30107;
  return uint16_t (x * factor_V);
}

//******************************************************************
// Leemos valor analógico del ADS de corriente y calculamos valor para OpenPLC
//******************************************************************
uint16_t ReadADS1115_4_20(byte channel) {
  int16_t x = ads1115_C.readADC_SingleEnded(channel);
  if (x < 6120) return uint16_t (0);//4mA->6120, 20ma->30046
  //map(x, 6120, 30046, 0, 30046);
  return uint16_t(x * factor_C);
}

//******************************************************************
// Menú configuración
//******************************************************************
void Stop_Config() {
  uint16_t Cont = 0;
  digitalWrite(pinLedRun, LOW);
  digitalWrite(pinTxRs485, HIGH);                                   // NECESARIO a 0 para poder programar el arduino desde USB
  digitalWrite(pinLedData, LOW);
  if (!STOP) {
    STOP = true;
    Serial.println('\n');
    Serial.println(F("-- ON Program USB --"));
    Serial.println(F("Board configuration:"));
    Serial.print(F("ID. "));
    Serial.println(ID, DEC);
    Serial.print(F("Current factor: "));
    Serial.println(factor_C, 6);
    Serial.print(F("Voltage factor: "));
    Serial.println(factor_V, 6);
    Serial.println(F("---------------------------"));
  }
  while (Serial.available()) {
    Serial.read();                                                  // Clear buffer
  }

  Serial.println(F("--Config. Board Input Analog Current/Voltage--"));
  Serial.println(F("  1-ID RS485"));
  Serial.println(F("  2-Current Calibration"));
  Serial.println(F("  3-Voltage Calibration"));
  Serial.println(F("  4-DEFAULT"));
  Serial.println(F("  r-Read"));
  Serial.println(F("  x-EXIT"));

  while (!Serial.available()) {
    delay (10);
    if (digitalRead (pinRUN)) return;
    if (++Cont % 50 == 0) {
      Serial.print(F("."));
      if (Cont > 850) {
        Serial.println('\n');
        return;
      }
    }
  }
  Cont = 0;
  uint8_t option = Serial.read();
  while (Serial.available())  {
    Serial.read();                                                // Clear buffer
  }
  Serial.println();
  if (option == '4') {
    Serial.println(F("Value default and RESET!"));
    EEPROM.update(0, 0);
    delay (1000);
    asm("jmp 0x0000");
  }
  if (Serial.read() == 'x') return;
  if (option > 48 && option < 52) {
    uint8_t character = 7;
    if (option == 49) {
      Serial.print(F("The ID is: "));
      Serial.println(ID, DEC);
      character = 1;
    } else if (option == 50) {
      Serial.print(F("The current factor is: "));
      Serial.println(factor_C, 5);
    } else if (option == 51) {
      Serial.print(F("The Voltage factor is: "));
      Serial.println(factor_V, 5);

    }
    Serial.print(F("New value (characters number "));
    Serial.print (character);
    Serial.println (F(") "));
    while (Serial.available() == 0) {
      delay (10);
      if (++Cont == 1000) return;                               // esperamos 10 segundos...
    }
    if (Serial.available() != character) {
      Serial.println(F("NOT valid!!"));
      return;
    }
    for (uint8_t x = 0; x != character; x++) {
      char inChar = (char)Serial.read();
      if (character == 1 && inChar == 'x') return;
      inputString += inChar;
    }
    Serial.println (inputString);
    if (option == '1') {
      ID = inputString.toInt();
      Serial.print(F("ID to: "));
      Serial.println(ID, DEC);
      Serial.print(F("-E- to save in EEPROM"));
    } else if (option == '2') {
      factor_C = inputString.toFloat();
      Serial.print(F("Current factor to: "));
      Serial.println(factor_C, 5);
      Serial.print(F("-E- to save in EEPROM"));
    } else if (option == '3') {
      factor_V = inputString.toFloat();
      Serial.print(F("Voltage factor to: "));
      Serial.println(factor_V, 5);
      Serial.println(F("-E- to save in EEPROM"));
    }
    inputString = "";                                           // limpiamos  String
    while (!Serial.available()) {
      delay (10);
      if (++Cont == 1000) return;                               // esperamos 10 segundos...
    }
    if (Serial.read() == 'x') return;
    if (Serial.read() == 'E') {
      EepromTx(0);
      EepromTx(1);
      EepromTx(2);
      Serial.println(F("Save in EEPROM"));
    }
  } else {
    if (option != 'r') return;                                 // RX serial NO "r"
    Serial.println("");
    Serial.print(F("Input 1 Voltage: "));
    Cont = ads1115_V.readADC_SingleEnded(0);
    Serial.print (Cont);
    Serial.print(F(" / "));
    Serial.print (Cont * 0.000333F);
    Serial.println(F("V"));

    Serial.print(F("Input 1 Corrent: "));
    Cont = ads1115_C.readADC_SingleEnded(0);
    Serial.print (Cont);
    Serial.print(F(" / "));
    Serial.print (Cont * 0.000665F);
    Serial.println(F("mA"));

    delay (20);
    Serial.print(F("Input 2 Voltage: "));
    Cont = ads1115_V.readADC_SingleEnded(1);
    Serial.print (Cont);
    Serial.print(F(" / "));
    Serial.print (Cont * 0.000333F);
    Serial.println(F("V"));

    Serial.print(F("Input 2 Corrent: "));
    Cont = ads1115_C.readADC_SingleEnded(1);
    Serial.print (Cont);
    Serial.print(F(" / "));
    Serial.print (Cont * 0.000665F);
    Serial.println(F("mA"));
    delay (20);

    Serial.print(F("Input 3 Voltage: "));
    Cont = ads1115_V.readADC_SingleEnded(2);
    Serial.print (Cont);
    Serial.print(F(" / "));
    Serial.print (Cont * 0.000333F);
    Serial.println(F("V"));

    Serial.print(F("Input 3 Corrent: "));
    Cont = ads1115_C.readADC_SingleEnded(2);
    Serial.print (Cont);
    Serial.print(F(" / "));
    Serial.print (Cont * 0.000665F);
    Serial.println(F("mA"));
    delay (20);

    Serial.print(F("Input 4 Voltage: "));
    Cont = ads1115_V.readADC_SingleEnded(3);
    Serial.print (Cont);
    Serial.print(F(" / "));
    Serial.print (Cont * 0.000333F);
    Serial.println(F("V"));

    Serial.print(F("Input 4 Corrent: "));
    Cont = ads1115_C.readADC_SingleEnded(3);
    Serial.print (Cont);
    Serial.print(F(" / "));
    Serial.print (Cont * 0.000665F);
    Serial.println(F("mA"));
    delay (5000);
  }
}
