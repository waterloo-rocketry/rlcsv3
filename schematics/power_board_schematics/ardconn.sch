EESchema Schematic File Version 4
LIBS:rlcs_power-cache
EELAYER 30 0
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
$Comp
L Connector:Conn_01x08_Male J8
U 1 1 5E6FC39B
P 4150 3350
F 0 "J8" H 4258 3831 50  0000 C CNN
F 1 "Conn_01x08_Male" H 4258 3740 50  0000 C CNN
F 2 "" H 4150 3350 50  0001 C CNN
F 3 "~" H 4150 3350 50  0001 C CNN
	1    4150 3350
	1    0    0    -1  
$EndComp
Text Notes 650  3150 0    60   ~ 0
Arduino Pins 14 - 21
Text Notes 4750 900  0    60   ~ 0
Arduino Pins 22 - 53
Text Notes 2650 1000 0    60   ~ 0
Arduino Pins A0 - A7
Text Notes 2600 1950 0    60   ~ 0
Arduino Pins A8 - A15
Text Notes 700  2100 0    60   ~ 0
Arduino Pins 8 - 13 \n+ some others\n
Text Notes 2800 3150 0    60   ~ 0
Arduino Pins Power
Text Notes 700  950  0    60   ~ 0
Arudino Pins 0 - 7
Text GLabel 4100 5350 0    60   Input ~ 0
ARD_CON_SD_MOSI
Text GLabel 4100 5200 0    60   Input ~ 0
ARD_CON_SD_MISO
Text GLabel 4100 5050 0    60   Input ~ 0
ARD_CON_SD_SS
Wire Wire Line
	5450 5850 6100 5850
Wire Wire Line
	5450 5800 5450 5850
Wire Wire Line
	4100 5800 5450 5800
Wire Wire Line
	5550 5750 6100 5750
Wire Wire Line
	5550 5650 5550 5750
Wire Wire Line
	4100 5650 5550 5650
Wire Wire Line
	5650 5650 6100 5650
Wire Wire Line
	5650 5500 5650 5650
Wire Wire Line
	4100 5500 5650 5500
Wire Wire Line
	5750 5550 6100 5550
Wire Wire Line
	5750 5350 5750 5550
Wire Wire Line
	4100 5350 5750 5350
Wire Wire Line
	5850 5450 6100 5450
Wire Wire Line
	5850 5200 5850 5450
Wire Wire Line
	4100 5200 5850 5200
Wire Wire Line
	5950 5350 6100 5350
Wire Wire Line
	5950 5050 5950 5350
Wire Wire Line
	4100 5050 5950 5050
Wire Wire Line
	4100 5950 6100 5950
Wire Wire Line
	5150 6050 6100 6050
Wire Wire Line
	5150 6100 5150 6050
Wire Wire Line
	5250 6150 6100 6150
Wire Wire Line
	5250 6250 5250 6150
Wire Wire Line
	5350 6250 6100 6250
Wire Wire Line
	5350 6400 5350 6250
Wire Wire Line
	5450 6350 6100 6350
Wire Wire Line
	5450 6550 5450 6350
Wire Wire Line
	4100 6550 5450 6550
Wire Wire Line
	5550 6450 6100 6450
Wire Wire Line
	5550 6700 5550 6450
Wire Wire Line
	4100 6700 5550 6700
Wire Wire Line
	5650 6550 6100 6550
Wire Wire Line
	5650 6850 5650 6550
Wire Wire Line
	4100 6850 5650 6850
Wire Wire Line
	5750 6650 6100 6650
Wire Wire Line
	5750 7000 5750 6650
Wire Wire Line
	4100 7000 5750 7000
Wire Wire Line
	5850 6750 6100 6750
Wire Wire Line
	5850 7150 5850 6750
Wire Wire Line
	4100 7150 5850 7150
Wire Wire Line
	5950 6850 6100 6850
Wire Wire Line
	5950 7300 5950 6850
