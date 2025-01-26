#include <FastLED.h>
#define NUM_LEDS 512
#define DATA_PIN 6
CRGB leds[NUM_LEDS];

uint8_t matrix_width = 32;
uint8_t matrix_height = 16; 
uint8_t single_display_height = 8; 

CRGBPalette16 myPalette = RainbowColors_p;

void light_up_specific_led(int x, int y, bool on) {
  // x should be an int 1 - 32
  // y should be an int 1 - 16
  int x_comp;
  int y_comp;
  
  if(y<=8){ // we are in panel 1
    x_comp = (x-1)*8;
    if(x%2 == 1){  // x is odd
      y_comp = 8-y;
    } else {
      y_comp = y-1;
    }
  } else{ // we are in panel 2
    x_comp = 32*16-(x-1)*8;
    if(x%2 == 1){  // x is odd
      y_comp = 8-y;
    } else {
      y_comp = y-17;
    }
  }

  int i = x_comp + y_comp;
  if(on){
    leds[i] = CRGB::Red;
  }else{
    leds[i] = CRGB::Black;
  }
}

void setup() {   
 FastLED.addLeds<WS2812B,DATA_PIN,GRB>(leds,NUM_LEDS);
 FastLED.setBrightness(20);
}
 
void loop() {
  for(int x=1; x<=16; x++){
      light_up_specific_led(x, x, true);
  }
    for(int x=17; x<32; x++){
      light_up_specific_led(x, 32-x, true);
  }
  FastLED.show();
}
