EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "RLCSv3"
Date "2019-10-27"
Rev "C"
Comp "Waterloo Rocketry Team"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L rlcsv3_modular-rescue:+12V #PWR06
U 1 1 597CBB0B
P 7850 950
F 0 "#PWR06" H 7850 800 50  0001 C CNN
F 1 "+12V" H 7850 1090 50  0000 C CNN
F 2 "" H 7850 950 50  0000 C CNN
F 3 "" H 7850 950 50  0000 C CNN
	1    7850 950 
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:+5V #PWR07
U 1 1 597CBB65
P 8200 950
F 0 "#PWR07" H 8200 800 50  0001 C CNN
F 1 "+5V" H 8200 1090 50  0000 C CNN
F 2 "" H 8200 950 50  0000 C CNN
F 3 "" H 8200 950 50  0000 C CNN
	1    8200 950 
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:GND #PWR04
U 1 1 5DD8888A
P 5700 800
F 0 "#PWR04" H 5700 550 50  0001 C CNN
F 1 "GND" H 5700 650 50  0000 C CNN
F 2 "" H 5700 800 50  0000 C CNN
F 3 "" H 5700 800 50  0000 C CNN
	1    5700 800 
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:+12V #PWR03
U 1 1 5DD80B39
P 5400 900
F 0 "#PWR03" H 5400 750 50  0001 C CNN
F 1 "+12V" H 5400 1040 50  0000 C CNN
F 2 "" H 5400 900 50  0000 C CNN
F 3 "" H 5400 900 50  0000 C CNN
	1    5400 900 
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:+5V #PWR02
U 1 1 5DD80B33
P 5200 900
F 0 "#PWR02" H 5200 750 50  0001 C CNN
F 1 "+5V" H 5200 1040 50  0000 C CNN
F 2 "" H 5200 900 50  0000 C CNN
F 3 "" H 5200 900 50  0000 C CNN
	1    5200 900 
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:CONN_01x05 U5
U 1 1 5DD7AFDF
P 4850 1500
F 0 "U5" H 4938 1375 60  0000 L CNN
F 1 "CONN_01x05" H 4938 1269 60  0000 L CNN
F 2 "rlcs:2.54mm_pitch_1.3mm_hole_1x3_socket" H 4850 1600 60  0001 C CNN
F 3 "" H 4850 1600 60  0001 C CNN
	1    4850 1500
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x05_Female J?
U 1 1 5DFBEBF4
P 1600 1200
AR Path="/5DCB71CA/5DFBEBF4" Ref="J?"  Part="1" 
AR Path="/5DFBEBF4" Ref="J1"  Part="1" 
F 0 "J1" H 1628 1226 50  0000 L CNN
F 1 "Programming Header" H 1628 1135 50  0000 L CNN
F 2 "rlcs:PinHeader_5x2.54_SMD_90deg_952-3198-1-ND" H 1600 1200 50  0001 C CNN
F 3 "~" H 1600 1200 50  0001 C CNN
	1    1600 1200
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5DFBEBFA
P 2290 860
AR Path="/5DCB71CA/5DFBEBFA" Ref="#PWR?"  Part="1" 
AR Path="/5DFBEBFA" Ref="#PWR011"  Part="1" 
F 0 "#PWR011" H 2290 710 50  0001 C CNN
F 1 "+5V" H 2305 1033 50  0000 C CNN
F 2 "" H 2290 860 50  0001 C CNN
F 3 "" H 2290 860 50  0001 C CNN
	1    2290 860 
	1    0    0    -1  
$EndComp
Text Label 2500 1100 0    60   ~ 0
~MCLR
Wire Wire Line
	2290 860  2290 1000
Wire Wire Line
	2290 1000 1800 1000
Wire Wire Line
	1800 1100 2500 1100
$Comp
L power:GND #PWR?
U 1 1 5DFBEC04
P 2290 1480
AR Path="/5DCB71CA/5DFBEC04" Ref="#PWR?"  Part="1" 
AR Path="/5DFBEC04" Ref="#PWR012"  Part="1" 
F 0 "#PWR012" H 2290 1230 50  0001 C CNN
F 1 "GND" H 2295 1307 50  0000 C CNN
F 2 "" H 2290 1480 50  0001 C CNN
F 3 "" H 2290 1480 50  0001 C CNN
	1    2290 1480
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 1200 2290 1200
Wire Wire Line
	2290 1200 2290 1480
Text Label 2500 1300 0    60   ~ 0
ICSPDAT
Text Label 2500 1400 0    60   ~ 0
ICSPCLK
Wire Wire Line
	1800 1300 2500 1300
Wire Wire Line
	1800 1400 2500 1400
Connection ~ 1400 2700
Wire Wire Line
	1400 2600 1400 2700
Wire Wire Line
	1500 2600 1400 2600
Connection ~ 1400 2800
Wire Wire Line
	1400 2700 1400 2800
Wire Wire Line
	1500 2700 1400 2700
