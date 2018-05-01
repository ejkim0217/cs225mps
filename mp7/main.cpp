#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace cs225;

int main()
{
    // Write your own main here
  	SquareMaze maze;
  	maze.makeMaze(10, 15);
  	maze.solveMaze();
  	PNG * actualOutput = maze.drawMazeWithSolution();
  	actualOutput->writeToFile("mp7creative"+ string(".png"));
    return 0;
}
