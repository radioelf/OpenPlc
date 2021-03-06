EESchema Schematic File Version 5
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 8
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
Wire Wire Line
	4350 3450 4300 3450
Wire Wire Line
	4300 3450 4300 3550
Wire Wire Line
	4300 3550 4350 3550
$Comp
L Device:R R50
U 1 1 5D3B5562
P 5650 3100
F 0 "R50" H 5720 3146 50  0000 L CNN
F 1 "4k2" H 5720 3055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5580 3100 50  0001 C CNN
F 3 "~" H 5650 3100 50  0001 C CNN
	1    5650 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R51
U 1 1 5D3B5B87
P 5650 4000
F 0 "R51" H 5720 4046 50  0000 L CNN
F 1 "4k2" H 5720 3955 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5580 4000 50  0001 C CNN
F 3 "~" H 5650 4000 50  0001 C CNN
	1    5650 4000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R52
U 1 1 5D3B5F9A
P 5950 3500
F 0 "R52" V 5900 3650 50  0000 L CNN
F 1 "120R" V 6050 3400 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5880 3500 50  0001 C CNN
F 3 "~" H 5950 3500 50  0001 C CNN
	1    5950 3500
	0    1    1    0   
$EndComp
Text HLabel 3100 2900 0    50   Input ~ 0
+3.3V
Text HLabel 3100 2600 0    50   Input ~ 0
+5V
Text HLabel 3100 4150 0    50   UnSpc ~ 0
GND
Text HLabel 3100 3650 0    50   Input ~ 0
TXD
Text HLabel 3100 3350 0    50   Output ~ 0
RXD
$Comp
L OpenPLC-rescue:MAX13487-Interface_UART U12
U 1 1 5D3D1084
P 4750 3450
F 0 "U12" H 4500 3900 50  0000 C CNN
F 1 "MAX13487" H 4950 3900 50  0000 C CNN
F 2 "Package_SO:PowerIntegrations_SO-8" H 4750 2750 50  0001 C CNN
F 3 "https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=12&cad=rja&uact=8&ved=2ahUKEwj63uXFp9bjAhUCbBoKHdRvDqsQFjALegQIARAC&url=https%3A%2F%2Fdatasheets.maximintegrated.com%2Fen%2Fds%2FMAX13487E-MAX13488E.pdf&usg=AOvVaw1T8jUhUf9rAcz-cFRcjWsZ" H 4750 3500 50  0001 C CNN
	1    4750 3450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0183
U 1 1 5D3D4926
P 4750 2500
F 0 "#PWR0183" H 4750 2350 50  0001 C CNN
F 1 "+5V" H 4765 2673 50  0000 C CNN
F 2 "" H 4750 2500 50  0001 C CNN
F 3 "" H 4750 2500 50  0001 C CNN
	1    4750 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0184
U 1 1 5D3D5026
P 4750 4300
F 0 "#PWR0184" H 4750 4050 50  0001 C CNN
F 1 "GND" H 4755 4127 50  0000 C CNN
F 2 "" H 4750 4300 50  0001 C CNN
F 3 "" H 4750 4300 50  0001 C CNN
	1    4750 4300
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0185
U 1 1 5D3D56E6
P 3400 2850
F 0 "#PWR0185" H 3400 2700 50  0001 C CNN
F 1 "+3.3V" H 3415 3023 50  0000 C CNN
F 2 "" H 3400 2850 50  0001 C CNN
F 3 "" H 3400 2850 50  0001 C CNN
	1    3400 2850
	1    0    0    -1  
$EndComp
$Comp
L OpenPLC-rescue:D_TVS-Device D23
U 1 1 5D3D6DD8
P 6250 3000
AR Path="/5D3D6DD8" Ref="D23"  Part="1" 
AR Path="/5D309516/5D3D6DD8" Ref="D23"  Part="1" 
F 0 "D23" V 6350 3150 50  0000 C CNN
F 1 "6V8C" V 6200 3150 50  0000 C CNN
F 2 "Diode_SMD:D_2010_5025Metric" H 6250 3000 50  0001 C CNN
F 3 "~" H 6250 3000 50  0001 C CNN
	1    6250 3000
	0    1    1    0   
