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
Sheet 2 2
Title "RLCSv3"
Date "2019-10-27"
Rev "C"
Comp "Waterloo Rocketry Team"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 2250 3300 0    60   Input ~ 0
PWR
Text HLabel 2250 5100 0    60   Input ~ 0
SEL
$Comp
L MMBF170 Q1
U 1 1 596A66C7
P 3250 3250
F 0 "Q1" H 3450 3325 50  0000 L CNN
F 1 "MMBF170" H 3450 3250 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 3450 3175 50  0001 L CIN
F 3 "" H 3250 3250 50  0001 L CNN
	1    3250 3250
	1    0    0    -1  
$EndComp
$Comp
L MMBF170 Q2
U 1 1 596A6703
P 3250 5050
F 0 "Q2" H 3450 5125 50  0000 L CNN
F 1 "MMBF170" H 3450 5050 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 3450 4975 50  0001 L CIN
F 3 "" H 3250 5050 50  0001 L CNN
	1    3250 5050
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 596A6767
P 2650 3550
F 0 "R3" V 2730 3550 50  0000 C CNN
F 1 "10K" V 2650 3550 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2800 3050 50  0000 C CNN
F 3 "" H 2650 3550 50  0001 C CNN
	1    2650 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 5100 2650 5250
Connection ~ 2650 5100
Wire Wire Line
	2650 3300 2650 3400
Connection ~ 2650 3300
$Comp
L GND #PWR010
U 1 1 596A67F7
P 3350 3450
F 0 "#PWR010" H 3350 3200 50  0001 C CNN
F 1 "GND" H 3350 3300 50  0000 C CNN
F 2 "" H 3350 3450 50  0001 C CNN
F 3 "" H 3350 3450 50  0001 C CNN
	1    3350 3450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 596A682C
P 2650 5550
F 0 "#PWR011" H 2650 5300 50  0001 C CNN
F 1 "GND" H 2650 5400 50  0000 C CNN
F 2 "" H 2650 5550 50  0001 C CNN
F 3 "" H 2650 5550 50  0001 C CNN
	1    2650 5550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 596A6843
P 2650 3700
F 0 "#PWR012" H 2650 3450 50  0001 C CNN
F 1 "GND" H 2650 3550 50  0000 C CNN
F 2 "" H 2650 3700 50  0001 C CNN
F 3 "" H 2650 3700 50  0001 C CNN
	1    2650 3700
	1    0    0    -1  
$EndComp
$Comp
L SPST_POWER_RELAY U1
U 1 1 596A68BA
P 4000 2650
F 0 "U1" H 4200 2100 60  0000 C CNN
F 1 "SPST_POWER_RELAY" H 4000 2650 60  0000 C CNN
F 2 "custom:Relay_SPST_G5LE-1A" H 4000 2650 60  0001 C CNN
F 3 "" H 4000 2650 60  0001 C CNN
	1    4000 2650
	1    0    0    -1  
$EndComp
$Comp
L dpdt_relay U2
U 1 1 596A6A01
P 4900 3500
F 0 "U2" H 5250 2900 60  0000 C CNN
F 1 "dpdt_relay" H 4900 3500 60  0000 C CNN
F 2 "custom:Relay_DPDT_RT424012F" H 4900 3500 60  0001 C CNN
F 3 "" H 4900 3500 60  0001 C CNN
	1    4900 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 596A6B95
P 4450 3750
F 0 "#PWR013" H 4450 3500 50  0001 C CNN
F 1 "GND" H 4450 3600 50  0000 C CNN
F 2 "" H 4450 3750 50  0001 C CNN
F 3 "" H 4450 3750 50  0001 C CNN
	1    4450 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2850 4700 2850
$Comp
L R R5
U 1 1 596A6EAC
P 7100 3650
F 0 "R5" V 7180 3650 50  0000 C CNN
F 1 "0.02" V 7100 3650 50  0000 C CNN
F 2 "Resistors_SMD:R_2512_HandSoldering" V 7030 3650 50  0001 C CNN
F 3 "" H 7100 3650 50  0001 C CNN
	1    7100 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	5350 3650 6950 3650
Wire Wire Line
	5350 3750 7700 3750
Text HLabel 8950 3650 2    60   Input ~ 0
P1
Text HLabel 8950 3750 2    60   Input ~ 0
P2
Text HLabel 8950 3850 2    60   Input ~ 0
G1
Text HLabel 8950 3950 2    60   Input ~ 0
G2
Wire Wire Line
	7250 3650 8950 3650
