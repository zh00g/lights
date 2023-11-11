#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define NEOPIXELPIN 18
#define NUMPIXELS 4
#define DELAY_INTERVAL 20

Adafruit_NeoPixel NeoPixel(NUMPIXELS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  NeoPixel.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
}

uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if(WheelPos < 85) {
        return NeoPixel.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if(WheelPos < 170) {
        WheelPos -= 85;
        return NeoPixel.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return NeoPixel.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// the loop function runs over and over again forever
void loop() {
  NeoPixel.clear();
  for(int j=0; j<256; j++) { // one cycle of all colors on the wheel
        for(int i=0; i< NUMPIXELS; i++) {
            NeoPixel.setPixelColor(i, Wheel((i+j) & 255));
        }
        NeoPixel.show();
        delay(DELAY_INTERVAL);
    }
}