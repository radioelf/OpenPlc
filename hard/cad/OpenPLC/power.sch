EESchema Schematic File Version 5
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 8 8
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
L Connector_Generic:Conn_01x02 J2
U 1 1 5D35C28D
P 1200 3400
F 0 "J2" H 1300 3400 50  0000 C CNN
F 1 "Conn_01x02" H 1150 3500 50  0000 C CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2_1x02_P5.00mm_Horizontal" H 1200 3400 50  0001 C CNN
F 3 "~" H 1200 3400 50  0001 C CNN
	1    1200 3400
	-1   0    0    1   
$EndComp
$Comp
L Device:D_Schottky D2
U 1 1 5D35CD46
P 3300 3300
F 0 "D2" H 3300 3084 50  0000 C CNN
F 1 "STPS1L30A" H 3300 3175 50  0000 C CNN
F 2 "Diode_SMD:D_SMA" H 3300 3300 50  0001 C CNN
F 3 "~" H 3300 3300 50  0001 C CNN
	1    3300 3300
	-1   0    0    1   
$EndComp
$Comp
L Device:Polyfuse F1
U 1 1 5D36544C
P 1800 3300
F 0 "F1" V 1575 3300 50  0000 C CNN
F 1 "PPTC- 250mA" V 1900 3400 50  0000 C CNN
F 2 "Fuse:Fuse_1206_3216Metric" H 1850 3100 50  0001 L CNN
F 3 "~" H 1800 3300 50  0001 C CNN
	1    1800 3300
	0    1    1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 5D366877
P 4100 3900
F 0 "C2" H 4215 3946 50  0000 L CNN
F 1 "100nF" H 4215 3855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4138 3750 50  0001 C CNN
F 3 "~" H 4100 3900 50  0001 C CNN
	1    4100 3900
	1    0    0    -1  
$EndComp
$Comp
L pspice:INDUCTOR L1
U 1 1 5D37A762
P 6750 3500
F 0 "L1" H 6750 3400 50  0000 C CNN
F 1 "47uH" H 6750 3624 50  0000 C CNN
F 2 "Inductor_SMD:L_12x12mm_H6mm" H 6750 3500 50  0001 C CNN
F 3 "" H 6750 3500 50  0001 C CNN
	1    6750 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1 C3
U 1 1 5D37B71B
P 7350 3900
F 0 "C3" H 7465 3946 50  0000 L CNN
F 1 "1000uF" H 7450 3800 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P3.50mm" H 7350 3900 50  0001 C CNN
F 3 "~" H 7350 3900 50  0001 C CNN
	1    7350 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5D37D774
P 5300 4650
F 0 "#PWR0102" H 5300 4400 50  0001 C CNN
F 1 "GND" H 5305 4477 50  0000 C CNN
F 2 "" H 5300 4650 50  0001 C CNN
F 3 "" H 5300 4650 50  0001 C CNN
	1    5300 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 3700 5300 4350
Wire Wire Line
	1600 4350 1600 3400
Wire Wire Line
	1600 3400 1400 3400
$Comp
L Device:D_TVS_uni D1
U 1 1 5D364A81
P 3000 3750
AR Path="/5D364A81" Ref="D1"  Part="1" 
AR Path="/5D3099EE/5D364A81" Ref="D1"  Part="1" 
F 0 "D1" V 2954 3829 50  0000 L CNN
F 1 "SMBJ36A" V 3045 3829 50  0000 L CNN
F 2 "duepi:DO-214AA" H 3000 3750 50  0001 C CNN
F 3 "~" H 3000 3750 50  0001 C CNN
	1    3000 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	3000 3900 3000 4350
Wire Wire Line
	3000 4350 3650 4350
Wire Wire Line
	3650 4050 3650 4350
Connection ~ 3650 4350
Wire Wire Line
	3650 4350 4100 4350
Wire Wire Line
	4100 4050 4100 4350
Connection ~ 4100 4350
Wire Wire Line
	4100 4350 4600 4350
Wire Wire Line
	4800 3300 4100 3300
Wire Wire Line
	3150 3300 3000 3300
Wire Wire Line
	1650 3300 1400 3300
Connection ~ 3000 3300
Wire Wire Line
	3650 3750 3650 3300
Connection ~ 3650 3300
Wire Wire Line
	3650 3300 3450 3300
Wire Wire Line
	4100 3750 4100 3300
Connection ~ 4100 3300
Wire Wire Line
	4100 3300 3650 3300
Wire Wire Line
	4800 3500 4600 3500
Wire Wire Line
	4600 3500 4600 4350
Connection ~ 4600 4350
Wire Wire Line
	4600 4350 5300 4350
Wire Wire Line
	6500 3500 6150 3500
Wire Wire Line
	6150 3750 6150 3500
Connection ~ 6150 3500
Wire Wire Line
	6150 3500 5800 3500
Wire Wire Line
	7350 4050 7350 4350
Connection ~ 5300 4350
Wire Wire Line
	6150 4050 6150 4350
Wire Wire Line
	5300 4350 6150 4350
