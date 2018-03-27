#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel(0,1,1);

  if(x < 100)
    pixel = HSLAPixel(0, 1, 1);
  else
    pixel = HSLAPixel(0, 0, 0);
  return pixel;
}