$EndComp
$Comp
L Device:R R67
U 1 1 5D3D7D9A
P 7100 3650
F 0 "R67" V 7200 3700 50  0000 L CNN
F 1 "100R" V 7200 3450 50  0000 L CNN
F 2 "Resistor_SMD:R_2512_6332Metric" V 7030 3650 50  0001 C CNN
F 3 "~" H 7100 3650 50  0001 C CNN
	1    7100 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	7450 3350 7250 3350
Wire Wire Line
	6950 3350 6250 3350
Wire Wire Line
	6950 3650 6250 3650
Wire Wire Line
	6250 3850 6250 3650
Connection ~ 6250 3650
Wire Wire Line
	6250 3650 5650 3650
Wire Wire Line
	6250 3150 6250 3350
Connection ~ 6250 3350
Wire Wire Line
	6250 3350 5650 3350
Wire Wire Line
	5650 3250 5650 3350
Connection ~ 5650 3350
Wire Wire Line
	5650 3350 5150 3350
Wire Wire Line
	5650 3650 5650 3850
Connection ~ 5650 3650
Wire Wire Line
	5650 3650 5150 3650
Wire Wire Line
	4750 4050 4750 4150
Wire Wire Line
	4750 2500 4750 2600
Wire Wire Line
	3400 2850 3400 2900
Wire Wire Line
	3100 2900 3400 2900
Connection ~ 3400 2900
Wire Wire Line
	4350 3650 3200 3650
Wire Wire Line
	3100 4150 3200 4150
Connection ~ 4750 4150
Wire Wire Line
	4750 4150 4750 4300
$Comp
L power:+5V #PWR0186
U 1 1 5D3DA23E
P 5650 4300
F 0 "#PWR0186" H 5650 4150 50  0001 C CNN
F 1 "+5V" H 5665 4473 50  0000 C CNN
F 2 "" H 5650 4300 50  0001 C CNN
F 3 "" H 5650 4300 50  0001 C CNN
	1    5650 4300
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0187
U 1 1 5D3DA719
P 5650 2500
F 0 "#PWR0187" H 5650 2250 50  0001 C CNN
F 1 "GND" H 5655 2327 50  0000 C CNN
F 2 "" H 5650 2500 50  0001 C CNN
F 3 "" H 5650 2500 50  0001 C CNN
	1    5650 2500
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0188
U 1 1 5D3DA9A1
P 6250 4300
F 0 "#PWR0188" H 6250 4050 50  0001 C CNN
F 1 "GND" H 6255 4127 50  0000 C CNN
F 2 "" H 6250 4300 50  0001 C CNN
F 3 "" H 6250 4300 50  0001 C CNN
	1    6250 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 2600 5650 2600
Wire Wire Line
	5650 2500 5650 2600
Connection ~ 5650 2600
Wire Wire Line
	5650 2600 5650 2850
Wire Wire Line
	6250 4150 6250 4300
Wire Wire Line
	6100 3500 6250 3500
Wire Wire Line
	6250 3500 6250 3650
Wire Wire Line
	5800 3500 5650 3500
Wire Wire Line
	5650 3500 5650 3350
$Comp
L Device:C C18
U 1 1 5D3DE42A
P 5200 2600
F 0 "C18" V 4948 2600 50  0000 C CNN
F 1 "100nF" V 5039 2600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5238 2450 50  0001 C CNN
F 3 "~" H 5200 2600 50  0001 C CNN
	1    5200 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	5350 2600 5650 2600
Wire Wire Line
	5050 2600 4750 2600
Connection ~ 4750 2600
Wire Wire Line
	4300 3450 4300 3150
Connection ~ 4300 3450
Connection ~ 4300 2600
Wire Wire Line
	4300 2600 4750 2600
Wire Wire Line
	6250 2600 6250 2850
Wire Wire Line
	5650 4150 5650 4300
Wire Wire Line
	4750 2600 4750 2850
$Comp
L OpenPLC-rescue:D_TVS-Device D20
U 1 1 5D3B0437
P 6250 4000
AR Path="/5D3B0437" Ref="D20"  Part="1" 
AR Path="/5D309516/5D3B0437" Ref="D20"  Part="1" 
F 0 "D20" V 6350 4150 50  0000 C CNN
F 1 "6V8C" V 6200 4150 50  0000 C CNN
F 2 "Diode_SMD:D_2010_5025Metric" H 6250 4000 50  0001 C CNN
F 3 "~" H 6250 4000 50  0001 C CNN
	1    6250 4000
	0    1    1    0   
