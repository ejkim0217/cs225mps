/* Your code here! */
#ifndef MAZE_H
#define MAZE_H
#include "cs225/PNG.h"
#include <vector>
#include "dsets.h"
#include <queue>
#include <map>

using namespace cs225;

class SquareMaze{
  public:
    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    vector<int> solveMaze();
    PNG * drawMaze() const;
    PNG * drawMazeWithSolution();
  private:
    vector<int> maze;
    DisjointSets cycle_detection;
    int width_ = 0;
    int height_ = 0;
};


#endif
