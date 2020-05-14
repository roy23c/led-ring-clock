# LED Ring Clock

3D printed clock displays time with LED ring

![image](https://github.com/roycechung/led-ring-clock/blob/master/images/led-ring-clock-gif.gif)

## Getting Started

### Prerequisites
* [Arduino_IDE](https://www.arduino.cc/en/Main/Software)
* [Adafruit_Neopixel](https://github.com/adafruit/Adafruit_NeoPixel)
* [Virtuabotix RTC](https://github.com/chrisfryer78/ArduinoRTClibrary)

### Hardware Required 
* Arduino Nano
* Adafruit Perma-Proto Half-sized Breadboard PCB
* 4x NeoPixel 1/4 60 Ring
* 1x DS1302 RTC
* 2x Button Switches

### Hardware Schematic
* Will be added! 

### 3D Model 
<img src="https://github.com/roycechung/led-ring-clock/blob/master/images/render.PNG" width="60%">

The plastic components of the clock are 3D printed in white PLA
* 1x led_ring.stl
* 1x led_ring_base.stl
* 1x led_ring_cover.stl

### Installing
Compile and load ```ring_clock.ino``` onto Arduino Nano.

During first upload uncomment the following line right under ```void setup()```
```
myRTC.setDS1302Time(55, 14, 9, 2, 10, 1, 2014);
```
Then set current time in function in the following order: seconds, minutes, hours, day of the week, day of the month, month, year. After, comment out the line and recompile and upload code to Arduino

### Button Input
The button connected to pin 9 is used to swtich the clock on/off.

The button connected to pin 2 is used to adjust the hour hand.

Both buttons pressed together will adjust the minute hand.

## Acknoledgements 
The origial [source code](https://github.com/andydoro/NeoPixel-60-Ring-Clock) for the led ring clock.

The code here is modified for a DS1302 real time clock and buttons for time adustment and on/off
