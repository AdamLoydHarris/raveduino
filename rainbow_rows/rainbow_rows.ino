#include <FastLED.h>
#define NUM_LEDS 256
#define DATA_PIN 6
CRGB leds[NUM_LEDS];

uint8_t matrix_width = 32;
uint8_t matrix_height = 8;

CRGBPalette16 myPalette = RainbowColors_p;  // rainbow palette can be called with any int 0-255
uint8_t colour_index = 0;  // start the loop at 0
uint8_t colour_increment = matrix_height;  // to get 32 diff colours we'll want to index 0, 7, 15, 23 etc..


void setup() {   
 FastLED.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
 FastLED.setBrightness(20);
}
 
void loop() {
  // loop through rows
  for (int x=0; x<=matrix_width; x++) {

    // get index of first and last led in the row
    int i_start = x * matrix_height;
    int i_end = i_start + matrix_height - 1;

    // loop though these leds and change their colour
    for (int i = i_start; i <= i_end; i++) {
      leds[i] = ColorFromPalette(myPalette, colour_index);
    }

    // turn off the leds in the previous row (except for when x=0)
    if (x>=1){
      i_start = (x-1) * matrix_height;
      i_end = i_start + matrix_height - 1;

      // loop though these leds and change their colour
      for (int i = i_start; i <= i_end; i++) {
        leds[i]=CRGB::Black;
      }
    }

    FastLED.show();

    // each loop increase the colour, until we get to 255, then reset to 0
    colour_index = colour_index + colour_increment;
    if(colour_index>=255){
      colour_index =0;
    }
    
    delay(60);
  }
}