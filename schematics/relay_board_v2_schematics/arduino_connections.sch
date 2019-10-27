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
Sheet 4 11
Title "RLCSv2"
Date "2017-07-09"
Rev "C"
Comp "Waterloo Rocketry Team"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 1450 6900 0    60   Output ~ 0
ARD_IGN_PWR
Text GLabel 1450 6750 0    60   Output ~ 0
ARD_IGN_SEL
Text GLabel 1450 5100 0    60   Output ~ 0
ARD_V1_PWR
Text GLabel 1450 4950 0    60   Output ~ 0
ARD_V1_DIR
Text GLabel 1450 4200 0    60   Output ~ 0
ARD_V2_PWR
Text GLabel 1450 4050 0    60   Output ~ 0
ARD_V2_DIR
Text GLabel 1450 6000 0    60   Output ~ 0
ARD_RD_PWR
Text GLabel 1450 5850 0    60   Output ~ 0
ARD_RD_DIR
Text GLabel 1450 6600 0    60   Output ~ 0
ARD_IGN_CS_1
Text GLabel 1450 6450 0    60   Output ~ 0
ARD_IGN_CS_2
Text GLabel 1450 4800 0    60   Output ~ 0
ARD_V1_CS_1
Text GLabel 1450 4650 0    60   Output ~ 0
ARD_V1_CS_2
Text GLabel 1450 3900 0    60   Output ~ 0
ARD_V2_CS_1
Text GLabel 1450 3750 0    60   Output ~ 0
ARD_V2_CS_2
Text GLabel 1450 5700 0    60   Output ~ 0
ARD_RD_CS_1
Text GLabel 1450 5550 0    60   Output ~ 0
ARD_RD_CS_2
Text GLabel 1450 5400 0    60   Output ~ 0
ARD_V1_LIM_1
Text GLabel 1450 5250 0    60   Output ~ 0
ARD_V1_LIM_2
Text GLabel 1450 4500 0    60   Output ~ 0
ARD_V2_LIM_1
Text GLabel 1450 4350 0    60   Output ~ 0
ARD_V2_LIM_2
Text GLabel 1450 6300 0    60   Output ~ 0
ARD_RD_LIM_1
Text GLabel 1450 6150 0    60   Output ~ 0
ARD_RD_LIM_2
Text GLabel 1450 800  0    60   Output ~ 0
ARD_PWR
Text GLabel 1450 650  0    60   Output ~ 0
ARD_GND
Text GLabel 1450 3300 0    60   Output ~ 0
ARD_V3_PWR
Text GLabel 1450 3150 0    60   Output ~ 0
ARD_V3_DIR
Text GLabel 1450 2400 0    60   Output ~ 0
ARD_V4_PWR
Text GLabel 1450 2250 0    60   Output ~ 0
ARD_V4_DIR
Text GLabel 1450 3000 0    60   Output ~ 0
ARD_V3_CS_1
Text GLabel 1450 2850 0    60   Output ~ 0
ARD_V3_CS_2
Text GLabel 1450 2100 0    60   Output ~ 0
ARD_V4_CS_1
Text GLabel 1450 1950 0    60   Output ~ 0
ARD_V4_CS_2
Text GLabel 1450 3600 0    60   Output ~ 0
ARD_V3_LIM_1
Text GLabel 1450 3450 0    60   Output ~ 0
ARD_V3_LIM_2
Text GLabel 1450 2550 0    60   Output ~ 0
ARD_V4_LIM_1
Text GLabel 1450 2700 0    60   Output ~ 0
ARD_V4_LIM_2
Text GLabel 1450 1500 0    60   Output ~ 0
LED_GREEN
Text GLabel 1450 1200 0    60   Output ~ 0
LED_AMBER
Text GLabel 1450 1050 0    60   Output ~ 0
LED_RED
Text GLabel 1450 1350 0    60   Output ~ 0
DAQ_MASS
Text GLabel 1450 1650 0    60   Output ~ 0
DAQ_P1
Text GLabel 1450 1800 0    60   Output ~ 0
DAQ_P2
$Comp
L CONN_01X40 P2
U 1 1 597FB2B0
P 6450 3000
F 0 "P2" H 6450 5050 50  0000 C CNN
F 1 "ARDUINO_CONNECTIONS" V 6550 3000 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_2x20_Pitch2.54mm" H 6450 3000 50  0001 C CNN
F 3 "" H 6450 3000 50  0000 C CNN
	1    6450 3000
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P1
U 1 1 597FB30F
P 6450 700
F 0 "P1" H 6450 850 50  0000 C CNN
F 1 "ARD_POWER" V 6550 700 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x02_Pitch2.54mm" H 6450 700 50  0001 C CNN
F 3 "" H 6450 700 50  0000 C CNN
	1    6450 700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 650  1450 650 
Wire Wire Line
	1450 800  1550 800 
Wire Wire Line
	1450 1050 6250 1050
Wire Wire Line
	1450 1200 1550 1200
Wire Wire Line
	1550 1200 1550 1150
Wire Wire Line
	1550 1150 6250 1150
Wire Wire Line
	1450 1350 1650 1350
Wire Wire Line
	1650 1350 1650 1250
Wire Wire Line
	1650 1250 6250 1250
Wire Wire Line
	1450 1500 1750 1500
Wire Wire Line
	1750 1500 1750 1350
Wire Wire Line
	1750 1350 6250 1350
Wire Wire Line
	1450 1650 1850 1650
Wire Wire Line
	1850 1650 1850 1450
Wire Wire Line
	1850 1450 6250 1450
Wire Wire Line
	1450 1800 1950 1800
Wire Wire Line
	1950 1800 1950 1550
Wire Wire Line
	1950 1550 6250 1550