Connection ~ 6150 4350
Wire Wire Line
	6150 4350 7350 4350
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5D380B83
P 3000 3050
F 0 "#FLG0101" H 3000 3125 50  0001 C CNN
F 1 "PWR_FLAG" H 3000 3223 50  0000 C CNN
F 2 "" H 3000 3050 50  0001 C CNN
F 3 "" H 3000 3050 50  0001 C CNN
	1    3000 3050
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5D381B95
P 1300 4200
F 0 "#FLG0103" H 1300 4275 50  0001 C CNN
F 1 "PWR_FLAG" H 1300 4373 50  0000 C CNN
F 2 "" H 1300 4200 50  0001 C CNN
F 3 "" H 1300 4200 50  0001 C CNN
	1    1300 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 4350 1300 4350
Wire Wire Line
	1300 4350 1300 4200
Wire Wire Line
	3000 3050 3000 3300
$Comp
L power:+24V #PWR0103
U 1 1 5D382652
P 3650 3050
F 0 "#PWR0103" H 3650 2900 50  0001 C CNN
F 1 "+24V" H 3665 3223 50  0000 C CNN
F 2 "" H 3650 3050 50  0001 C CNN
F 3 "" H 3650 3050 50  0001 C CNN
	1    3650 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5D370829
P 7750 3900
F 0 "C4" H 7865 3946 50  0000 L CNN
F 1 "100nF" H 7865 3855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7788 3750 50  0001 C CNN
F 3 "~" H 7750 3900 50  0001 C CNN
	1    7750 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 4050 7750 4350
Wire Wire Line
	7750 4350 7350 4350
Connection ~ 7350 4350
Wire Wire Line
	7750 3500 7750 3750
Text HLabel 9700 4350 2    50   UnSpc ~ 0
GND
Text HLabel 9650 3100 2    50   Output ~ 0
+5V
$Comp
L power:+5V #PWR0101
U 1 1 5D37D12D
P 9400 2900
F 0 "#PWR0101" H 9400 2750 50  0001 C CNN
F 1 "+5V" H 9415 3073 50  0000 C CNN
F 2 "" H 9400 2900 50  0001 C CNN
F 3 "" H 9400 2900 50  0001 C CNN
	1    9400 2900
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Switching:LM2596S-5 U6
U 1 1 5D3AD686
P 5300 3400
F 0 "U6" H 5300 3767 50  0000 C CNN
F 1 "LM2596S-5" H 5300 3676 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-263-5_TabPin3" H 5350 3150 50  0001 L CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm2596.pdf" H 5300 3400 50  0001 C CNN
	1    5300 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_PMOS_GSD Q1
U 1 1 5D3D029D
P 8650 3200
F 0 "Q1" V 8993 3200 50  0000 C CNN
F 1 "DMG2305" V 8902 3200 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8850 3300 50  0001 C CNN
F 3 "~" H 8650 3200 50  0001 C CNN
	1    8650 3200
	0    -1   -1   0   
$EndComp
$Comp
L OpenPLC-rescue:Q_DUAL_PNP_DMMT5401-Device Q2
U 1 1 5D3D025B
P 8650 3650
F 0 "Q2" H 8250 3750 50  0000 L CNN
F 1 "DMMT5401" H 8000 3600 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 8650 3650 50  0001 C CIN
F 3 "~" H 8550 3650 50  0001 L CNN
	1    8650 3650
	1    0    0    -1  
$EndComp
$Comp
L OpenPLC-rescue:D_TVS-Device D28
U 1 1 5D4074F9
P 9400 3650
AR Path="/5D4074F9" Ref="D28"  Part="1" 
AR Path="/5D3099EE/5D4074F9" Ref="D28"  Part="1" 
F 0 "D28" V 9354 3729 50  0000 L CNN
F 1 "PESD0402-140" V 9445 3729 50  0000 L CNN
F 2 "Diode_SMD:D_0402_1005Metric" H 9400 3650 50  0001 C CNN
F 3 "~" H 9400 3650 50  0001 C CNN
	1    9400 3650
	0    1    1    0   
$EndComp
$Comp
L pspice:INDUCTOR L3
U 1 1 5D40E658
P 2400 3300
F 0 "L3" H 2400 3515 50  0000 C CNN
F 1 "10uH" H 2400 3424 50  0000 C CNN
F 2 "Inductor_THT:L_Axial_L5.3mm_D2.2mm_P10.16mm_Horizontal_Vishay_IM-1" H 2400 3300 50  0001 C CNN
F 3 "" H 2400 3300 50  0001 C CNN
	1    2400 3300
	1    0    0    -1  
$EndComp
$Comp
L pspice:INDUCTOR L4
U 1 1 5D40ED6A
P 2400 4350
F 0 "L4" H 2400 4169 50  0000 C CNN
F 1 "10uH" H 2400 4260 50  0000 C CNN
F 2 "Inductor_THT:L_Axial_L5.3mm_D2.2mm_P10.16mm_Horizontal_Vishay_IM-1" H 2400 4350 50  0001 C CNN
F 3 "" H 2400 4350 50  0001 C CNN
	1    2400 4350
	-1   0    0    1   
