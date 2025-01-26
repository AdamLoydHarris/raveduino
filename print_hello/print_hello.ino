#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6

// MATRIX DECLARATION:
// Parameter 1 = width of the matrix
// Parameter 2 = height of the matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags
//   First two are the position of the first LED in the matrix = NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   Next one indicates how the LEDs are arranged = NEO_MATRIX_COLUMNS
//   Next one indicates rows how the columns proceed = NEO_MATRIX_ZIGZAG
// Parameter 5 = pixel type flags = NEO_GRB + NEO_KHZ800

int matrix_width = 32;
int matrix_height = 8;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(matrix_width, matrix_height, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(100, 0, 0), matrix.Color(0, 100, 0), matrix.Color(0, 0, 10) };

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(100);
  matrix.setTextColor(colors[0]);
}

int x    = matrix.width();
int pass = 0; // this increments after each loop to change the text colour

void loop() {
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);  // start at 32, 0
  matrix.print(F("Hello"));  // print the word hello in every loop
  if(--x < -36) {  // x=x-1 in each loop
    x = matrix_width;  // once we get to the end of the board reset x to 32
    if(++pass >= 3)  // and pass=pass+1
      pass = 0;  // once pass gets to 3, set it back to 0, so the colours continue to cycle
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  delay(100);
}