Wire Wire Line
	1400 2900 1400 3000
Connection ~ 1400 2900
Wire Wire Line
	1400 2800 1400 2900
Wire Wire Line
	1500 2800 1400 2800
Wire Wire Line
	1500 2900 1400 2900
$Comp
L power:GND #PWR?
U 1 1 5DFBAF18
P 1400 3000
AR Path="/5DCB71CA/5DFBAF18" Ref="#PWR?"  Part="1" 
AR Path="/5DFBAF18" Ref="#PWR01"  Part="1" 
F 0 "#PWR01" H 1400 2750 50  0001 C CNN
F 1 "GND" H 1405 2827 50  0000 C CNN
F 2 "" H 1400 3000 50  0001 C CNN
F 3 "" H 1400 3000 50  0001 C CNN
	1    1400 3000
	1    0    0    -1  
$EndComp
Connection ~ 2100 2600
Wire Wire Line
	2300 2600 2100 2600
$Comp
L Device:R R?
U 1 1 5DFBAEF2
P 2100 2450
AR Path="/5DCB71CA/5DFBAEF2" Ref="R?"  Part="1" 
AR Path="/5DFBAEF2" Ref="R1"  Part="1" 
F 0 "R1" H 2170 2496 50  0000 L CNN
F 1 "10k" H 2170 2405 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2030 2450 50  0001 C CNN
F 3 "~" H 2100 2450 50  0001 C CNN
	1    2100 2450
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_DIP_x04 SW?
U 1 1 5DFBAEEC
P 1800 2800
AR Path="/5DCB71CA/5DFBAEEC" Ref="SW?"  Part="1" 
AR Path="/5DFBAEEC" Ref="SW1"  Part="1" 
F 0 "SW1" H 1800 3267 50  0000 C CNN
F 1 "SW_DIP_x04" H 1800 3176 50  0000 C CNN
F 2 "rlcs:DIP_SWITCH_4X2" H 1800 2800 50  0001 C CNN
F 3 "~" H 1800 2800 50  0001 C CNN
	1    1800 2800
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5DFBAED0
P 2100 2300
AR Path="/5DCB71CA/5DFBAED0" Ref="#PWR?"  Part="1" 
AR Path="/5DFBAED0" Ref="#PWR010"  Part="1" 
F 0 "#PWR010" H 2100 2150 50  0001 C CNN
F 1 "+5V" H 2115 2473 50  0000 C CNN
F 2 "" H 2100 2300 50  0001 C CNN
F 3 "" H 2100 2300 50  0001 C CNN
	1    2100 2300
	1    0    0    -1  
$EndComp
Text Label 5600 1400 0    60   ~ 0
SDA
Text Label 5600 1500 0    60   ~ 0
SCL
Wire Wire Line
	5200 900  5200 1100
Wire Wire Line
	5200 1100 5000 1100
Wire Wire Line
	5400 900  5400 1200
Wire Wire Line
	5400 1200 5000 1200
Wire Wire Line
	5000 1300 5600 1300
Wire Wire Line
	5600 1300 5600 700 
Wire Wire Line
	5600 700  5700 700 
Wire Wire Line
	5700 700  5700 800 
Wire Wire Line
	5000 1400 5600 1400
Wire Wire Line
	5000 1500 5600 1500
Text Notes 1550 3490 0    60   ~ 0
The dip switches are for physically setting\n a board "ID" or I2C address so that the software \nknows which board it's dealing with.
Wire Wire Line
	3400 2900 2100 2900
Wire Wire Line
	3500 2900 3400 2900
Text Label 2300 2600 0    60   ~ 0
DIP_1
Text Label 2700 2700 0    60   ~ 0
DIP_2
Text Label 3500 2900 0    60   ~ 0
DIP_4
Text Label 3100 2800 0    60   ~ 0
DIP_3
$Comp
L power:+5V #PWR?
U 1 1 5DFBAEDA
P 3000 2300
AR Path="/5DCB71CA/5DFBAEDA" Ref="#PWR?"  Part="1" 
AR Path="/5DFBAEDA" Ref="#PWR014"  Part="1" 
F 0 "#PWR014" H 3000 2150 50  0001 C CNN
F 1 "+5V" H 3015 2473 50  0000 C CNN
F 2 "" H 3000 2300 50  0001 C CNN
F 3 "" H 3000 2300 50  0001 C CNN
	1    3000 2300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5DFBAEE0
P 3400 2300
AR Path="/5DCB71CA/5DFBAEE0" Ref="#PWR?"  Part="1" 
AR Path="/5DFBAEE0" Ref="#PWR015"  Part="1" 
F 0 "#PWR015" H 3400 2150 50  0001 C CNN
F 1 "+5V" H 3415 2473 50  0000 C CNN
F 2 "" H 3400 2300 50  0001 C CNN
F 3 "" H 3400 2300 50  0001 C CNN
	1    3400 2300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5DFBAEE6
