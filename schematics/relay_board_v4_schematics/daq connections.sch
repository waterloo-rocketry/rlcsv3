EESchema Schematic File Version 2
LIBS:rlcsv2_modular-rescue
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:custom
LIBS:rlcsv2_modular-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 11
Title "RLCSv2"
Date "2017-07-09"
Rev "C"
Comp "Waterloo Rocketry Team"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_01X03 J9
U 1 1 596A759A
P 4100 3950
F 0 "J9" H 4100 4150 50  0000 C CNN
F 1 "PRESSURE_2" V 4200 3950 50  0000 C CNN
F 2 "custom:2.54mm_pitch_1.3mm_hole_1x3_socket" H 4100 3950 50  0001 C CNN
F 3 "" H 4100 3950 50  0001 C CNN
	1    4100 3950
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR017
U 1 1 596A7632
P 4500 2450
F 0 "#PWR017" H 4500 2300 50  0001 C CNN
F 1 "+5V" H 4500 2590 50  0000 C CNN
F 2 "" H 4500 2450 50  0001 C CNN
F 3 "" H 4500 2450 50  0001 C CNN
	1    4500 2450
	1    0    0    -1  
$EndComp
$Comp
L +15V #PWR018
U 1 1 596A7652
P 4500 3150
F 0 "#PWR018" H 4500 3000 50  0001 C CNN
F 1 "+15V" H 4500 3290 50  0000 C CNN
F 2 "" H 4500 3150 50  0001 C CNN
F 3 "" H 4500 3150 50  0001 C CNN
	1    4500 3150
	1    0    0    -1  
$EndComp
$Comp
L +15V #PWR019
U 1 1 596A7670
P 4500 3850
F 0 "#PWR019" H 4500 3700 50  0001 C CNN
F 1 "+15V" H 4500 3990 50  0000 C CNN
F 2 "" H 4500 3850 50  0001 C CNN
F 3 "" H 4500 3850 50  0001 C CNN
	1    4500 3850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 596A7689
P 4500 4050
F 0 "#PWR020" H 4500 3800 50  0001 C CNN
F 1 "GND" H 4500 3900 50  0000 C CNN
F 2 "" H 4500 4050 50  0001 C CNN
F 3 "" H 4500 4050 50  0001 C CNN
	1    4500 4050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR021
U 1 1 596A76A7
P 4500 3350
F 0 "#PWR021" H 4500 3100 50  0001 C CNN
F 1 "GND" H 4500 3200 50  0000 C CNN
F 2 "" H 4500 3350 50  0001 C CNN
F 3 "" H 4500 3350 50  0001 C CNN
	1    4500 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 3350 4500 3350
Wire Wire Line
	4300 4050 4500 4050
Wire Wire Line
	4300 3850 4500 3850
Wire Wire Line
	4300 3150 4500 3150
Wire Wire Line
	4300 2450 4500 2450
$Comp
L GND #PWR022
U 1 1 596A76EB
P 4500 2650
F 0 "#PWR022" H 4500 2400 50  0001 C CNN
F 1 "GND" H 4500 2500 50  0000 C CNN
F 2 "" H 4500 2650 50  0001 C CNN
F 3 "" H 4500 2650 50  0001 C CNN
	1    4500 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 2650 4500 2650
Wire Wire Line
	4300 3250 6550 3250
Wire Wire Line
	4300 2550 5200 2550
Wire Wire Line
	5200 2550 5200 3100
Wire Wire Line
	5200 3100 6550 3100
Wire Wire Line
	4300 3950 5200 3950
Wire Wire Line
	5200 3950 5200 3400
Wire Wire Line
	5200 3400 6550 3400
Text Notes 7150 3850 1    60   ~ 0
DAQ connections to arduino\n
Text Notes 3800 4050 1    60   ~ 0
Connections going out to sensors\n
$Comp
L CONN_01X03 J7
U 1 1 596DB4D6
P 4100 2550
F 0 "J7" H 4100 2750 50  0000 C CNN
F 1 "MASS" V 4200 2550 50  0000 C CNN
F 2 "custom:2.54mm_pitch_1.3mm_hole_1x3_socket" H 4100 2550 50  0001 C CNN
F 3 "" H 4100 2550 50  0001 C CNN
	1    4100 2550
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X03 J8
U 1 1 596DB500
P 4100 3250
F 0 "J8" H 4100 3450 50  0000 C CNN
F 1 "PRESSURE_1" V 4200 3250 50  0000 C CNN
F 2 "custom:2.54mm_pitch_1.3mm_hole_1x3_socket" H 4100 3250 50  0001 C CNN
F 3 "" H 4100 3250 50  0001 C CNN
	1    4100 3250
	-1   0    0    1   
$EndComp
Text GLabel 6550 3100 2    60   Input ~ 0
DAQ_MASS
Text GLabel 6550 3250 2    60   Input ~ 0
DAQ_P1
Text GLabel 6550 3400 2    60   Input ~ 0
DAQ_P2
$EndSCHEMATC
