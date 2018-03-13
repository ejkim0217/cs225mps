
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;
PNG getTestPNG() {
  PNG png(6, 6);
  HSLAPixel blackPixel(180, 1, 0);

  for (unsigned i = 0; i < 6; i++) {
    for(unsigned j=0; j<6; j++){
        png.getPixel(i, j) = blackPixel;
    }
  }

  return png;
}



int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */
  PNG png = getTestPNG();
  Point startPoint(2, 2);

  BFS t(png, startPoint, 0.2);
  unsigned count = 0;
  for (const Point & p : t) {
    std::cout<<p<<endl;
    count++;
  }




  return 0;
}