P 2600 2300
AR Path="/5DCB71CA/5DFBAEE6" Ref="#PWR?"  Part="1" 
AR Path="/5DFBAEE6" Ref="#PWR013"  Part="1" 
F 0 "#PWR013" H 2600 2150 50  0001 C CNN
F 1 "+5V" H 2615 2473 50  0000 C CNN
F 2 "" H 2600 2300 50  0001 C CNN
F 3 "" H 2600 2300 50  0001 C CNN
	1    2600 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DFBAEF8
P 3000 2450
AR Path="/5DCB71CA/5DFBAEF8" Ref="R?"  Part="1" 
AR Path="/5DFBAEF8" Ref="R3"  Part="1" 
F 0 "R3" H 3070 2496 50  0000 L CNN
F 1 "10k" H 3070 2405 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2930 2450 50  0001 C CNN
F 3 "~" H 3000 2450 50  0001 C CNN
	1    3000 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DFBAEFE
P 2600 2450
AR Path="/5DCB71CA/5DFBAEFE" Ref="R?"  Part="1" 
AR Path="/5DFBAEFE" Ref="R2"  Part="1" 
F 0 "R2" H 2670 2496 50  0000 L CNN
F 1 "10k" H 2670 2405 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2530 2450 50  0001 C CNN
F 3 "~" H 2600 2450 50  0001 C CNN
	1    2600 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DFBAF04
P 3400 2450
AR Path="/5DCB71CA/5DFBAF04" Ref="R?"  Part="1" 
AR Path="/5DFBAF04" Ref="R4"  Part="1" 
F 0 "R4" H 3470 2496 50  0000 L CNN
F 1 "10k" H 3470 2405 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3330 2450 50  0001 C CNN
F 3 "~" H 3400 2450 50  0001 C CNN
	1    3400 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 2700 2600 2700
Wire Wire Line
	2600 2700 2600 2600
Wire Wire Line
	2700 2700 2600 2700
Connection ~ 2600 2700
Wire Wire Line
	3000 2600 3000 2800
Wire Wire Line
	3000 2800 2100 2800
Wire Wire Line
	3100 2800 3000 2800
Connection ~ 3000 2800
Wire Wire Line
	3400 2600 3400 2900
Connection ~ 3400 2900
Wire Wire Line
	8200 950  8200 1050
Wire Wire Line
	7850 950  7850 1050
Wire Wire Line
	7500 1000 7500 1100
$Comp
L rlcsv3_modular-rescue:GND #PWR05
U 1 1 597CBAB1
P 7500 1100
F 0 "#PWR05" H 7500 850 50  0001 C CNN
F 1 "GND" H 7500 950 50  0000 C CNN
F 2 "" H 7500 1100 50  0000 C CNN
F 3 "" H 7500 1100 50  0000 C CNN
	1    7500 1100
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:TEST_1P TP0
U 1 1 597CB866
P 7500 1000
F 0 "TP0" H 7500 1270 50  0000 C CNN
F 1 "TEST_1P" H 7500 1200 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x01_Pitch2.54mm" H 7700 1000 50  0001 C CNN
F 3 "" H 7700 1000 50  0000 C CNN
	1    7500 1000
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:TEST_1P TP1
U 1 1 597CB649
P 7850 1050
F 0 "TP1" H 7850 1320 50  0000 C CNN
F 1 "TEST_1P" H 7850 1250 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x01_Pitch2.54mm" H 8050 1050 50  0001 C CNN
F 3 "" H 8050 1050 50  0000 C CNN
	1    7850 1050
	-1   0    0    1   
$EndComp
$Comp
L rlcsv3_modular-rescue:TEST_1P TP2
U 1 1 597CB557
P 8200 1050
F 0 "TP2" H 8200 1320 50  0000 C CNN
F 1 "TEST_1P" H 8200 1250 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x01_Pitch2.54mm" H 8400 1050 50  0001 C CNN
F 3 "" H 8400 1050 50  0000 C CNN
	1    8200 1050
	-1   0    0    1   
$EndComp
Text Label 6700 2400 0    60   ~ 0
CURR_SENSE_2
Text Label 6700 2250 0    60   ~ 0
CURR_SENSE_1
Text Label 4970 2700 2    60   ~ 0
~MCLR
$Comp
L Device:R R?
U 1 1 5DFA5AC0
P 5060 2450
AR Path="/5DCB71CA/5DFA5AC0" Ref="R?"  Part="1" 
AR Path="/5DFA5AC0" Ref="R13"  Part="1" 
F 0 "R13" H 5130 2496 50  0000 L CNN
F 1 "10K" H 5130 2405 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4990 2450 50  0001 C CNN
F 3 "~" H 5060 2450 50  0001 C CNN
	1    5060 2450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5DFA5ABA
