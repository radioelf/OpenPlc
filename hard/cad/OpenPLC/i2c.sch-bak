EESchema Schematic File Version 5
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 8
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
Comment5 ""
Comment6 ""
Comment7 ""
Comment8 ""
Comment9 ""
$EndDescr
$Comp
L OpenPLC-rescue:DS3231-Timer_RTC U2
U 1 1 5D31B924
P 5850 3400
F 0 "U2" H 5500 3850 50  0000 C CNN
F 1 "DS3231MZ" H 6100 2950 50  0000 C CNN
F 2 "Package_SO:SOIC-18W_7.5x11.6mm_P1.27mm" H 5850 2800 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS3231M.pdf" H 5850 2700 50  0001 C CNN
	1    5850 3400
	1    0    0    -1  
$EndComp
$Comp
L Memory_EEPROM:24LC32 U3
U 1 1 5D3CC7A9
P 5850 4700
F 0 "U3" H 6100 4400 50  0000 C CNN
F 1 "24LC32" H 5650 4950 50  0000 C CNN
F 2 "Package_SO:MSOP-8_3x3mm_P0.65mm" H 5900 4450 50  0001 L CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21072G.pdf" H 5850 4600 50  0001 C CNN
	1    5850 4700
	-1   0    0    1   
$EndComp
Wire Wire Line
	5450 4700 4950 4700
Wire Wire Line
	4950 4700 4950 3300
Wire Wire Line
	4950 3300 5350 3300
Connection ~ 4950 3300
Wire Wire Line
	4650 3400 5350 3400
Wire Wire Line
	5450 4800 4650 4800
Wire Wire Line
	4650 4800 4650 3400
Connection ~ 4650 3400
Wire Wire Line
	5850 3900 5850 4100
Text HLabel 4000 3400 0    50   BiDi ~ 0
SDA
Text HLabel 4000 3300 0    50   Input ~ 0
SDL
Wire Wire Line
	4000 3300 4950 3300
Wire Wire Line
	4650 3400 4000 3400
Wire Wire Line
	5850 2900 5850 2750
$Comp
L power:+3.3V #PWR0120
U 1 1 5D398CD7
P 5850 2600
F 0 "#PWR0120" H 5850 2450 50  0001 C CNN
F 1 "+3.3V" H 5865 2773 50  0000 C CNN
F 2 "" H 5850 2600 50  0001 C CNN
F 3 "" H 5850 2600 50  0001 C CNN
	1    5850 2600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0121
U 1 1 5D3993EC
P 5850 5150
F 0 "#PWR0121" H 5850 5000 50  0001 C CNN
F 1 "+3.3V" H 5865 5323 50  0000 C CNN
F 2 "" H 5850 5150 50  0001 C CNN
F 3 "" H 5850 5150 50  0001 C CNN
	1    5850 5150
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 5D399AD8
P 5400 4150
F 0 "#PWR0122" H 5400 3900 50  0001 C CNN
F 1 "GND" H 5405 3977 50  0000 C CNN
F 2 "" H 5400 4150 50  0001 C CNN
F 3 "" H 5400 4150 50  0001 C CNN
	1    5400 4150
	1    0    0    -1  
$EndComp
Text HLabel 4000 4100 0    50   UnSpc ~ 0
GND
Wire Wire Line
	4000 4100 5150 4100
Connection ~ 5850 4100
Wire Wire Line
	5850 4100 5850 4400
Wire Wire Line
	5400 4150 5400 4100
Connection ~ 5400 4100
Wire Wire Line
	5400 4100 5850 4100
Wire Wire Line
	5850 5000 5850 5100
Wire Wire Line
	5850 2600 5850 2750
Connection ~ 5850 2750
Text HLabel 4000 2750 0    50   Input ~ 0
+3.3V
Wire Wire Line
	5850 4100 6550 4100
Wire Wire Line
	6550 4100 6550 4600
Wire Wire Line
	6550 4800 6250 4800
Wire Wire Line
	6250 4700 6550 4700
Connection ~ 6550 4700
Wire Wire Line
	6550 4700 6550 4800
Wire Wire Line
	6250 4600 6550 4600
Connection ~ 6550 4600
Wire Wire Line
	6550 4600 6550 4700
$Comp
L Device:C C13
U 1 1 5D3A34D7
P 6750 2950
F 0 "C13" H 6865 2996 50  0000 L CNN
F 1 "100nF" H 6865 2905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6788 2800 50  0001 C CNN
F 3 "~" H 6750 2950 50  0001 C CNN
	1    6750 2950
	1    0    0    -1  
$EndComp
NoConn ~ 6350 3300
NoConn ~ 6350 3400
NoConn ~ 5350 3600
Text Notes 5950 4450 0    50   ~ 0
Address  0X50
$Comp
L Device:Battery_Cell BT1
U 1 1 5D3A669F
P 6750 3300
F 0 "BT1" H 6632 3304 50  0000 R CNN
F 1 "Battery_Cell" H 6632 3395 50  0000 R CNN
F 2 "Battery:BatteryHolder_Keystone_103_1x20mm" V 6750 3360 50  0001 C CNN
F 3 "~" V 6750 3360 50  0001 C CNN
	1    6750 3300
	-1   0    0    1   
$EndComp
Wire Wire Line
	5850 2750 6750 2750
Wire Wire Line
	6750 2750 6750 2800
Wire Wire Line
	6350 3600 6750 3600
Wire Wire Line
	6750 3600 6750 3500
Wire Wire Line
	6750 3100 6750 3150
$Comp
L power:GND #PWR0123
U 1 1 5D3A74B6
P 7150 3150
F 0 "#PWR0123" H 7150 2900 50  0001 C CNN
F 1 "GND" V 7250 3100 50  0000 C CNN
F 2 "" H 7150 3150 50  0001 C CNN
F 3 "" H 7150 3150 50  0001 C CNN
	1    7150 3150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7150 3150 6750 3150
Connection ~ 6750 3150
Wire Wire Line
	6750 3150 6750 3200
Text Notes 6050 3000 0    50   ~ 0
Address 0x68
Wire Wire Line
	4000 2750 5850 2750
Text Notes 4250 3250 0    50   ~ 0
Pull-UP in RPI
Wire Wire Line
	5450 4600 5150 4600
Wire Wire Line
	5150 4600 5150 4100
Connection ~ 5150 4100
Wire Wire Line
	5150 4100 5400 4100
Text Notes 8750 6900 0    50   ~ 0
RTC-  EEPROM
$Comp
L Device:C C8
U 1 1 5D8C9879
P 6300 5100
F 0 "C8" V 6250 5150 50  0000 L CNN
F 1 "100nF" V 6415 5055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6338 4950 50  0001 C CNN
F 3 "~" H 6300 5100 50  0001 C CNN
	1    6300 5100
	0    1    1    0   
$EndComp
Wire Wire Line
	6550 4800 6550 5100
Wire Wire Line
	6550 5100 6450 5100
Connection ~ 6550 4800
Wire Wire Line
	6150 5100 5850 5100
Connection ~ 5850 5100
Wire Wire Line
	5850 5100 5850 5150
$EndSCHEMATC