$EndComp
$Comp
L Device:R R68
U 1 1 5D4170B2
P 8450 4100
F 0 "R68" H 8520 4146 50  0000 L CNN
F 1 "47K" H 8520 4055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8380 4100 50  0001 C CNN
F 3 "~" H 8450 4100 50  0001 C CNN
	1    8450 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R69
U 1 1 5D417705
P 8850 4100
F 0 "R69" H 8920 4146 50  0000 L CNN
F 1 "47K" H 8920 4055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8780 4100 50  0001 C CNN
F 3 "~" H 8850 4100 50  0001 C CNN
	1    8850 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 3850 8700 3900
Wire Wire Line
	8700 3900 8600 3900
Wire Wire Line
	8450 3900 8450 3950
Wire Wire Line
	8450 3850 8450 3900
Connection ~ 8450 3900
Wire Wire Line
	8600 3850 8600 3900
Connection ~ 8600 3900
Wire Wire Line
	8600 3900 8450 3900
Wire Wire Line
	8850 3850 8850 3900
Wire Wire Line
	8850 4250 8850 4350
Wire Wire Line
	8850 4350 8450 4350
Wire Wire Line
	8450 4350 8450 4250
Wire Wire Line
	3000 3300 2650 3300
Wire Wire Line
	3000 4350 2650 4350
Connection ~ 3000 4350
Wire Wire Line
	2150 3300 1950 3300
Wire Wire Line
	2150 4350 1600 4350
Connection ~ 1600 4350
Wire Wire Line
	7350 3500 7750 3500
Connection ~ 7350 3500
Wire Wire Line
	7350 3500 7350 3750
Wire Wire Line
	7000 3500 7350 3500
Wire Wire Line
	8450 3100 8400 3100
Wire Wire Line
	7750 3100 7750 3300
Connection ~ 7750 3500
Wire Wire Line
	5800 3300 7750 3300
Connection ~ 7750 3300
Wire Wire Line
	7750 3300 7750 3500
Wire Wire Line
	8650 3400 9050 3400
Wire Wire Line
	9050 3400 9050 3900
Wire Wire Line
	9050 3900 8850 3900
Connection ~ 8850 3900
Wire Wire Line
	8850 3900 8850 3950
Wire Wire Line
	8450 4350 7750 4350
Connection ~ 8450 4350
Connection ~ 7750 4350
Wire Wire Line
	8850 4350 9400 4350
Wire Wire Line
	9400 4350 9400 3800
Connection ~ 8850 4350
Wire Wire Line
	8850 3100 8900 3100
Wire Wire Line
	9400 3100 9400 3500
Wire Wire Line
	5300 4350 5300 4650
Wire Wire Line
	8850 3450 8850 3250
Wire Wire Line
	8850 3250 8900 3250
Wire Wire Line
	8900 3250 8900 3100
Connection ~ 8900 3100
Wire Wire Line
	8900 3100 9400 3100
Wire Wire Line
	8450 3450 8450 3250
Wire Wire Line
	8450 3250 8400 3250
Wire Wire Line
	8400 3250 8400 3100
Connection ~ 8400 3100
Wire Wire Line
	8400 3100 7750 3100
Wire Wire Line
	3650 3150 3650 3300
Wire Wire Line
	3650 3050 3650 3150
Connection ~ 3650 3150
Wire Wire Line
	3800 3150 3650 3150
Text HLabel 3800 3150 2    50   Output ~ 0
+24V
Text Label 9100 3100 0    50   ~ 0
+5v
Wire Wire Line
	9400 2900 9400 3100
Connection ~ 9400 3100
Wire Wire Line
	9650 3100 9400 3100
Wire Wire Line
	9700 4350 9400 4350
Connection ~ 9400 4350
Text Label 9100 4350 0    50   ~ 0
GND
Text Label 3750 3300 0    50   ~ 0
+24V
$Comp
L Device:CP1 C1
U 1 1 5D365E48
P 3650 3900
F 0 "C1" H 3765 3946 50  0000 L CNN
F 1 "100uF 50V" H 3250 3750 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P3.50mm" H 3650 3900 50  0001 C CNN
F 3 "~" H 3650 3900 50  0001 C CNN
	1    3650 3900
	1    0    0    -1  
$EndComp
Text Notes 8550 6900 0    50   ~ 0
Fuente  alimentación
$Comp
L Diode:1N5819 D3
U 1 1 5D37AE84
P 6150 3900
F 0 "D3" V 6104 3979 50  0000 L CNN
F 1 "SS34" V 6195 3979 50  0000 L CNN
F 2 "Diode_SMD:D_SMA" H 6150 3725 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88525/1n5817.pdf" H 6150 3900 50  0001 C CNN
	1    6150 3900
	0    1    1    0   
$EndComp
Text Notes 1550 3200 0    50   ~ 0
nSMD025-30V
Wire Wire Line
	3000 3300 3000 3650
$EndSCHEMATC
