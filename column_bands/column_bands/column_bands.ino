#include <FastLED.h>

#define NUM_LEDS 256 * 2  // Total number of LEDs in both arrays
#define DATA_PIN 6        // Data pin for the LED strip

CRGB leds[NUM_LEDS];

uint8_t matrix_width = 64;  // Total width of both arrays (32 + 32)
uint8_t matrix_height = 8;  // Height of each array

CRGBPalette16 myPalette = RainbowColors_p;  // Rainbow color palette
uint8_t colour_index = 0;                   // Start color index
uint8_t colour_increment = 8;               // Increment for color transitions

void setup() {
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
}

void loop() {
  // Define the range of active rows for the band (3 rows at a time)
  static int band_start = 0;
  static int band_end = 2;

  // Clear all LEDs
  fill_solid(leds, NUM_LEDS, CRGB::Black);

  // Light up the active band across both arrays
  for (int y = band_start; y <= band_end; y++) {
    // Light up the first array (columns 0 to 31)
    for (int x = 0; x < 32; x++) {
      int index = x * matrix_height + y;
      leds[index] = ColorFromPalette(myPalette, colour_index);
    }

    // Light up the second array (columns 32 to 63)
    for (int x = 32; x < 64; x++) {
      int index = x * matrix_height + y;
      leds[index] = ColorFromPalette(myPalette, colour_index);
    }
  }

  // Show the updated LEDs
  FastLED.show();

  // Update the color index for the next frame
  colour_index += colour_increment;
  if (colour_index >= 256) {
    colour_index = 0;
  }

  // Move the band one row forward
  band_start++;
  band_end++;

  // Wrap around the band when it reaches the end
  if (band_start >= matrix_height) {
    band_start = 0;
    band_end = 2;
  }

  // Add a delay to control the animation speed
  delay(100);
}