P 5060 2300
AR Path="/5DCB71CA/5DFA5ABA" Ref="#PWR?"  Part="1" 
AR Path="/5DFA5ABA" Ref="#PWR021"  Part="1" 
F 0 "#PWR021" H 5060 2150 50  0001 C CNN
F 1 "+5V" H 5075 2473 50  0000 C CNN
F 2 "" H 5060 2300 50  0001 C CNN
F 3 "" H 5060 2300 50  0001 C CNN
	1    5060 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5220 2850 5220 2870
Text Label 5700 2550 2    60   ~ 0
DIP_1
Text Label 5700 3450 2    60   ~ 0
DIP_4
Text Label 5700 3300 2    60   ~ 0
DIP_3
Text Label 5700 3000 2    60   ~ 0
DIP_2
Wire Wire Line
	4970 2700 5060 2700
Wire Wire Line
	5060 2600 5060 2700
Wire Wire Line
	7960 2500 7870 2500
Wire Wire Line
	7960 2570 7960 2500
$Comp
L power:GND #PWR?
U 1 1 5DFA5AAB
P 7960 2570
AR Path="/5DCB71CA/5DFA5AAB" Ref="#PWR?"  Part="1" 
AR Path="/5DFA5AAB" Ref="#PWR027"  Part="1" 
F 0 "#PWR027" H 7960 2320 50  0001 C CNN
F 1 "GND" H 7965 2397 50  0000 C CNN
F 2 "" H 7960 2570 50  0001 C CNN
F 3 "" H 7960 2570 50  0001 C CNN
	1    7960 2570
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DFA5AA5
P 7720 2500
AR Path="/5DCB71CA/5DFA5AA5" Ref="C?"  Part="1" 
AR Path="/5DFA5AA5" Ref="C1"  Part="1" 
F 0 "C1" V 7913 2546 50  0000 L CNN
F 1 "22uF" V 7835 2455 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7758 2350 50  0001 C CNN
F 3 "~" H 7720 2500 50  0001 C CNN
	1    7720 2500
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DFA5A9D
P 5220 2870
AR Path="/5DCB71CA/5DFA5A9D" Ref="#PWR?"  Part="1" 
AR Path="/5DFA5A9D" Ref="#PWR022"  Part="1" 
F 0 "#PWR022" H 5220 2620 50  0001 C CNN
F 1 "GND" H 5225 2697 50  0000 C CNN
F 2 "" H 5220 2870 50  0001 C CNN
F 3 "" H 5220 2870 50  0001 C CNN
	1    5220 2870
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 2850 5220 2850
$Comp
L power:+5V #PWR?
U 1 1 5DFA5A84
P 7500 2300
AR Path="/5DCB71CA/5DFA5A84" Ref="#PWR?"  Part="1" 
AR Path="/5DFA5A84" Ref="#PWR026"  Part="1" 
F 0 "#PWR026" H 7500 2150 50  0001 C CNN
F 1 "+5V" H 7515 2473 50  0000 C CNN
F 2 "" H 7500 2300 50  0001 C CNN
F 3 "" H 7500 2300 50  0001 C CNN
	1    7500 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 2300 7500 2500
Wire Wire Line
	7500 2500 7570 2500
Text Label 6700 3000 0    60   ~ 0
ICSPDAT
Text Label 6700 3150 0    60   ~ 0
ICSPCLK
$Comp
L rlcsv3_modular-rescue:PIC16F1826-ISO U?
U 1 1 5DFA5A69
P 6200 2500
AR Path="/5DCB71CA/5DFA5A69" Ref="U?"  Part="1" 
AR Path="/5DFA5A69" Ref="U2"  Part="1" 
F 0 "U2" H 6200 3087 60  0000 C CNN
F 1 "PIC16F1826-ISO" H 6200 2981 60  0000 C CNN
F 2 "rlcs:PIC16F1826-ISO" H 6200 2950 60  0001 C CNN
F 3 "" H 6200 2950 60  0001 C CNN
	1    6200 2500
	1    0    0    -1  
$EndComp
Connection ~ 5060 2700
Wire Wire Line
	5060 2700 5700 2700
Text Label 5700 2250 2    60   ~ 0
POWER
Text Label 5700 2400 2    60   ~ 0
SELECT
Text Label 5700 3150 2    60   ~ 0
SDA
Text Label 6700 3450 0    60   ~ 0
SCL
Text Label 6700 2700 0    60   ~ 0
LIM2
Text Label 6700 2550 0    60   ~ 0
LIM1
$Comp
L rlcsv3_modular-rescue:MMBF170 Q1
U 1 1 5DFD4FB5
P 4690 5150
F 0 "Q1" H 4890 5225 50  0000 L CNN
F 1 "MMBF170" H 4890 5150 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 4890 5075 50  0001 L CIN
F 3 "" H 4690 5150 50  0001 L CNN
	1    4690 5150
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:MMBF170 Q2
U 1 1 5DFD4FBB
P 4690 6950
F 0 "Q2" H 4890 7025 50  0000 L CNN
F 1 "MMBF170" H 4890 6950 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 4890 6875 50  0001 L CIN
F 3 "" H 4690 6950 50  0001 L CNN
	1    4690 6950
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:R R11
U 1 1 5DFD4FC1
P 4090 5450
F 0 "R11" V 4170 5450 50  0000 C CNN
F 1 "10K" V 4090 5450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4240 4950 50  0000 C CNN
F 3 "" H 4090 5450 50  0001 C CNN
	1    4090 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4090 7000 4090 7150
