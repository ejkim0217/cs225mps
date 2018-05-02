#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace cs225;

int main()
{
    // Write your own main here
  	SquareMaze maze;
  	PNG * actualOutput = maze.drawCreativeMaze();
  	actualOutput->writeToFile("mp7creative"+ string(".png"));
    return 0;
}
