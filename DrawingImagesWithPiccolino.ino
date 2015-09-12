
#include <Wire.h>
#include <Piccolino_OLED.h>
#include "picco.h"

Piccolino_OLED display;
const char scrn_w_center = 128/2;
const char scrn_h_center = 64/2;
const char piccoPosX = scrn_w_center - (picco_w/2);
const char piccoPosY = scrn_h_center - (picco_h/2);


/* Draws a bitmap at the specified location
** x is horizontal distance from the left of the screen to the left of the image
** y is virtical distance from the top of the screen to the top of the image
** bitmap is a pointer to the start of the image data
** w is the width in pixels of the image
** h is the height in pixels of the image
*
** remarks: the image data contains pixels represented with a single bit. 1 representing white pixels.
**          8 pixels are expected per byte and the data is interpreted horizontally (each byte represents
**          8 horizontal pixels) thus the width of the image must be a multiple of 8.
*/
void drawBitmap(int16_t x, int16_t y, const unsigned char *bitmap, int16_t w, int16_t h) {
  int16_t i, j, byteWidth = (w + 7) / 8;

  for(j=0; j<h; j++) {
    for(i=0; i<w; i++ ) {
      if(0 == (pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7)))) {
        display.drawPixel(x+i, y+j, WHITE);
      }
    }
  }
  display.update();
}

void setup() {
  // put your setup code here, to run once:
  display.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  display.clear();
  drawBitmap(piccoPosX, piccoPosY, picco, picco_w, picco_h);
}