Wire Wire Line
	4100 7300 5950 7300
$Comp
L rlcs_power-rescue:CONN_01X16 J7
U 1 1 59C7785C
P 6300 6100
F 0 "J7" H 6300 6950 50  0000 C CNN
F 1 "CONN_01X16" V 6400 6100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x08_Pitch2.54mm" H 6300 6100 50  0001 C CNN
F 3 "" H 6300 6100 50  0001 C CNN
	1    6300 6100
	1    0    0    -1  
$EndComp
Text Notes 850  6200 0    60   ~ 0
All Arduino connections put on this sheet\nso they can be reordered without screwing\nup the main sheet\n\n(this doesn't include power out)
Text GLabel 4100 7300 0    60   Input ~ 0
ARD_CON_7SEG_G
Text GLabel 4100 6850 0    60   Input ~ 0
ARD_CON_7SEG_F
Text GLabel 4100 6700 0    60   Input ~ 0
ARD_CON_7SEG_E
Text GLabel 4100 6550 0    60   Input ~ 0
ARD_CON_7SEG_C
Text GLabel 4100 7000 0    60   Input ~ 0
ARD_CON_7SEG_B
Text GLabel 4100 7150 0    60   Input ~ 0
ARD_CON_7SEG_A
Text GLabel 4100 5650 0    60   Input ~ 0
ARD_CON_SD_CD
Text GLabel 4100 5800 0    60   Input ~ 0
ARD_CON_SD_WP
Text GLabel 4100 5500 0    60   Input ~ 0
ARD_CON_SD_SCL
$Comp
L custom:conn_22_to_53 U6
U 1 1 5E7AFC08
P 8050 2200
F 0 "U6" H 8050 3239 60  0000 C CNN
F 1 "conn_22_to_53" H 8050 3133 60  0000 C CNN
F 2 "" H 8000 3250 60  0001 C CNN
F 3 "" H 8000 3250 60  0001 C CNN
	1    8050 2200
	1    0    0    -1  
$EndComp
$Comp
L custom:Conn_0_to_7 U1
U 1 1 5E7B26E9
P 2000 1100
F 0 "U1" H 1937 1597 60  0000 C CNN
F 1 "Conn_0_to_7" H 1937 1491 60  0000 C CNN
F 2 "" H 1900 1800 60  0001 C CNN
F 3 "" H 1900 1800 60  0001 C CNN
	1    2000 1100
	1    0    0    -1  
$EndComp
$Comp
L custom:conn_8_to_13 U2
U 1 1 5E7B5F51
P 2050 2200
F 0 "U2" H 1912 2797 60  0000 C CNN
F 1 "conn_8_to_13" H 1912 2691 60  0000 C CNN
F 2 "" H 2050 3100 60  0001 C CNN
F 3 "" H 2050 3100 60  0001 C CNN
	1    2050 2200
	1    0    0    -1  
$EndComp
$Comp
L custom:Conn_14_to_21 U3
U 1 1 5E7B8C25
P 2050 3350
F 0 "U3" H 1912 3847 60  0000 C CNN
F 1 "Conn_14_to_21" H 1912 3741 60  0000 C CNN
F 2 "" H 1950 4250 60  0001 C CNN
F 3 "" H 1950 4250 60  0001 C CNN
	1    2050 3350
	1    0    0    -1  
$EndComp
$Comp
L custom:conn_A0_to_A7 U5
U 1 1 5E7C0D80
P 4500 1250
F 0 "U5" H 4112 1847 60  0000 C CNN
F 1 "conn_A0_to_A7" H 4112 1741 60  0000 C CNN
F 2 "" H 4500 1850 60  0001 C CNN
F 3 "" H 4500 1850 60  0001 C CNN
	1    4500 1250
	1    0    0    -1  
$EndComp
$Comp
L custom:conn_A8_to_A15 U4
U 1 1 5E7C1AAF
P 4400 2250
F 0 "U4" H 3962 2847 60  0000 C CNN
F 1 "conn_A8_to_A15" H 3962 2741 60  0000 C CNN
F 2 "" H 4450 2850 60  0001 C CNN
F 3 "" H 4450 2850 60  0001 C CNN
	1    4400 2250
	1    0    0    -1  
$EndComp
Text GLabel 4100 6250 0    60   Input ~ 0
ARD_CON_7SEG_D
Text GLabel 4100 6400 0    60   Input ~ 0
ARD_CON_7SEG_DP
Text GLabel 4100 5950 0    60   Input ~ 0
ARD_CON_7SEG_D1
Text GLabel 4100 6100 0    60   Input ~ 0
ARD_CON_7SEG_D2
Wire Wire Line
	4100 6400 5350 6400
Wire Wire Line
	4100 6250 5250 6250
Wire Wire Line
	4100 6100 5150 6100
Text GLabel 9550 1450 2    60   Input ~ 0
Remotefill_Select
Text GLabel 9550 1250 2    60   Input ~ 0
Remotevent_Power
Text GLabel 9550 1050 2    60   Input ~ 0
Linactuator_Select
Text GLabel 9550 1650 2    60   Input ~ 0
Ignition_Primary_Select
Text GLabel 9550 2450 2    60   Input ~ 0
Ignition_Secondary_Power
Text GLabel 9550 2250 2    60   Input ~ 0
Limitsw_Remotefill_CLS
Text GLabel 9550 2050 2    60   Input ~ 0
Limitsw_Remotevent_OPN
Text GLabel 9550 3450 2    60   Input ~ 0
Sevenseg_D1
Text GLabel 9550 2650 2    60   Input ~ 0
Sevenseg_A
Text GLabel 9550 3050 2    60   Input ~ 0
Sevenseg_C
Text GLabel 9550 3250 2    60   Input ~ 0
Sevenseg_D
Text GLabel 9550 2850 2    60   Input ~ 0
Sevenseg_F
Text GLabel 9550 3650 2    60   Input ~ 0
SD_SS
Wire Wire Line
	7650 2600 7650 3450
Wire Wire Line
	7600 2500 7600 3250
Wire Wire Line
	7550 2400 7550 3050
Wire Wire Line
	7500 2300 7500 2850
Text GLabel 6550 1450 0    60   Input ~ 0
Remotefill_Power
Text GLabel 6550 1050 0    60   Input ~ 0
Linactuator_Power
Text GLabel 6550 1650 0    60   Input ~ 0
Ignition_Primary_Power
Text GLabel 6550 2450 0    60   Input ~ 0
Ignition_Secondary_Select
Text GLabel 6550 2250 0    60   Input ~ 0
Limitsw_Remotefill_OPN
Text GLabel 6550 2050 0    60   Input ~ 0
Limitsw_Removevent_CLS
Text GLabel 6550 1850 0    60   Input ~ 0
Limitsw_Linac_Ret
Text GLabel 6550 3450 0    60   Input ~ 0
Sevenseg_D2
Text GLabel 6550 2850 0    60   Input ~ 0
Sevenseg_B
Text GLabel 6550 3050 0    60   Input ~ 0
Sevenseg_E
Text GLabel 6550 2650 0    60   Input ~ 0
Sevenseg_G
Text GLabel 6550 3250 0    60   Input ~ 0
Sevenseg_DP
Text GLabel 6550 1250 0    60   Input ~ 0
Remotevent_Select
Wire Wire Line
	7400 1050 6550 1050
Wire Wire Line
	7350 1500 7350 1250
Wire Wire Line
	7350 1250 6550 1250
Wire Wire Line
	7300 1600 7300 1450
Wire Wire Line
	7300 1450 6550 1450
Wire Wire Line
	7250 1700 7250 1650
Wire Wire Line
	7250 1650 6550 1650
Wire Wire Line
	7250 1800 7250 1850
Wire Wire Line
	7250 1850 6550 1850
Wire Wire Line
	7300 1900 7300 2050
Wire Wire Line
	7300 2050 6550 2050
Wire Wire Line
	7350 2250 6550 2250
Wire Wire Line
	7350 2000 7350 2250
Wire Wire Line
	7400 2450 6550 2450
Wire Wire Line
	7450 2650 6550 2650
Wire Wire Line
	7500 2850 6550 2850
Wire Wire Line
	7550 3050 6550 3050
Wire Wire Line
	7600 3250 6550 3250
Wire Wire Line
	7650 3450 6550 3450
Wire Wire Line
	7450 2200 7450 2650
Wire Wire Line
	7400 2100 7400 2450
Wire Wire Line
	7400 1400 7400 1050
Wire Wire Line
	7400 1400 7800 1400
Wire Wire Line
	7350 1500 7800 1500
Wire Wire Line
	7300 1600 7800 1600
Wire Wire Line
	7250 1700 7800 1700
Wire Wire Line
	7250 1800 7800 1800
Wire Wire Line
	7300 1900 7800 1900
Wire Wire Line
	7350 2000 7800 2000
Wire Wire Line
	7400 2100 7800 2100
Wire Wire Line
	7450 2200 7800 2200
Wire Wire Line
	7500 2300 7800 2300
Wire Wire Line
	7550 2400 7800 2400
Wire Wire Line
	7600 2500 7800 2500
Wire Wire Line
	7650 2600 7800 2600
Wire Wire Line
	8700 1050 9550 1050
Wire Wire Line
	8750 1250 9550 1250
Wire Wire Line
	8800 1600 8800 1450
Wire Wire Line
	8800 1450 9550 1450
Wire Wire Line
	8850 1700 8850 1650
Wire Wire Line
	8850 1650 9550 1650
Wire Wire Line
	8850 1800 8850 1850
Wire Wire Line
	8850 1850 9550 1850
Wire Wire Line
	8800 1900 8800 2050
Wire Wire Line
	8800 2050 9550 2050
Wire Wire Line
	8450 2600 8300 2600
Wire Wire Line
	8500 2500 8300 2500
Wire Wire Line
	8550 2400 8300 2400
Wire Wire Line
	8600 2300 8300 2300
Wire Wire Line
	8650 2200 8300 2200
Wire Wire Line
	8700 2100 8300 2100
Wire Wire Line
	8750 2000 8300 2000
Wire Wire Line
	8800 1900 8300 1900
Wire Wire Line
	8850 1800 8300 1800
Wire Wire Line
	8850 1700 8300 1700
Wire Wire Line
	8800 1600 8300 1600
Wire Wire Line
	8750 1500 8300 1500
Wire Wire Line
	8700 1400 8300 1400
Wire Wire Line
	8700 1400 8700 1050
Wire Wire Line
	8700 2100 8700 2450
Wire Wire Line
	8650 2200 8650 2650
Wire Wire Line
	8450 3450 9550 3450
Wire Wire Line
	8500 3250 9550 3250
Wire Wire Line
	8550 3050 9550 3050
Wire Wire Line
	8600 2850 9550 2850
Wire Wire Line
	8650 2650 9550 2650
Wire Wire Line
	8700 2450 9550 2450
Wire Wire Line
	8750 2000 8750 2250
Wire Wire Line
	8750 2250 9550 2250
Wire Wire Line
	8750 1500 8750 1250
Wire Wire Line
	8600 2300 8600 2850
Wire Wire Line
	8550 2400 8550 3050
Wire Wire Line
	8500 2500 8500 3250
Wire Wire Line
	8450 2600 8450 3450
Text GLabel 9550 1850 2    60   Input ~ 0
Limitsw_Linac_EXT
Wire Wire Line
	8300 2900 8300 3650
Wire Wire Line
	8300 3650 9550 3650
$EndSCHEMATC