$EndComp
Text HLabel 8200 4000 0    50   Input ~ 0
+24V
Text HLabel 7450 3200 0    50   Input ~ 0
RUN-STOP
$Comp
L OpenPLC-rescue:MAX3370-maxim U11
U 1 1 5D456CA4
P 3750 3250
F 0 "U11" H 3750 3592 50  0000 C CNN
F 1 "MAX3370" H 3750 3501 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-353_SC-70-5" H 3750 3550 50  0001 C CIN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX3370-MAX3371.pdf" H 3750 3300 50  0001 C CNN
	1    3750 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 2600 4300 2600
Wire Wire Line
	3750 3550 3750 4150
Connection ~ 3750 4150
Wire Wire Line
	3750 4150 4750 4150
Wire Wire Line
	4350 3350 4050 3350
Wire Wire Line
	4050 3150 4300 3150
Connection ~ 4300 3150
Wire Wire Line
	4300 3150 4300 2600
Wire Wire Line
	3450 3350 3200 3350
Wire Wire Line
	3400 3150 3450 3150
Wire Wire Line
	3400 2900 3400 3150
$Comp
L Connector_Generic:Conn_02x07_Odd_Even J7
U 1 1 5D3F1054
P 8000 3500
F 0 "J7" H 8050 4017 50  0000 C CNN
F 1 "Conn_02x07_Odd_Even" H 8050 3926 50  0000 C CNN
F 2 "Connector_IDC:IDC-Header_2x07_P2.54mm_Horizontal_Lock" H 8000 3500 50  0001 C CNN
F 3 "~" H 8000 3500 50  0001 C CNN
	1    8000 3500
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0153
U 1 1 5D3F503A
P 9100 4150
F 0 "#PWR0153" H 9100 4000 50  0001 C CNN
F 1 "+5V" H 9115 4323 50  0000 C CNN
F 2 "" H 9100 4150 50  0001 C CNN
F 3 "" H 9100 4150 50  0001 C CNN
	1    9100 4150
	-1   0    0    1   
$EndComp
$Comp
L power:+24V #PWR0189
U 1 1 5D3F520A
P 8450 4150
F 0 "#PWR0189" H 8450 4000 50  0001 C CNN
F 1 "+24V" H 8465 4323 50  0000 C CNN
F 2 "" H 8450 4150 50  0001 C CNN
F 3 "" H 8450 4150 50  0001 C CNN
	1    8450 4150
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0190
U 1 1 5D3F4CBD
P 8900 4150
F 0 "#PWR0190" H 8900 3900 50  0001 C CNN
F 1 "GND" H 8905 3977 50  0000 C CNN
F 2 "" H 8900 4150 50  0001 C CNN
F 3 "" H 8900 4150 50  0001 C CNN
	1    8900 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 3400 9100 4150
Wire Wire Line
	8300 3400 9100 3400
Wire Wire Line
	7800 3300 7450 3300
Wire Wire Line
	7450 3300 7450 3350
Wire Wire Line
	7800 3200 7450 3200
$Comp
L power:+3.3V #PWR0191
U 1 1 5D3EBA54
P 8700 4150
F 0 "#PWR0191" H 8700 4000 50  0001 C CNN
F 1 "+3.3V" H 8715 4323 50  0000 C CNN
F 2 "" H 8700 4150 50  0001 C CNN
F 3 "" H 8700 4150 50  0001 C CNN
	1    8700 4150
	-1   0    0    1   
$EndComp
Text Label 7600 3200 0    50   ~ 0
Run
Text Label 7450 3300 0    50   ~ 0
B-RS485
Text Label 7450 3700 0    50   ~ 0
A-RS485
Wire Wire Line
	7450 3700 7450 3650
Wire Wire Line
	7450 3650 7250 3650
Wire Wire Line
	7450 3700 7800 3700
Text Label 7600 3500 0    50   ~ 0
+3.3V
Text Label 8350 3600 0    50   ~ 0
GND
Text Label 8350 3400 0    50   ~ 0
+5V
Text Label 8350 3800 0    50   ~ 0
+24V
Wire Wire Line
	7800 3400 7450 3400
Wire Wire Line
	7800 3500 7450 3500
Wire Wire Line
	7800 3600 7450 3600
