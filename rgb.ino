#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(25, PIN,NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'\
}

void loop() {
  //
  // TODO: DMX Slave 
  // take RS485 differential "DMX" input
  // and convert it into:
  // ch 1 = procedure chooser
  // ch 2, 3, 4 = color picker
  // and ch 4 = rate
  // maybe ch 5 "option" (theater chase spacing?)
  // 
  // Some example procedures showing how to display to the pixels:
 colorFlood(strip.Color(0,0,0),1500);// Off between each demo
 //spinning_star(strip.Color(255,255,255),500); //grab a pixel make it white, spin the pixels around it
// colorFlood(strip.Color(0,0,0),1500);// Off between each demo//
// spinning_chase(strip.Color(96,0,255),100); //3x3 matrix outer perimeter Z configuration chase
 colorFlood(strip.Color(0,0,0),100);// Off / blackout
 colorWipe(strip.Color(255, 0, 0), 500); // Red
 colorWipe(strip.Color(0,0,0),500);// Off / wipe
 colorWipe(strip.Color(0, 255, 0), 500); // Green
 colorWipe(strip.Color(0,0,0),500);// Off
 colorWipe(strip.Color(0, 0, 255), 500); // Blue
 colorWipe(strip.Color(0,0,0),500);// Off
 colorWipe(strip.Color(0,0,0),1500);// Off between each demo
  stars(strip.Color(255,255,255),75);
  colorFlood(strip.Color(0,0,0),1500);// Off between each demo
  /*
  theaterChaseRainbow(175); // Send a theater pixel chase in...
  colorFlood(strip.Color(0,0,0),1500);// Off between each demo
  theaterChase(strip.Color(127, 127, 127), 150); // White
  colorFlood(strip.Color(0,0,0),1500);// Off between each demo
  theaterChase(strip.Color(127,   0,   0), 150); // Red
  colorFlood(strip.Color(0,0,0),1500);// Off between each demo
  theaterChase(strip.Color(  0,   0, 127), 150); // Blue
  colorFlood(strip.Color(0,0,0),1500);// Off between each demo
 */
  //pickapixel(7,strip.Color(255,255,255),1); //grab a pixel make it white
  //pickapixel(5,strip.Color(0,255,255),1); // grab a pixel make it cyan
 // pickapixel(3,strip.Color(255,255,0),1); // grab a pixel make it yellow
 // pickapixel(1,strip.Color(255,0,255),1);  // grab a pixel make it magenta
 // delay(3500); //let the pickapixel show for a moment.
  colorFlood(strip.Color(0,0,0),1500);// Off between each demo
  
  rainbow(20);
  colorFlood(strip.Color(0,0,0),1500);// Off between each demo
  strobe(27);
  colorFlood(strip.Color(0,0,0),1500);// Off between each demo
  rainbowCycle(20);
  colorFlood(strip.Color(0,0,0),1500);// Off between each demo
    
 stars(strip.Color(255,255,255),100);
 colorFlood(strip.Color(0,0,0),1500);// Off between each demo
 rainbowCycle(10);
 colorFlood(strip.Color(0,0,0),1500);// Off between each demo

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void colorFlood(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
}

void stars(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    int pixeltopick = (random(0,strip.numPixels()));  
    strip.setPixelColor(pixeltopick, c);
      strip.show();
      delay(wait);
      strip.setPixelColor(pixeltopick, 0,0,0);
      strip.show();
      delay(wait);
      }
}

void pickapixel(uint32_t p, uint32_t c, uint8_t wait) {
    strip.setPixelColor(p, c);
    strip.show();
    delay(wait);
      }

      
void spinning_chase(uint32_t c, uint8_t wait) {
for(uint16_t i=0; i<strip.numPixels(); i++) {
    
    strip.setPixelColor(0, c);
    strip.show();
    delay(wait);
    strip.setPixelColor(0, strip.Color(0,0,0));
    strip.setPixelColor(1, c);
    strip.show();
    delay(wait);
    strip.setPixelColor(1, strip.Color(0,0,0));
    strip.setPixelColor(2, c);
    strip.show();
    delay(wait);
    strip.setPixelColor(2, strip.Color(0,0,0));
    strip.setPixelColor(3, c);
    strip.show();
    delay(wait);
    strip.setPixelColor(3, strip.Color(0,0,0));
    strip.setPixelColor(8, c);
    strip.show();
    delay(wait);
    strip.setPixelColor(8, strip.Color(0,0,0));
    strip.setPixelColor(7, c);
    strip.show();
    delay(wait);//or anyone I found information/software to build this with
    strip.setPixelColor(7, strip.Color(0,0,0));
    strip.setPixelColor(6, c);
    strip.show();
    delay(wait);
    strip.setPixelColor(6, strip.Color(0,0,0));
    strip.setPixelColor(5, c);
    strip.show();
    delay(wait);
    strip.setPixelColor(5, strip.Color(0,0,0));
    strip.show();
}}
      
void spinning_star(uint32_t c, uint8_t wait) {
for(uint16_t i=0; i<strip.numPixels(); i++) {
    
    strip.setPixelColor(0, strip.Color(0,0,0));
    strip.setPixelColor(2, strip.Color(0,0,0));
    strip.setPixelColor(4, strip.Color(0,0,0));
    strip.setPixelColor(6, strip.Color(0,0,0));
    strip.setPixelColor(8, strip.Color(0,0,0));
    strip.setPixelColor(1, c);
    strip.setPixelColor(3, c);
    strip.setPixelColor(5, c);
    strip.setPixelColor(7, c);
    strip.show();
    delay(wait);
    strip.setPixelColor(1, strip.Color(0,0,0));
    strip.setPixelColor(3, strip.Color(0,0,0));
    strip.setPixelColor(5, strip.Color(0,0,0));
    strip.setPixelColor(7, strip.Color(0,0,0));
    strip.setPixelColor(0, c);
    strip.setPixelColor(2, c);
    strip.setPixelColor(4, c);
    strip.setPixelColor(6, c);
    strip.setPixelColor(8, c);
    strip.show();
    delay(wait);
}      
    }
      
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
void strobe(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, 255,255,255);
    }
    strip.show();
    delay(wait);
   for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, 0,0,0);
    }
    strip.show();
    delay(wait);
     
}
  
}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<3; j++) {  //do 3 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
