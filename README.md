# Lego Power Functions Infrared Control for Arduino

This is an Arduino Lego Power Functions Library.
For now it only supports single/combo PWM.
Based on [SuperCow's code](http://forum.arduino.cc/index.php?topic=38142.msg282833#msg282833)
And [Jurriaans library] (https://github.com/jurriaan/Arduino-PowerFunctions)

## Protocol

See [LEGO_Power_Functions_RC_v120.pdf](https://github.com/TheDIYGuy999/LegoIr/blob/master/LEGO_Power_Functions_RC_v120.pdf) for more info

## Changelog

New in V 1.0:
- Library is now also compatible with CPU's slower than 16MHz. Tested an Arduino Pro Mini 3.3V / 8MHz board

New in V 1.1:
- Library is now also compatible with CPU's faster than 16MHz. Tested on an STM32 ARM "Maple" board

New in V 1.11:
- The STM32 MPU does not like delays with a duration of zero! This caused a crash on LEGO channel 4
- This bug is now fixed and you can use all 4 channels

## Usage

See [example](https://github.com/TheDIYGuy999/LegoIr/blob/master/examples/LegoIr/LegoIr.ino).

## Schematic

See [example](https://github.com/TheDIYGuy999/LegoIr/blob/master/IR%20LED%20Driver.png).


(c) 2013 Jurriaan Pruis
Modified and enhanced by TheDIYGuy999, June 2016, December 2017