Text Label 7600 3400 0    50   ~ 0
+5V
Text Label 7600 3600 0    50   ~ 0
GND
Text Label 7600 3800 0    50   ~ 0
+24V
Text Label 8350 3500 0    50   ~ 0
+3.3V
$Comp
L Device:R R66
U 1 1 5D3D76F1
P 7100 3350
F 0 "R66" V 7200 3400 50  0000 L CNN
F 1 "100R" V 7200 3150 50  0000 L CNN
F 2 "Resistor_SMD:R_2512_6332Metric" V 7030 3350 50  0001 C CNN
F 3 "~" H 7100 3350 50  0001 C CNN
	1    7100 3350
	0    1    1    0   
$EndComp
$Comp
L Connector_Specialized:Test_Point TP1
U 1 1 5D4FFAAD
P 3200 3300
F 0 "TP1" H 3258 3418 50  0000 L CNN
F 1 "RX" H 3250 3350 50  0000 L CNN
F 2 "TestPoint:TestPoint_Loop_D1.80mm_Drill1.0mm_Beaded" H 3400 3300 50  0001 C CNN
F 3 "~" H 3400 3300 50  0001 C CNN
	1    3200 3300
	1    0    0    -1  
$EndComp
$Comp
L Connector_Specialized:Test_Point TP2
U 1 1 5D50051D
P 3200 3600
F 0 "TP2" H 3258 3718 50  0000 L CNN
F 1 "TX" H 3258 3627 50  0000 L CNN
F 2 "TestPoint:TestPoint_Loop_D1.80mm_Drill1.0mm_Beaded" H 3400 3600 50  0001 C CNN
F 3 "~" H 3400 3600 50  0001 C CNN
	1    3200 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 3600 3200 3650
Connection ~ 3200 3650
Wire Wire Line
	3200 3650 3100 3650
Wire Wire Line
	3200 3300 3200 3350
Connection ~ 3200 3350
Wire Wire Line
	3200 3350 3100 3350
$Comp
L Connector_Specialized:Test_Point TP3
U 1 1 5D50DC75
P 3200 4100
F 0 "TP3" H 3258 4218 50  0000 L CNN
F 1 "GND" H 3258 4127 50  0000 L CNN
F 2 "TestPoint:TestPoint_Loop_D1.80mm_Drill1.0mm_Beaded" H 3400 4100 50  0001 C CNN
F 3 "~" H 3400 4100 50  0001 C CNN
	1    3200 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 4100 3200 4150
Connection ~ 3200 4150
Wire Wire Line
	3200 4150 3750 4150
$Comp
L Device:CP C7
U 1 1 5D52E0EA
P 5200 2850
F 0 "C7" V 5250 3000 50  0000 C CNN
F 1 "10uF" V 5250 2700 50  0000 C CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3216-10_Kemet-I" H 5238 2700 50  0001 C CNN
F 3 "~" H 5200 2850 50  0001 C CNN
	1    5200 2850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5350 2850 5650 2850
Connection ~ 5650 2850
Wire Wire Line
	5650 2850 5650 2950
Wire Wire Line
	5050 2850 4750 2850
Connection ~ 4750 2850
Wire Wire Line
	4750 2850 4750 2950
Text Notes 8400 6900 0    71   ~ 0
Modbus RTU - RS485
Wire Wire Line
	8300 3700 8900 3700
Connection ~ 8900 3700
Wire Wire Line
	8900 3700 8900 4150
Wire Wire Line
	8300 3300 8900 3300
Wire Wire Line
	8300 3800 8450 3800
Wire Wire Line
	7800 3800 7450 3800
Wire Wire Line
	8300 3600 8900 3600
Connection ~ 8900 3600
Wire Wire Line
	8900 3600 8900 3700
Wire Wire Line
	8900 3300 8900 3600
Wire Wire Line
	8450 4150 8450 4000
Wire Wire Line
	8200 4000 8450 4000
Connection ~ 8450 4000
Wire Wire Line
	8450 4000 8450 3800
Wire Wire Line
	8300 3500 8700 3500
Wire Wire Line
	8700 3500 8700 4150
Wire Wire Line
	8300 3200 8900 3200
Wire Wire Line
	8900 3200 8900 3300
Connection ~ 8900 3300
Text Label 8350 3700 0    50   ~ 0
GND
Text Label 8350 3300 0    50   ~ 0
GND
Text Label 8350 3200 0    50   ~ 0
GND
Text Notes 5250 3500 0    50   ~ 0
Master
$EndSCHEMATC
