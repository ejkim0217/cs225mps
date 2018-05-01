
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
  // PNG png;
  // png.readFromFile("tests/i.png");
  //
  // FloodFilledImage image(png);
  // BFS dfs(png, Point(40, 40), 0.05);
  // BFS bfs(png, Point (0, 0), 1.0);
  // MyColorPicker derived;
  // RainbowColorPicker rainbow(.1);
  //
  // image.addFloodFill(bfs, derived);
  // image.addFloodFill( dfs, rainbow );
  //
  // Animation animation = image.animate(1000);
  //
  // PNG firstFrame = animation.getFrame(0);
  // PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  //
  // firstFrame.writeToFile("mycolorpicker-first.png");
  // lastFrame.writeToFile("mycolorpicker-last.png");
  // animation.write("mycolorpicker.gif");
  PNG png;
  png.readFromFile("mp7creative.png");

  FloodFilledImage image(png);
  BFS bfs(png, Point (1, 1), 1.0);
  HSLAPixel color(231, 1, 0.5);
  SolidColorPicker derived(color);


  image.addFloodFill(bfs, derived);

  Animation animation = image.animate(1000);

  PNG firstFrame = animation.getFrame(0);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );

  firstFrame.writeToFile("mycolorpicker-first.png");
  lastFrame.writeToFile("mycolorpicker-last.png");
  animation.write("mycolorpicker.gif");




  return 0;
}