Wire Wire Line
	8000 3750 8950 3750
Wire Wire Line
	8050 3100 8050 3750
Connection ~ 8050 3750
Wire Wire Line
	7400 3650 7400 2150
Connection ~ 7400 3650
Wire Wire Line
	6850 3650 6850 1950
Wire Wire Line
	6850 1950 7400 1950
Connection ~ 6850 3650
Wire Wire Line
	7600 3750 7600 2900
Wire Wire Line
	7600 2900 8050 2900
Connection ~ 7600 3750
$Comp
L +5V #PWR014
U 1 1 596A74A8
P 7600 1300
F 0 "#PWR014" H 7600 1150 50  0001 C CNN
F 1 "+5V" H 7600 1440 50  0000 C CNN
F 2 "" H 7600 1300 50  0001 C CNN
F 3 "" H 7600 1300 50  0001 C CNN
	1    7600 1300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 596A7503
P 7600 2350
F 0 "#PWR015" H 7600 2100 50  0001 C CNN
F 1 "GND" H 7600 2200 50  0000 C CNN
F 2 "" H 7600 2350 50  0001 C CNN
F 3 "" H 7600 2350 50  0001 C CNN
	1    7600 2350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 596A7533
P 8250 3300
F 0 "#PWR016" H 8250 3050 50  0001 C CNN
F 1 "GND" H 8250 3150 50  0000 C CNN
F 2 "" H 8250 3300 50  0001 C CNN
F 3 "" H 8250 3300 50  0001 C CNN
	1    8250 3300
	1    0    0    -1  
$EndComp
Text HLabel 8950 3000 2    60   Input ~ 0
CS2
Text HLabel 8950 2050 2    60   Input ~ 0
CS1
Wire Wire Line
	8000 2050 8950 2050
Wire Wire Line
	8650 3000 8950 3000
$Comp
L C C1
U 1 1 596A5ACA
P 7750 1550
F 0 "C1" V 7800 1600 50  0000 L CNN
F 1 "0.1uF" V 7600 1500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 7788 1400 50  0001 C CNN
F 3 "" H 7750 1550 50  0001 C CNN
	1    7750 1550
	0    1    1    0   
$EndComp
Wire Wire Line
	3350 2850 3500 2850
Wire Wire Line
	4450 3650 4450 3050
$Comp
L GND #PWR017
U 1 1 596A634A
P 3350 5250
F 0 "#PWR017" H 3350 5000 50  0001 C CNN
F 1 "GND" H 3350 5100 50  0000 C CNN
F 2 "" H 3350 5250 50  0001 C CNN
F 3 "" H 3350 5250 50  0001 C CNN
	1    3350 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 3050 3500 3050
$Comp
L +12V #PWR018
U 1 1 596A63B0
P 5400 4500
F 0 "#PWR018" H 5400 4350 50  0001 C CNN
F 1 "+12V" H 5400 4640 50  0000 C CNN
F 2 "" H 5400 4500 50  0001 C CNN
F 3 "" H 5400 4500 50  0001 C CNN
	1    5400 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 4500 5400 4500
Wire Wire Line
	5350 3850 8950 3850
Wire Wire Line
	8950 3950 5350 3950
$Comp
L R R4
U 1 1 596D9FD1
P 2650 5400
F 0 "R4" V 2730 5400 50  0000 C CNN
F 1 "10K" V 2650 5400 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2800 4900 50  0001 C CNN
F 3 "" H 2650 5400 50  0001 C CNN
	1    2650 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 4850 3350 4500
Wire Wire Line
	3350 4500 4750 4500
Wire Wire Line
	7600 1300 7600 1750
$Comp
L GND #PWR019
U 1 1 596DCE68
P 8000 1550
F 0 "#PWR019" H 8000 1300 50  0001 C CNN
F 1 "GND" H 8000 1400 50  0000 C CNN
F 2 "" H 8000 1550 50  0001 C CNN
F 3 "" H 8000 1550 50  0001 C CNN
	1    8000 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 1550 8000 1550
Connection ~ 7600 1550
$Comp
L +5V #PWR020
U 1 1 596DDA1B
P 8250 2250
F 0 "#PWR020" H 8250 2100 50  0001 C CNN
F 1 "+5V" H 8250 2390 50  0000 C CNN
F 2 "" H 8250 2250 50  0001 C CNN
F 3 "" H 8250 2250 50  0001 C CNN
	1    8250 2250
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 596DDA21
P 8400 2500
F 0 "C2" V 8450 2550 50  0000 L CNN
F 1 "0.1uF" V 8250 2450 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8438 2350 50  0001 C CNN
F 3 "" H 8400 2500 50  0001 C CNN
	1    8400 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	8250 2250 8250 2700
