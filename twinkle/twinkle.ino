#include <FastLED.h>
#define NUM_LEDS 512
#define DATA_PIN 6
CRGB leds[NUM_LEDS];

void setup() {   
 FastLED.addLeds<WS2812B,DATA_PIN,GRB>(leds,NUM_LEDS);
 FastLED.setBrightness(20);
}
 
void loop() {
  // select random leds to turn on and off
  int num_leds_to_turn_on = rand() % 101;

  // randomly choose leds and light them up 
  for(int i=0; i<=num_leds_to_turn_on; i++){
    int led = rand() % NUM_LEDS;
    leds[led] = CRGB::White;
  }

  FastLED.show();
  delay(130);

  // turn all leds off
  for(int i=0; i<=NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }
}