Wire Wire Line
	1450 1950 2050 1950
Wire Wire Line
	2050 1950 2050 1650
Wire Wire Line
	2050 1650 6250 1650
Wire Wire Line
	1450 2100 2150 2100
Wire Wire Line
	2150 2100 2150 1750
Wire Wire Line
	2150 1750 6250 1750
Wire Wire Line
	1450 2250 2250 2250
Wire Wire Line
	2250 2250 2250 1850
Wire Wire Line
	2250 1850 6250 1850
Wire Wire Line
	1450 2400 2350 2400
Wire Wire Line
	2350 2400 2350 1950
Wire Wire Line
	2350 1950 6250 1950
Wire Wire Line
	1450 2550 2450 2550
Wire Wire Line
	2450 2550 2450 2050
Wire Wire Line
	2450 2050 6250 2050
Wire Wire Line
	1450 2700 2550 2700
Wire Wire Line
	2550 2700 2550 2150
Wire Wire Line
	2550 2150 6250 2150
Wire Wire Line
	1450 2850 2650 2850
Wire Wire Line
	2650 2850 2650 2250
Wire Wire Line
	2650 2250 6250 2250
Wire Wire Line
	1450 3000 2750 3000
Wire Wire Line
	2750 3000 2750 2350
Wire Wire Line
	2750 2350 6250 2350
Wire Wire Line
	1450 3150 2850 3150
Wire Wire Line
	2850 3150 2850 2450
Wire Wire Line
	2850 2450 6250 2450
Wire Wire Line
	1450 3300 2950 3300
Wire Wire Line
	2950 3300 2950 2550
Wire Wire Line
	2950 2550 6250 2550
Wire Wire Line
	1450 3450 3050 3450
Wire Wire Line
	3050 3450 3050 2650
Wire Wire Line
	3050 2650 6250 2650
Wire Wire Line
	1450 3600 3150 3600
Wire Wire Line
	3150 3600 3150 2750
Wire Wire Line
	3150 2750 6250 2750
Wire Wire Line
	1450 3750 3250 3750
Wire Wire Line
	3250 3750 3250 2850
Wire Wire Line
	3250 2850 6250 2850
Wire Wire Line
	1450 3900 3350 3900
Wire Wire Line
	3350 3900 3350 2950
Wire Wire Line
	3350 2950 6250 2950
Wire Wire Line
	1450 4050 3450 4050
Wire Wire Line
	3450 4050 3450 3050
Wire Wire Line
	3450 3050 6250 3050
Wire Wire Line
	1450 4200 3550 4200
Wire Wire Line
	3550 4200 3550 3150
Wire Wire Line
	3550 3150 6250 3150
Wire Wire Line
	1450 4350 3650 4350
Wire Wire Line
	3650 4350 3650 3250
Wire Wire Line
	3650 3250 6250 3250
Wire Wire Line
	1450 4500 3750 4500
Wire Wire Line
	3750 4500 3750 3350
Wire Wire Line
	3750 3350 6250 3350
Wire Wire Line
	1450 4650 3850 4650
Wire Wire Line
	3850 4650 3850 3450
Wire Wire Line
	3850 3450 6250 3450
Wire Wire Line
	1450 4800 3950 4800
Wire Wire Line
	3950 4800 3950 3550
Wire Wire Line
	3950 3550 6250 3550
Wire Wire Line
	1450 4950 4050 4950
Wire Wire Line
	4050 4950 4050 3650
Wire Wire Line
	4050 3650 6250 3650
Wire Wire Line
	1450 5100 4150 5100
Wire Wire Line
	4150 5100 4150 3750
Wire Wire Line
	4150 3750 6250 3750
Wire Wire Line
	1450 5250 4250 5250
Wire Wire Line
	4250 5250 4250 3850
Wire Wire Line
	4250 3850 6250 3850
Wire Wire Line
	1450 5400 4350 5400
Wire Wire Line
	4350 5400 4350 3950
Wire Wire Line
	4350 3950 6250 3950
Wire Wire Line
	1450 5550 4450 5550
Wire Wire Line
	4450 5550 4450 4050
Wire Wire Line
	4450 4050 6250 4050
Wire Wire Line
	1450 5700 4550 5700
Wire Wire Line
	4550 5700 4550 4150
Wire Wire Line
	4550 4150 6250 4150
Wire Wire Line
	1450 5850 4650 5850
Wire Wire Line
	4650 5850 4650 4250
Wire Wire Line
	4650 4250 6250 4250
Wire Wire Line
	1450 6000 4750 6000
Wire Wire Line
	4750 6000 4750 4350
Wire Wire Line
	4750 4350 6250 4350
Wire Wire Line
	1450 6150 4850 6150
Wire Wire Line
	4850 6150 4850 4450
Wire Wire Line
	4850 4450 6250 4450
Wire Wire Line
	1450 6300 4950 6300
Wire Wire Line
	4950 6300 4950 4550
Wire Wire Line
	4950 4550 6250 4550
Wire Wire Line
	1450 6450 5050 6450
Wire Wire Line
	5050 6450 5050 4650
Wire Wire Line
	5050 4650 6250 4650
Wire Wire Line
	1450 6600 5150 6600
Wire Wire Line
	5150 6600 5150 4750
Wire Wire Line
	5150 4750 6250 4750
Wire Wire Line
	1450 6750 5250 6750
Wire Wire Line
	5250 6750 5250 4850
Wire Wire Line
	5250 4850 6250 4850
Wire Wire Line
	1450 6900 5350 6900
Wire Wire Line
	5350 6900 5350 4950
Wire Wire Line
	5350 4950 6250 4950
Wire Wire Line
	1550 800  1550 750 
Wire Wire Line
	1550 750  6250 750 
$EndSCHEMATC