Connection ~ 4090 7000
Wire Wire Line
	4090 5200 4090 5300
Connection ~ 4090 5200
$Comp
L rlcsv3_modular-rescue:GND #PWR019
U 1 1 5DFD4FCB
P 4790 5350
F 0 "#PWR019" H 4790 5100 50  0001 C CNN
F 1 "GND" H 4790 5200 50  0000 C CNN
F 2 "" H 4790 5350 50  0001 C CNN
F 3 "" H 4790 5350 50  0001 C CNN
	1    4790 5350
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:GND #PWR018
U 1 1 5DFD4FD1
P 4090 7450
F 0 "#PWR018" H 4090 7200 50  0001 C CNN
F 1 "GND" H 4090 7300 50  0000 C CNN
F 2 "" H 4090 7450 50  0001 C CNN
F 3 "" H 4090 7450 50  0001 C CNN
	1    4090 7450
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:GND #PWR017
U 1 1 5DFD4FD7
P 4090 5600
F 0 "#PWR017" H 4090 5350 50  0001 C CNN
F 1 "GND" H 4090 5450 50  0000 C CNN
F 2 "" H 4090 5600 50  0001 C CNN
F 3 "" H 4090 5600 50  0001 C CNN
	1    4090 5600
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:SPST_POWER_RELAY U1
U 1 1 5DFD4FDD
P 5440 4550
F 0 "U1" H 5640 4000 60  0000 C CNN
F 1 "SPST_POWER_RELAY" H 5440 4550 60  0000 C CNN
F 2 "custom:Relay_SPST_G5LE-1A" H 5440 4550 60  0001 C CNN
F 3 "" H 5440 4550 60  0001 C CNN
	1    5440 4550
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:dpdt_relay U3
U 1 1 5DFD4FE3
P 6340 5400
F 0 "U3" H 6690 4800 60  0000 C CNN
F 1 "dpdt_relay" H 6340 5400 60  0000 C CNN
F 2 "custom:Relay_DPDT_RT424012F" H 6340 5400 60  0001 C CNN
F 3 "" H 6340 5400 60  0001 C CNN
	1    6340 5400
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:GND #PWR023
U 1 1 5DFD4FE9
P 5890 5650
F 0 "#PWR023" H 5890 5400 50  0001 C CNN
F 1 "GND" H 5890 5500 50  0000 C CNN
F 2 "" H 5890 5650 50  0001 C CNN
F 3 "" H 5890 5650 50  0001 C CNN
	1    5890 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5890 4750 6140 4750
$Comp
L rlcsv3_modular-rescue:R R14
U 1 1 5DFD4FF0
P 8540 5550
F 0 "R14" V 8620 5550 50  0000 C CNN
F 1 "0.02" V 8540 5550 50  0000 C CNN
F 2 "Resistors_SMD:R_2512_HandSoldering" V 8470 5550 50  0001 C CNN
F 3 "" H 8540 5550 50  0001 C CNN
	1    8540 5550
	0    1    1    0   
$EndComp
Wire Wire Line
	6790 5550 8290 5550
Wire Wire Line
	6790 5650 9040 5650
Wire Wire Line
	8690 5550 8840 5550
Wire Wire Line
	9440 5650 9490 5650
Wire Wire Line
	9490 5000 9490 5650
Connection ~ 9490 5650
Wire Wire Line
	8840 5550 8840 4050
Connection ~ 8840 5550
Wire Wire Line
	8290 5550 8290 3850
Wire Wire Line
	8290 3850 8840 3850
Connection ~ 8290 5550
Wire Wire Line
	9040 5650 9040 4800
Wire Wire Line
	9040 4800 9490 4800
Connection ~ 9040 5650
$Comp
L rlcsv3_modular-rescue:+5V #PWR028
U 1 1 5DFD5008
P 9040 3200
F 0 "#PWR028" H 9040 3050 50  0001 C CNN
F 1 "+5V" H 9040 3340 50  0000 C CNN
F 2 "" H 9040 3200 50  0001 C CNN
F 3 "" H 9040 3200 50  0001 C CNN
	1    9040 3200
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:GND #PWR029
U 1 1 5DFD500E
P 9040 4250
F 0 "#PWR029" H 9040 4000 50  0001 C CNN
F 1 "GND" H 9040 4100 50  0000 C CNN
F 2 "" H 9040 4250 50  0001 C CNN
F 3 "" H 9040 4250 50  0001 C CNN
	1    9040 4250
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:GND #PWR032
U 1 1 5DFD5014
P 9690 5200
F 0 "#PWR032" H 9690 4950 50  0001 C CNN
F 1 "GND" H 9690 5050 50  0000 C CNN
F 2 "" H 9690 5200 50  0001 C CNN
F 3 "" H 9690 5200 50  0001 C CNN
	1    9690 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9440 3950 10390 3950
