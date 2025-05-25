# Smart lighting - microcontroller
## Project Overview 

The smart lights project consists of the two repositories: [Arduino code](https://github.com/MaybeAshLately/smartLights) and [Android app](https://github.com/MaybeAshLately/lightControl). The aim of the project is to create simple prototype of smart lightning, based on Arduino and app to control it. 

## Arduino part overview

This repository contains Arduino program. The code is responsible for receiving commands (through bluetooth), and turning on the lights in one of four modes:
- NORMAL - the RGB LED turns on in received color and brightness,
- PHOTORESISTOR - the RGB LED turns on in received color and brightness when the photoresistor reports light level under received level,
- MOTION - the RGB LED turns on in received color and brightness after PIR sensor detects the movement, 
- TV - the RGB LED is blinking in random colors (to simulate the TV in a room).

## Wiring
Hardware part of project consists of:
- Arduino Uno R3.l
- Bluetooth module HC-06 connected to pins 0 (TX of HC-06) and 1 (RX of HC-06). Pin RX of HC-06 has to be connected through voltage converter (because Arduino has 5V logic while HC-06 has 3,3V logic). **Attention: during uploading the sketch remember to unwire pins 0 and 1**. They are connected to hardware Serial and will interfere with the uploading.
- RGB diode, red to pin 9, green to pin 10 and blue to pin 11 (**through resistors**). If you want to use other pins, remember that they have to be PWM pins. 
- Photoresistor is connected to analog pin A5. Remember to use resistor. 
- PIR motion sensor is connected to pin 2. 

## License

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.