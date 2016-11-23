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
Date "24 oct 2016"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L R R?
U 1 1 580E645A
P 5900 4000
F 0 "R?" V 5980 4000 40  0000 C CNN
F 1 "R" V 5907 4001 40  0000 C CNN
F 2 "~" V 5830 4000 30  0000 C CNN
F 3 "~" H 5900 4000 30  0000 C CNN
	1    5900 4000
	1    0    0    -1  
$EndComp
$Comp
L LED D?
U 1 1 580E6469
P 5400 4050
F 0 "D?" H 5400 4150 50  0000 C CNN
F 1 "LED" H 5400 3950 50  0000 C CNN
F 2 "~" H 5400 4050 60  0000 C CNN
F 3 "~" H 5400 4050 60  0000 C CNN
	1    5400 4050
	0    -1   -1   0   
$EndComp
$Comp
L ELECTRO_HAT U?
U 1 1 580E6481
P 5650 3400
F 0 "U?" V 6050 3600 60  0000 C CNN
F 1 "ELECTRO_HAT" H 5650 3700 60  0000 C CNN
F 2 "~" H 5650 3400 60  0000 C CNN
F 3 "~" H 5650 3400 60  0000 C CNN
	1    5650 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 3700 5400 3850
Wire Wire Line
	5400 4250 5900 4250
Wire Wire Line
	5900 3750 5900 3700
$EndSCHEMATC
