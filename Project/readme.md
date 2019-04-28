*Project Summary:* 

*VUSB based alarm system*

The objective of project is to send threshold values for LDR sensor via USB protocol. LDR Sensor is interfaced to ADC of Atmega8. The firmware of Atmega8 will compare the converted sensor value with threshold value sent from the userspace. If the ADC's converted value is higher than threshold value, there will be an alarm. The firmware part includes a C program that controls ADC channel selection and setting LDR and alarm initialisation to atmega pins. IOCTL calls are used to send threshold value. Libusb is also used to send threshold value. Four threshold levels(0 to 3) are defined for the sensor.Threshold level 0 indicates lowest value and threshold level 3 indicates highest value. 

*Sensor Description:*

Light Dependent Resistor(LDR) is a light-controlled variable resistor. The resistance of a LDR decreases with increasing incident light intensity.

LDR returns higher value when light intensity is less and returns lower value when light intensity is high. 

*Build process*

*Driver*

To build kernel module

`$ make all`

To insert kernel module

`$ make insert`

To remove kernel module

`$ make remove`

To clean up files

`$ make clean`

*Firmware*
To create hex file

`$ make hex`

To set fuses

`$ make fuse`

To flash the code

`$ make flash`

To clean up files

`$ make clean`

*commandline*
To build program

`$ make all`

To get sensor readings

`$ ./ldr_adc get 0`

To send threshold values
```
$./ldr_adc set 0
$./ldr_adc set 1
$./ldr_adc set 2
$./ldr_adc set 3
```

*userapp*
To compile
`$ make compile`

To run
```
$./userapp set 0
$./userapp set 1
$./userapp set 2
$./userapp set 3
```

Project made by: Likhith V (2018H1400133G) and Krishna Chaithanya Reddy (2018H1400126G)














