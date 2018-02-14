#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image dragon;    dragon.readFromFile("dragon.png");
  Image cyborg;    cyborg.readFromFile("cyborg.png");
  Image i;         i.readFromFile("tests/i.png");
  Image wing;      wing.readFromFile("wing.png");

  StickerSheet sheet(dragon, 3);
  sheet.addSticker(cyborg, 20, 200);
  sheet.addSticker(i, 600, 600);
  sheet.addSticker(wing, 800, 600);

  sheet.render().writeToFile("myImage.png");
  return 0;
}
