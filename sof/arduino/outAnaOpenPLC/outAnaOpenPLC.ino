/* Control de cuatro salidas analógicas 0-10V / 4-20mA a traves de Modbus/RS485 para OpenPLC.
  Usamos un DAC MCP472 de cuatro canales y cuatro XTR300 como drivers de salida 4-20mA/0-10V

  http://www.simplymodbus.ca/FAQ.htm

  Function Code OpenPLC
  [02] Discrete Inputs (%IX100.0)
  [03] Holding Registers - Read (%IW100)
  [04] Input Registers (%IW100)
  [15] Coils (%QX100.0)
  [16] Holding Registers - Write (%QW100)

  TX OpenPLC ->02 10 00 00 00 04 08 00 00 00 00 00 00 00 00 f5 7b
  Modbus read Analog Input Registers FC=06
  RX Modbus
  ID   Function Code  Data Address  value to write  bytes to follow value data   CRC
  2        10            0000             0004           08   00000000000000     F57B
                     40001 + 1
  TX Modbus to OpenPLC ->
  ID   Function Code  Data Address   value written   CRC
  2        10            0001             0001      800D

  4 analog outputs (%QW100 - %QW103)

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

#include "MCP4728.h"                                                // https://github.com/hideakitai/MCP4728

//ModBus puerto
#define BAUD        19200

#define pinTxRs485  2                 // pin RE/SDHN RS485
#define pinXTR300A  3                 // pin modo funcionamiento 1-> 4-20mA, 0-> 0-10V
#define pinXTR300B  4                 // pin modo funcionamiento 1-> 4-20mA, 0-> 0-10V
#define pinXTR300C  5                 // pin modo funcionamiento 1-> 4-20mA, 0-> 0-10V
#define pinXTR300D  6                 // pin modo funcionamiento 1-> 4-20mA, 0-> 0-10V
#define pinXTR300OD 13                // pin XTR300 Disabled ->Low
#define pinRUN      7                 // pin estado RUN/STOP
#define pinLDAC     8                 // pin entrada de sincronización/selección para leer y escribir bits
#define pinLedData  10                // pin indicación modo datos RS485
#define pinLedRun   11                // pin indicación modo RUN/STOP
#define pinErrorA   17                // pin error XTR300
#define pinErrorB   16                // pin error XTR300
#define pinErrorC   15                // pin error XTR300
#define pinErrorD   14                // pin error XTR300

uint8_t ID = 2;                       // ID para el bus RS485
uint8_t trama [128];                  // longitud de la trama RS485
uint8_t Config = B0000;               // configuración tipo de salidas de los IC XTR300
double factor_V = 1.00000F;
double factor_C = 1.00000F;
String inputString = "";

#include "Modbus.h"                   // https://github.com/andresarmento/modbus-arduino
#include "ModbusSerial.h"
#include "Eeprom.h"

// Modbus objeto
ModbusSerial modbus;
// DAC objeto
MCP4728 dac;                          // address I2C 0x60

//******************************************************************
// Configuración
//******************************************************************
void setup() {

  pinMode(pinLedRun, OUTPUT);
  pinMode(pinXTR300A, OUTPUT);
  pinMode(pinXTR300B, OUTPUT);
  pinMode(pinXTR300C, OUTPUT);
  pinMode(pinXTR300D, OUTPUT);
  pinMode(pinXTR300OD, OUTPUT);
  pinMode(pinRUN, INPUT);
  pinMode(pinErrorA, INPUT_PULLUP);
  pinMode(pinErrorB, INPUT_PULLUP);
  pinMode(pinErrorC, INPUT_PULLUP);
  pinMode(pinErrorD, INPUT_PULLUP);

  digitalWrite(pinLedRun, LOW);
  digitalWrite(pinXTR300OD, HIGH);

  inputString.reserve(8);

  //Config Modbus Serial (puerto, velocidad, pin rs485 tx)
  modbus.config(&Serial, BAUD, pinTxRs485, pinLedData); // 115200 8N1

  delay (500);
  Wire.begin();
  dac.attatch(Wire, pinLDAC);
  dac.readRegisters();
  // Vref interna 2.048V, Ganacia x2->LSB Size 1mV, 4.096V/4096
  dac.selectVref(MCP4728::VREF::INTERNAL_2_8V, MCP4728::VREF::INTERNAL_2_8V, MCP4728::VREF::INTERNAL_2_8V, MCP4728::VREF::INTERNAL_2_8V);
  // Valor de la resistencia conectada a la salida con GND en modo apagado
  dac.selectPowerDown(MCP4728::PWR_DOWN::GND_100KOHM, MCP4728::PWR_DOWN::GND_100KOHM, MCP4728::PWR_DOWN::GND_100KOHM, MCP4728::PWR_DOWN::GND_100KOHM);
  // Ganacia x2
  dac.selectGain(MCP4728::GAIN::X2, MCP4728::GAIN::X2, MCP4728::GAIN::X2, MCP4728::GAIN::X2);
  dac.analogWrite(MCP4728::DAC_CH::A, 0);
  dac.analogWrite(MCP4728::DAC_CH::B, 0);
  dac.analogWrite(MCP4728::DAC_CH::C, 0);
  dac.analogWrite(MCP4728::DAC_CH::D, 0);
  dac.enable(true);
  dac.readRegisters();
  dac.analogWrite(0, 0, 0, 0);

  if (EEPROM.read(0) != 128) {                                    // actualizamos a datos por defecto?
    EEPROM.write(0, 128);
    ID = 2;
    factor_V = 1.00000F;
    factor_C = 1.00000F;
    Config = B0000;
    EepromTx(0);
    EepromTx(1);
    EepromTx(2);
    EepromTx(3);
  }
  EepromRx(0);                                                    // Leemos la configuración de la EEPROM
  EepromRx(1);
  EepromTx(2);
  EepromTx(3);

  modbus.setSlaveId(ID);
  for (uint8_t i = 0; i < 8; ++i) {
    modbus.addHreg(i);                                            // Registros modbus 0, 1, 2, y 3
    digitalWrite ((pinXTR300A + i), bitRead(Config, i));
  }
}

bool STOP = true;
uint32_t ts = 0;
//******************************************************************
// Main
//******************************************************************
void loop() {
  uint8_t x = 0;
  uint16_t Set_Output [4] {0, 0, 0, 0};

  while (!digitalRead (pinRUN)) {                                 // OpenPLC en RUN?
    Stop_Config();                                                // NO, menú configuración
    uint8_t Cont = 0;
    do {
      delay (20);
    } while (!digitalRead (pinRUN) && Cont++ < 100);
  }
  if (STOP == true) {
    digitalWrite(pinTxRs485, LOW);
    digitalWrite(pinLedRun, HIGH);
    STOP = false;
  }
  // Obtenemos el valor de las salidas analógicas 0-10V o 4-20mA
  do {
    modbus.task();
    if ((millis () - ts) >= 50){
                
      if (!digitalRead (pinErrorA - x)) {                         // Error?
        ErrorXTR(x);
      }
      else {
        if (Set_Output [x] != modbus.Hreg(x)) {                   // tenemos que actualizar?
          Set_Output [x] = modbus.Hreg(x);
          SetOutput(x, Set_Output [x]);                           // colocamos el valor en la salida correspondiente
        }
      }
      if (++x == 4) x = 0;                                          // 0, 1, 2, 3
      ts = millis();
    }
  } while (digitalRead (pinRUN) && STOP == false);
}
//******************************************************************
// Ajustamos el valor de la salida del DAC 12bits (0-4095)
//******************************************************************
void SetOutput(byte channel, uint16_t value) {
  bool C_V = bitRead(Config, channel);
  uint16_t x = (value * (C_V == 1 ? factor_C : factor_V));
  if (C_V) {
    dac.analogWrite(channel, map(x, 10, 3645, 0, 65535));           // corriente
  }
  else {
    dac.analogWrite(channel, map(x, 0, 65535, 10, 3645));           // voltaje
  }
}

//******************************************************************
// Error en XTR 300
//******************************************************************
void ErrorXTR(uint8_t n) {
  dac.analogWrite(0, 0, 0, 0);
  digitalWrite(pinLedData, LOW);
  STOP = true;
  uint8_t x = 0;
  Serial.print(F("Error en salida: ")); Serial.println(n);
  while (!digitalRead (pinErrorA - n) && digitalRead (pinRUN)) {
    digitalWrite (pinXTR300A + n, !digitalRead(n));
    delay (200);
    Serial.println(".");
  }
  digitalWrite ((pinXTR300A + n), bitRead(Config, n));
  delay (500);
}

//******************************************************************
// Menú configuración
//******************************************************************
void Stop_Config() {
  uint8_t i;
  uint16_t Cont = 0;
  dac.enable(false);
  digitalWrite(pinLedRun, LOW);
  digitalWrite(pinTxRs485, HIGH);                                 // NECESARIO a 0 para poder programar el arduino desde USB
  digitalWrite(pinLedData, LOW);
  uint8_t status_i2c = dac.analogWrite(0, 0, 0, 0);

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
    if (!status_i2c) {
      for (i = 0; i < 4; i++) {
        Serial.print(F("output "));
        Serial.print(i + 1);
        Serial.print(F(" of "));
        if (bitRead(Config, i)) {
          Serial.print(F("4-20mA "));
        }
        else {
          Serial.print(F("0-10V "));
        }
        Serial.print(F("status:"));
        if (!digitalRead (pinErrorA - i)) {
          Serial.println(F(" ERROR"));
        }
        else {
          Serial.println(F(" OK"));
        }
      }
    }
    else {
      Wire.beginTransmission(0x60);
      status_i2c = Wire.endTransmission();
      // 0: OK
      // 1: datos demasiado largo para caber en la memoria intermedia de transmisión
      // 2: NACK recibido en transmisión de dirección
      // 3: recibido NACK en transmisión de datos
      // 4: otro error
      if (status_i2c == 0) {
        Serial.print(F("Error respuesta MCP4728"));
      }
      else {
        Serial.print(F("Error comunicacion I2C: "));
        Serial.println(status_i2c);
        STOP = false;
      }
      delay (5000);
      return;
    }
    Serial.println(F("---------------------------"));
  }
  while (Serial.available())  {
    Serial.read();                                                      // Clear buffer
  }

  Serial.println(F("--Config. Board Output Analog Current/Voltage--"));
  Serial.println(F("  1-ID RS485"));
  Serial.println(F("  2-Current Calibration"));
  Serial.println(F("  3-Voltage Calibration"));
  Serial.println(F("  4-Out 1->4-20mA / 0->0-10V"));
  Serial.println(F("  5-DEFAULT"));
  Serial.println(F("  r-Read"));
  Serial.println(F("  t-Test outputs 50%"));
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
  uint8_t option = (Serial.read());
  while (Serial.available())  {
    Serial.read();                                                        // Clear buffer
  }
  if (option == 'x') return;
  Serial.println();
  if (option == 't') {
    uint16_t value = 5;
    for (i = 0; i < 4; i++) {
      SetOutput (i, 32767);                                                // 16 bits -> 65535/ 2= 32767
    }
    Serial.println(F("Run outputs 50%"));
    delay (10000);
    dac.analogWrite(0, 0, 0, 0);
    Serial.println(F("STOP outputs 0%"));
    return;
  }
  if (option == '5') {
    Serial.println(F("Value default and RESET!"));
    EEPROM.update(0, 0);
    delay (1000);
    asm("jmp 0x0000");
  }

  if (option > 48 && option < 53) {
    uint8_t character = 7;
    if (option == '1') {
      Serial.print(F("The ID is: "));
      Serial.println(ID, DEC);
      character = 1;
    } else if (option == '2') {
      Serial.print(F("The current factor is: "));
      Serial.println(factor_C, 6);
    } else if (option == '3') {
      Serial.print(F("The Voltage factor is: "));
      Serial.println(factor_V, 6);
    } else if (option == '4') {
      Serial.print(F("output configuration: "));
      Serial.print(bitRead(Config, 3));
      Serial.print(bitRead(Config, 2));
      Serial.print(bitRead(Config, 1));
      Serial.println(bitRead(Config, 0));
      character = 4;
    }
    Serial.print(F("New value (characters number "));
    Serial.print (character);
    Serial.println (F(") "));
    while (Serial.available())  {
      Serial.read(); //Clear buffer
    }
    while (Serial.available() == 0) {
      delay (10);
      if (++Cont == 1000) return;                                       // esperamos 10 segundos...
    }
    if (Serial.available() != character) {
      Serial.println (Serial.available());
      Serial.println(F("NOT valid!!"));
      return;
    }
    for (i = 0; i != character; i++) {
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
    } else if (option == '4') {
      Serial.print(F("1->4-20mA / 0->0-10V: "));
      if (inputString[0] == 48 || inputString[0] == 49) {
        bitWrite(Config, 0, (inputString[0] - 48));
        digitalWrite (pinXTR300A, (inputString[0] - 48));
        Serial.print(inputString[0]);
      }
      else {
        Serial.print(F("X"));
      }
      if (inputString[1] == 48 || inputString[1] == 49) {
        bitWrite(Config, 1, (inputString[1] - 48));
        digitalWrite (pinXTR300B, (inputString[1] - 48));
        Serial.print(inputString[1]);
      }
      else {
        Serial.print(F("X"));
      }
      if (inputString[2] == 48 || inputString[2] == 49) {
        bitWrite(Config, 2, (inputString[2] - 48));
        digitalWrite (pinXTR300C, (inputString[2] - 48));
        Serial.print(inputString[2]);
      }
      else {
        Serial.print(F("X"));
      }
      if (inputString[3] == 48 || inputString[3] == 49) {
        bitWrite(Config, 3, (inputString[3] - 48));
        digitalWrite (pinXTR300D, (inputString[3] - 48));
        Serial.println(inputString[3]);
      }
      else {
        Serial.println(F("X"));
      }
      Serial.println(F("-E- to save in EEPROM"));
    }
    inputString = "";                                                   // limpiamos  String
    while (!Serial.available()) {
      delay (10);
      if (++Cont == 1000) return;                                       // esperamos 10 segundos...
    }
    if (Serial.read() == 'E') {
      EepromTx(0);
      EepromTx(1);
      EepromTx(2);
      EepromTx(3);
      Serial.println(F("Save in EEPROM"));
    } else {
      return;
    }
  } else {
    if (option != 'r') return;                                            // RX serial NO "r"
    dac.readRegisters();
    Serial.println('\n');
    for (i = 0; i < 4; i++) {
      Serial.print("DAC    ");
      Serial.print(i, DEC);
      Serial.print(" getVref: ");
      Serial.print(dac.getVref(i), BIN);
      Serial.print(" getGain: ");
      Serial.print(dac.getGain(i), BIN);
      Serial.print(" getPowerDown: ");
      Serial.print(dac.getPowerDown(i), BIN);
      Serial.print(" getDACData: ");
      Serial.println(dac.getDACData(i), DEC);

      Serial.print("EEPROM ");
      Serial.print(i, DEC);
      Serial.print(" getVref: ");
      Serial.print(dac.getVref(i, true), BIN);
      Serial.print(" getGain: ");
      Serial.print(dac.getGain(i, true), BIN);
      Serial.print(" getPowerDown: ");
      Serial.print(dac.getPowerDown(i, true), BIN);
      Serial.print(" getDACData: ");
      Serial.println(dac.getDACData(i, true), DEC);
    }
    Serial.println('\n');
    delay (5000);
  }
}
