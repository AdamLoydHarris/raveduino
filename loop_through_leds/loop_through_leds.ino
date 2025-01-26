#include <FastLED.h>
#define NUM_LEDS 256
#define DATA_PIN 6
CRGB leds[NUM_LEDS];

CRGBPalette16 myPalette = RainbowColors_p;
uint8_t index = 0;


void setup() {   
 FastLED.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
 FastLED.setBrightness(20);
}
 
void loop() {
  for (int i=0; i<=256; i++) {
    ++index;
    leds[i] = ColorFromPalette(myPalette, index);
    leds[i-1]=CRGB::Black;
    FastLED.show();
    delay(60);
  }
}