Wire Wire Line
	10090 4900 10390 4900
$Comp
L rlcsv3_modular-rescue:C C2
U 1 1 5DFD501E
P 9190 3450
F 0 "C2" V 9240 3500 50  0000 L CNN
F 1 "0.1uF" V 9040 3400 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9228 3300 50  0001 C CNN
F 3 "" H 9190 3450 50  0001 C CNN
	1    9190 3450
	0    1    1    0   
$EndComp
Wire Wire Line
	4790 4750 4940 4750
Wire Wire Line
	5890 5550 5890 4950
$Comp
L rlcsv3_modular-rescue:GND #PWR020
U 1 1 5DFD5026
P 4790 7150
F 0 "#PWR020" H 4790 6900 50  0001 C CNN
F 1 "GND" H 4790 7000 50  0000 C CNN
F 2 "" H 4790 7150 50  0001 C CNN
F 3 "" H 4790 7150 50  0001 C CNN
	1    4790 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4590 4950 4790 4950
$Comp
L rlcsv3_modular-rescue:+12V #PWR025
U 1 1 5DFD502D
P 6840 6400
F 0 "#PWR025" H 6840 6250 50  0001 C CNN
F 1 "+12V" H 6840 6540 50  0000 C CNN
F 2 "" H 6840 6400 50  0001 C CNN
F 3 "" H 6840 6400 50  0001 C CNN
	1    6840 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6490 6400 6840 6400
Wire Wire Line
	6790 5750 10390 5750
Wire Wire Line
	10390 5850 6790 5850
$Comp
L rlcsv3_modular-rescue:R R12
U 1 1 5DFD5036
P 4090 7300
F 0 "R12" V 4170 7300 50  0000 C CNN
F 1 "10K" V 4090 7300 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4240 6800 50  0001 C CNN
F 3 "" H 4090 7300 50  0001 C CNN
	1    4090 7300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4790 6750 4790 6400
Wire Wire Line
	4790 6400 6190 6400
Wire Wire Line
	9040 3200 9040 3450
$Comp
L rlcsv3_modular-rescue:GND #PWR030
U 1 1 5DFD503F
P 9440 3450
F 0 "#PWR030" H 9440 3200 50  0001 C CNN
F 1 "GND" H 9440 3300 50  0000 C CNN
F 2 "" H 9440 3450 50  0001 C CNN
F 3 "" H 9440 3450 50  0001 C CNN
	1    9440 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9340 3450 9440 3450
Connection ~ 9040 3450
$Comp
L rlcsv3_modular-rescue:+5V #PWR031
U 1 1 5DFD5047
P 9690 4150
F 0 "#PWR031" H 9690 4000 50  0001 C CNN
F 1 "+5V" H 9690 4290 50  0000 C CNN
F 2 "" H 9690 4150 50  0001 C CNN
F 3 "" H 9690 4150 50  0001 C CNN
	1    9690 4150
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:C C3
U 1 1 5DFD504D
P 9840 4400
F 0 "C3" V 9890 4450 50  0000 L CNN
F 1 "0.1uF" V 9690 4350 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 9878 4250 50  0001 C CNN
F 3 "" H 9840 4400 50  0001 C CNN
	1    9840 4400
	0    1    1    0   
$EndComp
Wire Wire Line
	9690 4150 9690 4400
$Comp
L rlcsv3_modular-rescue:GND #PWR033
U 1 1 5DFD5054
P 10090 4400
F 0 "#PWR033" H 10090 4150 50  0001 C CNN
F 1 "GND" H 10090 4250 50  0000 C CNN
F 2 "" H 10090 4400 50  0001 C CNN
F 3 "" H 10090 4400 50  0001 C CNN
	1    10090 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9990 4400 10090 4400
Connection ~ 9690 4400
$Comp
L rlcsv3_modular-rescue:R R15
U 1 1 5DFD505C
P 9290 5650
F 0 "R15" V 9370 5650 50  0000 C CNN
F 1 "0.02" V 9290 5650 50  0000 C CNN
F 2 "Resistors_SMD:R_2512_HandSoldering" V 9220 5650 50  0001 C CNN
F 3 "" H 9290 5650 50  0001 C CNN
	1    9290 5650
	0    1    1    0   
$EndComp
$Comp
L rlcsv3_modular-rescue:R R6
U 1 1 5DFD5062
P 3890 7000
F 0 "R6" V 3990 7000 50  0000 C CNN
F 1 "150" V 3890 7000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3820 7000 50  0001 C CNN
F 3 "" H 3890 7000 50  0000 C CNN
	1    3890 7000
	0    1    1    0   