$Comp
L GND #PWR021
U 1 1 596DDA29
P 8650 2500
F 0 "#PWR021" H 8650 2250 50  0001 C CNN
F 1 "GND" H 8650 2350 50  0000 C CNN
F 2 "" H 8650 2500 50  0001 C CNN
F 3 "" H 8650 2500 50  0001 C CNN
	1    8650 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 2500 8650 2500
Connection ~ 8250 2500
$Comp
L R R6
U 1 1 596A6EF1
P 7850 3750
F 0 "R6" V 7930 3750 50  0000 C CNN
F 1 "0.02" V 7850 3750 50  0000 C CNN
F 2 "Resistors_SMD:R_2512_HandSoldering" V 7780 3750 50  0001 C CNN
F 3 "" H 7850 3750 50  0001 C CNN
	1    7850 3750
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 59753AC9
P 2450 5100
F 0 "R2" V 2550 5100 50  0000 C CNN
F 1 "150" V 2450 5100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2380 5100 50  0001 C CNN
F 3 "" H 2450 5100 50  0000 C CNN
	1    2450 5100
	0    1    1    0   
$EndComp
Wire Wire Line
	2250 5100 2300 5100
Wire Wire Line
	2600 5100 3050 5100
$Comp
L R R1
U 1 1 59753FE7
P 2450 3300
F 0 "R1" V 2550 3300 50  0000 C CNN
F 1 "150" V 2450 3300 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2380 3300 50  0001 C CNN
F 3 "" H 2450 3300 50  0000 C CNN
	1    2450 3300
	0    1    1    0   
$EndComp
Wire Wire Line
	2250 3300 2300 3300
Wire Wire Line
	2600 3300 3050 3300
Text HLabel 4700 2850 2    60   Input ~ 0
VIN
Wire Wire Line
	2250 2500 3350 2500
Wire Wire Line
	3350 2500 3350 2850
$Comp
L +12V #PWR022
U 1 1 5976F798
P 2250 2500
F 0 "#PWR022" H 2250 2350 50  0001 C CNN
F 1 "+12V" H 2250 2640 50  0000 C CNN
F 2 "" H 2250 2500 50  0000 C CNN
F 3 "" H 2250 2500 50  0000 C CNN
	1    2250 2500
	1    0    0    -1  
$EndComp
$Comp
L MCP601 U4
U 1 1 5978F0C9
P 8350 3000
F 0 "U4" H 8400 3200 50  0000 C CNN
F 1 "INA180A1" H 8550 2800 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5_HandSoldering" H 8300 3100 50  0001 C CNN
F 3 "" H 8400 3200 50  0000 C CNN
	1    8350 3000
	1    0    0    -1  
$EndComp
$Comp
L MCP601 U3
U 1 1 5978FE7D
P 7700 2050
F 0 "U3" H 7750 2250 50  0000 C CNN
F 1 "INA180A1" H 7900 1850 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5_HandSoldering" H 7650 2150 50  0001 C CNN
F 3 "" H 7750 2250 50  0000 C CNN
	1    7700 2050
	1    0    0    -1  
$EndComp
$Comp
L D D1
U 1 1 5A5EA1E1
P 3150 2900
F 0 "D1" H 3150 3000 50  0000 C CNN
F 1 "D" H 3150 2800 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 3150 2900 50  0001 C CNN
F 3 "" H 3150 2900 50  0001 C CNN
	1    3150 2900
	0    1    1    0   
$EndComp
$Comp
L D D2
U 1 1 5A5EA2DD
P 4900 4625
F 0 "D2" H 4900 4725 50  0000 C CNN
F 1 "D" H 4900 4525 50  0000 C CNN
F 2 "Diodes_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4900 4625 50  0001 C CNN
F 3 "" H 4900 4625 50  0001 C CNN
	1    4900 4625
	-1   0    0    1   
$EndComp
Wire Wire Line
	4750 4500 4750 4625
Wire Wire Line
	5050 4625 5050 4500
Connection ~ 3350 3050
Wire Wire Line
	3150 2750 3350 2750
Connection ~ 3350 2750
$EndSCHEMATC
