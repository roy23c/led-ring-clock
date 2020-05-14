#include <virtuabotixRTC.h>                                                                              //|
#include <Adafruit_NeoPixel.h>

// define pins
#define NEOPIN 3
#define STARTPIXEL 30 // where do we start on the loop? use this to shift the arcs if the wiring does not start at the "12" point
virtuabotixRTC myRTC(6, 7, 8);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, NEOPIN, NEO_GRB + NEO_KHZ800); // strip object

byte pixelColorRed, pixelColorGreen, pixelColorBlue; // holds color values

#define BRIGHTNESS 30

const int on_switch = 9;
const int time_adjust = 2;
bool on = true; 


void setup () {  
  // Set the current date, and time in the following format:
  // seconds, minutes, hours, day of the week, day of the month, month, year
  // myRTC.setDS1302Time(55, 14, 9, 2, 10, 1, 2014);
  
  
  Serial.begin(9600);
  // set pinmodes
  pinMode(NEOPIN, OUTPUT);
  pinMode(on_switch, INPUT);
  pinMode(time_adjust, INPUT);



  strip.begin();
  //strip.show(); // Initialize all pixels to 'off'

  strip.setBrightness(BRIGHTNESS); // set brightness

  // startup sequence
  delay(500);
  colorWipe(strip.Color(255, 0, 0), 20); // Red
  colorWipe(strip.Color(0, 255, 0), 20); // Green
  colorWipe(strip.Color(0, 0, 255), 20); // Blue
  delay(500);

}

void loop () {

  bool on_state = digitalRead(on_switch);
  bool adjust_state = digitalRead(time_adjust);

  // get time
  myRTC.updateTime();                                                                                    

  byte secondval = myRTC.seconds;  // get seconds
  byte minuteval = myRTC.minutes;  // get minutes
  int hourval = myRTC.hours;   // get hours
  
  if(on_state == HIGH && on){
    delay(500);
    if(on_state ==HIGH && adjust_state == HIGH){    
      minuteval += 1;
      if (minuteval == 61){
        minuteval = 0;
      }
      myRTC.setDS1302Time(myRTC.seconds, minuteval, myRTC.hours, myRTC.dayofweek, myRTC.dayofmonth, myRTC.month, myRTC.year);
    }
    else if(on_state ==HIGH && adjust_state == LOW){
      strip.setBrightness(0); 
      on = false; 
      delay(1500);
    }
  }
  else if (on_state == HIGH && !on){
    strip.setBrightness(BRIGHTNESS);
    on = true; 
    delay(1500);
  }
  else if (adjust_state == HIGH && on){
    hourval += 1;
    if (hourval == 25){
      hourval = 0;
    }
    myRTC.setDS1302Time(myRTC.seconds, myRTC.minutes, hourval, myRTC.dayofweek, myRTC.dayofmonth, myRTC.month, myRTC.year);
    delay(500);
  }


  hourval = hourval % 12; // This clock is 12 hour, if 13-23, convert to 0-11`

  hourval = (hourval * 60 + minuteval) / 12; //each red dot represent 24 minutes.

  // arc mode
  for (uint8_t i = 0; i < strip.numPixels(); i++) {

    if (i <= secondval) {
      // calculates a faded arc from low to maximum brightness
      pixelColorBlue = (i + 1) * (255 / (secondval + 1));
      //pixelColorBlue = 255;
    }
    else {
      pixelColorBlue = 0;
    }

    if (i <= minuteval) {
      pixelColorGreen = (i + 1) * (255 / (minuteval + 1));
      //pixelColorGreen = 255;
    }
    else {
      pixelColorGreen = 0;
    }

    if (i <= hourval) {
      pixelColorRed = (i + 1) * (255 / (hourval + 1));
      //pixelColorRed = 255;
    }
    else {
      pixelColorRed = 0;
    }

    strip.setPixelColor((i + STARTPIXEL) % 60, strip.Color(pixelColorRed, pixelColorGreen, pixelColorBlue));
  }

  //display
  strip.show();

  // printTheTime(theTime);

  // wait
  delay(100);

}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    //strip.setPixelColor(i, c);
    strip.setPixelColor((i + STARTPIXEL) % 60, c);
    strip.show();
    delay(wait);
  }
}