$EndComp
Wire Wire Line
	3690 7000 3740 7000
Wire Wire Line
	4040 7000 4090 7000
$Comp
L rlcsv3_modular-rescue:R R5
U 1 1 5DFD506A
P 3890 5200
F 0 "R5" V 3990 5200 50  0000 C CNN
F 1 "150" V 3890 5200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3820 5200 50  0001 C CNN
F 3 "" H 3890 5200 50  0000 C CNN
	1    3890 5200
	0    1    1    0   
$EndComp
Wire Wire Line
	3690 5200 3740 5200
Wire Wire Line
	4040 5200 4090 5200
Wire Wire Line
	3690 4400 4790 4400
Wire Wire Line
	4790 4400 4790 4650
$Comp
L rlcsv3_modular-rescue:+12V #PWR016
U 1 1 5DFD5075
P 3690 4400
F 0 "#PWR016" H 3690 4250 50  0001 C CNN
F 1 "+12V" H 3690 4540 50  0000 C CNN
F 2 "" H 3690 4400 50  0000 C CNN
F 3 "" H 3690 4400 50  0000 C CNN
	1    3690 4400
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:MCP601 U6
U 1 1 5DFD507B
P 9790 4900
F 0 "U6" H 9840 5100 50  0000 C CNN
F 1 "INA180A1" H 9990 4700 50  0000 C CNN
F 2 "rlcs:DCDC-Conv_IV1215SA" H 9740 5000 50  0001 C CNN
F 3 "" H 9840 5100 50  0000 C CNN
	1    9790 4900
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:MCP601 U4
U 1 1 5DFD5081
P 9140 3950
F 0 "U4" H 9190 4150 50  0000 C CNN
F 1 "INA180A1" H 9340 3750 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5_HandSoldering" H 9090 4050 50  0001 C CNN
F 3 "" H 9190 4150 50  0000 C CNN
	1    9140 3950
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:D D1
U 1 1 5DFD5087
P 4590 4800
F 0 "D1" H 4590 4900 50  0000 C CNN
F 1 "D" H 4590 4700 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4590 4800 50  0001 C CNN
F 3 "" H 4590 4800 50  0001 C CNN
	1    4590 4800
	0    1    1    0   
$EndComp
$Comp
L rlcsv3_modular-rescue:D D2
U 1 1 5DFD508D
P 6340 6525
F 0 "D2" H 6340 6625 50  0000 C CNN
F 1 "D" H 6340 6425 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 6340 6525 50  0001 C CNN
F 3 "" H 6340 6525 50  0001 C CNN
	1    6340 6525
	-1   0    0    1   
$EndComp
Wire Wire Line
	6190 6400 6190 6525
Wire Wire Line
	6490 6525 6490 6400
Connection ~ 4790 4950
Wire Wire Line
	4590 4650 4790 4650
Connection ~ 4790 4650
Wire Wire Line
	4090 7000 4490 7000
Wire Wire Line
	4090 5200 4490 5200
Wire Wire Line
	9490 5650 10390 5650
Wire Wire Line
	8840 5550 10390 5550
Wire Wire Line
	8290 5550 8390 5550
Wire Wire Line
	9040 5650 9140 5650
Wire Wire Line
	9040 3450 9040 3650
Wire Wire Line
	9690 4400 9690 4600
Wire Wire Line
	4790 4950 4940 4950
Wire Wire Line
	4790 4650 4790 4750
Connection ~ 6190 6400
Connection ~ 6490 6400
Text Label 10390 3950 0    60   ~ 0
CURR_SENSE_1
Text Label 10390 4900 0    60   ~ 0
CURR_SENSE_2
Text Label 10390 5550 0    60   ~ 0
P1
Text Label 10390 5650 0    60   ~ 0
P2
Text Label 10390 5750 0    60   ~ 0
G1
Text Label 10390 5850 0    60   ~ 0
G2
$Comp
L rlcsv3_modular-rescue:CONN_01X02 P1
U 1 1 5E14F9E1
P 6990 4700
F 0 "P1" H 6990 4850 50  0000 C CNN
F 1 "ACT_PWR" V 7090 4700 50  0000 C CNN
F 2 "Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-2pol" H 6990 4700 50  0001 C CNN
F 3 "" H 6990 4700 50  0000 C CNN
	1    6990 4700
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:FUSE F1
U 1 1 5E14F9E7
P 6540 4750
F 0 "F1" H 6640 4800 50  0000 C CNN
F 1 "FUSE" H 6440 4700 50  0000 C CNN
F 2 "custom:littlefuse_01000020Z" H 6540 4750 50  0001 C CNN
F 3 "" H 6540 4750 50  0000 C CNN
	1    6540 4750
	-1   0    0    1   
