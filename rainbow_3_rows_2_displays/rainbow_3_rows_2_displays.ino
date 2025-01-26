#include <FastLED.h>
#define NUM_LEDS 512
#define DATA_PIN 6
CRGB leds[NUM_LEDS];

uint8_t matrix_width = 32;    // Number of rows
uint8_t matrix_height = 16;   // Number of LEDs in a row
uint8_t single_display_height = 8; 

CRGBPalette16 myPalette = RainbowColors_p;  // rainbow palette can be called with any int 0-255
uint8_t colour_index = 0;  // start the loop at 0
uint8_t colour_increment = 8;  // to get 32 diff colours we'll want to index 0, 7, 15, 23 etc..

// Function to return the LED indexes for a given row
void get_led_indexes_for_row(int row_number, int* row) {
  
    // Add the indexes for the first display (e.g 0-7)
    int i = row_number * single_display_height;
    for (int n = 0; n < single_display_height; n++) {
      row[n] = i;
      i++;
    }

    // And the second display (all the values of 511-i, e.g. 503-511)
    int j = 511 - i + 1;
    for (int n = single_display_height; n < matrix_height; n++) {
      row[n] = j;
      j++;
    }
}

void setup() {   
 FastLED.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
 FastLED.setBrightness(20);
}
 
void loop() {
  int led;
  int row[matrix_height];

  for (int x=0; x<matrix_width; x++) {

    get_led_indexes_for_row(x, row);
    for (int i = 0; i < matrix_height; i++) {
      led = row[i];
      leds[led] = ColorFromPalette(myPalette, colour_index);
    }

    int row_to_turn_off = (x - 3); 
    if(row_to_turn_off < 0){
      row_to_turn_off = row_to_turn_off + matrix_width;
    }

    get_led_indexes_for_row(row_to_turn_off, row);
    for (int i = 0; i < matrix_height; i++) {
      led = row[i];
      leds[led] = CRGB::Black;
    }

    FastLED.show();
    
    // each loop increase the colour, until we get to 255, then reset to 0
    colour_index = colour_index + colour_increment;
    if(colour_index>=255){
      colour_index=0;
    }
    
    delay(60);
  }
}
