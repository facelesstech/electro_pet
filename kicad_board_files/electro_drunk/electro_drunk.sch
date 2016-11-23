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
LIBS:special
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
LIBS:My_stuff
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "1 nov 2016"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ELECTRO_HAT U1
U 1 1 5818B310
P 3700 2000
F 0 "U1" V 4100 2200 60  0000 C CNN
F 1 "ELECTRO_HAT" H 3700 2300 60  0000 C CNN
F 2 "~" H 3700 2000 60  0000 C CNN
F 3 "~" H 3700 2000 60  0000 C CNN
	1    3700 2000
	1    0    0    -1  
$EndComp
$Comp
L MQ-3 U2
U 1 1 5818B562
P 4500 2050
F 0 "U2" H 4800 2200 60  0000 C CNN
F 1 "MQ-3" H 4500 2400 60  0000 C CNN
F 2 "" H 4500 1950 60  0000 C CNN
F 3 "" H 4500 1950 60  0000 C CNN
	1    4500 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 2300 4350 2550
Wire Wire Line
	4350 2550 3450 2550
Wire Wire Line
	3450 2550 3450 2300
Wire Wire Line
	4550 2300 4550 2500
Wire Wire Line
	4550 2500 3950 2500
Wire Wire Line
	3950 2500 3950 2300
Wire Wire Line
	4650 2300 4650 2450
Wire Wire Line
	4650 2450 3550 2450
Wire Wire Line
	3550 2450 3550 2300
$EndSCHEMATC
