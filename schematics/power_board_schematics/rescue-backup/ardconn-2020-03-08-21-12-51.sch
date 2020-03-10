EESchema Schematic File Version 2
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
LIBS:rlcs_power-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title "RLCS power board"
Date "2017-09-24"
Rev "A"
Comp "Waterloo Rocketry"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 5100 3000 0    60   Input ~ 0
ARD_CON_SD_MOSI
Text GLabel 5100 3150 0    60   Input ~ 0
ARD_CON_SD_SCL
Text GLabel 5100 2700 0    60   Input ~ 0
ARD_CON_SD_SS
Text GLabel 5100 3450 0    60   Input ~ 0
ARD_CON_SD_WP
Text GLabel 5100 3300 0    60   Input ~ 0
ARD_CON_SD_CD
Text GLabel 5100 4800 0    60   Input ~ 0
ARD_CON_7SEG_A
Text GLabel 5100 4650 0    60   Input ~ 0
ARD_CON_7SEG_B
Text GLabel 5100 4200 0    60   Input ~ 0
ARD_CON_7SEG_C
Text GLabel 5100 3900 0    60   Input ~ 0
ARD_CON_7SEG_D
Text GLabel 5100 4350 0    60   Input ~ 0
ARD_CON_7SEG_E
Text GLabel 5100 4500 0    60   Input ~ 0
ARD_CON_7SEG_F
Text GLabel 5100 4950 0    60   Input ~ 0
ARD_CON_7SEG_G
Text GLabel 5100 4050 0    60   Input ~ 0
ARD_CON_7SEG_DP
Text GLabel 5100 3600 0    60   Input ~ 0
ARD_CON_7SEG_D1
Text GLabel 5100 3750 0    60   Input ~ 0
ARD_CON_7SEG_D2
Text GLabel 5100 2850 0    60   Input ~ 0
ARD_CON_SD_MISO
Text Notes 1850 3850 0    60   ~ 0
All Arduino connections put on this sheet\nso they can be reordered without screwing\nup the main sheet\n\n(this doesn't include power out)
$Comp
L CONN_01X16 J7
U 1 1 59C7785C
P 7300 3750
F 0 "J7" H 7300 4600 50  0000 C CNN
F 1 "CONN_01X16" V 7400 3750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x08_Pitch2.54mm" H 7300 3750 50  0001 C CNN
F 3 "" H 7300 3750 50  0001 C CNN
	1    7300 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 4950 6950 4950
Wire Wire Line
	6950 4950 6950 4500
Wire Wire Line
	6950 4500 7100 4500
Wire Wire Line
	5100 4800 6850 4800
Wire Wire Line
	6850 4800 6850 4400
Wire Wire Line
	6850 4400 7100 4400
Wire Wire Line
	5100 4650 6750 4650
Wire Wire Line
	6750 4650 6750 4300
Wire Wire Line
	6750 4300 7100 4300
Wire Wire Line
	5100 4500 6650 4500
Wire Wire Line
	6650 4500 6650 4200
Wire Wire Line
	6650 4200 7100 4200
Wire Wire Line
	5100 4350 6550 4350
Wire Wire Line
	6550 4350 6550 4100
Wire Wire Line
	6550 4100 7100 4100
Wire Wire Line
	5100 4200 6450 4200
Wire Wire Line
	6450 4200 6450 4000
Wire Wire Line
	6450 4000 7100 4000
Wire Wire Line
	5100 4050 6350 4050
Wire Wire Line
	6350 4050 6350 3900
Wire Wire Line
	6350 3900 7100 3900
Wire Wire Line
	5100 3900 6250 3900
Wire Wire Line
	6250 3900 6250 3800
Wire Wire Line
	6250 3800 7100 3800
Wire Wire Line
	5100 3750 6150 3750
Wire Wire Line
	6150 3750 6150 3700
Wire Wire Line
	6150 3700 7100 3700
Wire Wire Line
	5100 3600 7100 3600
Wire Wire Line
	5100 2700 6950 2700
Wire Wire Line
	6950 2700 6950 3000
Wire Wire Line
	6950 3000 7100 3000
Wire Wire Line
	5100 2850 6850 2850
Wire Wire Line
	6850 2850 6850 3100
Wire Wire Line
	6850 3100 7100 3100
Wire Wire Line
	5100 3000 6750 3000
Wire Wire Line
	6750 3000 6750 3200
Wire Wire Line
	6750 3200 7100 3200
Wire Wire Line
	5100 3150 6650 3150
Wire Wire Line
	6650 3150 6650 3300
Wire Wire Line
	6650 3300 7100 3300
Wire Wire Line
	5100 3300 6550 3300
Wire Wire Line
	6550 3300 6550 3400
Wire Wire Line
	6550 3400 7100 3400
Wire Wire Line
	5100 3450 6450 3450
Wire Wire Line
	6450 3450 6450 3500
Wire Wire Line
	6450 3500 7100 3500
$EndSCHEMATC