$EndComp
$Comp
L rlcsv3_modular-rescue:GND #PWR024
U 1 1 5E14F9ED
P 6690 4400
F 0 "#PWR024" H 6690 4150 50  0001 C CNN
F 1 "GND" H 6690 4250 50  0000 C CNN
F 2 "" H 6690 4400 50  0000 C CNN
F 3 "" H 6690 4400 50  0000 C CNN
	1    6690 4400
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:TEST_1P TP3
U 1 1 5E14F9F3
P 6140 4750
F 0 "TP3" H 6140 5020 50  0000 C CNN
F 1 "TEST_1P" H 6140 4950 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x01_Pitch2.54mm" H 6340 4750 50  0001 C CNN
F 3 "" H 6340 4750 50  0000 C CNN
	1    6140 4750
	-1   0    0    1   
$EndComp
Wire Wire Line
	6290 4750 6140 4750
Connection ~ 6140 4750
Wire Wire Line
	6790 4650 6790 4350
Wire Wire Line
	6790 4350 6690 4350
Wire Wire Line
	6690 4350 6690 4400
Text Label 3690 5200 2    60   ~ 0
POWER
Text Label 3690 7000 2    60   ~ 0
SELECT
Wire Wire Line
	10200 2900 10200 3000
Connection ~ 10200 2400
Wire Wire Line
	10200 2400 10200 2600
Wire Wire Line
	10300 2400 10200 2400
Connection ~ 10000 2400
Wire Wire Line
	9900 2400 10000 2400
Wire Wire Line
	10400 2100 10200 2100
Wire Wire Line
	10000 2400 10000 2600
Wire Wire Line
	10000 2000 10400 2000
Wire Wire Line
	9200 1900 10400 1900
Wire Wire Line
	9200 1800 10400 1800
Wire Wire Line
	9200 1700 10400 1700
Wire Wire Line
	9200 1600 10400 1600
Text Label 10300 2400 0    60   ~ 0
LIM2
Text Label 9900 2400 2    60   ~ 0
LIM1
Text Label 9200 1900 2    60   ~ 0
G2
Text Label 9200 1800 2    60   ~ 0
G1
Text Label 9200 1700 2    60   ~ 0
P2
Text Label 9200 1600 2    60   ~ 0
P1
$Comp
L rlcsv3_modular-rescue:R R10
U 1 1 597CF0E0
P 10200 2750
F 0 "R10" V 10280 2750 50  0000 C CNN
F 1 "10K" V 10200 2750 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 10130 2750 50  0001 C CNN
F 3 "" H 10200 2750 50  0000 C CNN
	1    10200 2750
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:R R8
U 1 1 597CF29F
P 10000 2750
F 0 "R8" V 10080 2750 50  0000 C CNN
F 1 "10K" V 10000 2750 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 9930 2750 50  0001 C CNN
F 3 "" H 10000 2750 50  0000 C CNN
	1    10000 2750
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:R R7
U 1 1 597CF30F
P 10000 2250
F 0 "R7" V 10080 2250 50  0000 C CNN
F 1 "20K" V 10000 2250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 9930 2250 50  0001 C CNN
F 3 "" H 10000 2250 50  0000 C CNN
	1    10000 2250
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:GND #PWR08
U 1 1 597D0207
P 10000 3000
F 0 "#PWR08" H 10000 2750 50  0001 C CNN
F 1 "GND" H 10000 2850 50  0000 C CNN
F 2 "" H 10000 3000 50  0000 C CNN
F 3 "" H 10000 3000 50  0000 C CNN
	1    10000 3000
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:GND #PWR09
U 1 1 597D0273
P 10200 3000
F 0 "#PWR09" H 10200 2750 50  0001 C CNN
F 1 "GND" H 10200 2850 50  0000 C CNN
F 2 "" H 10200 3000 50  0000 C CNN
F 3 "" H 10200 3000 50  0000 C CNN
	1    10200 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 2100 10000 2000
Wire Wire Line
	10000 3000 10000 2900
$Comp
L rlcsv3_modular-rescue:R R9
U 1 1 597CF3BE
P 10200 2250
F 0 "R9" V 10280 2250 50  0000 C CNN
F 1 "20K" V 10200 2250 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 10130 2250 50  0001 C CNN
F 3 "" H 10200 2250 50  0000 C CNN
	1    10200 2250
	1    0    0    -1  
$EndComp
$Comp
L rlcsv3_modular-rescue:CONN_01X06 P3
U 1 1 597CE787
P 10600 1850
F 0 "P3" H 10600 2200 50  0000 C CNN
F 1 "ACTUATOR" V 10700 1850 50  0000 C CNN
F 2 "Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-6pol" H 10600 1850 50  0001 C CNN
F 3 "" H 10600 1850 50  0000 C CNN
	1    10600 1850
	1    0    0    1   
$EndComp
Wire Wire Line
	7500 2500 7000 2500
Wire Wire Line
	7000 2500 7000 2850
Wire Wire Line
	7000 2850 6700 2850
Connection ~ 7500 2500
$EndSCHEMATC
