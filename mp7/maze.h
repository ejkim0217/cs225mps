#ifndef DMAZE_H_
#define DMAZE_H_
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
#include <list>
#include <math.h>
#include <tuple>
using namespace std;
using namespace cs225;

class SquareMaze{
	public:
		SquareMaze();
		void makeMaze(int width, int height);
		void makeMazeI(int width, int height);
		bool canTravel(int x, int y, int dir) const;
		void setWall(int x, int y, int dir, bool exists);
		vector<int> solveMaze();
		PNG * drawMaze() const;
		PNG * drawMazeWithSolution();
	private:
		int width_ = 0;
		int height_ = 0;
		DisjointSets cycle_detection;
		vector<int> maze;
		vector<pair<bool,bool>> wbool;	//right is first, down is second
		vector<tuple<int, int, int>> xyverts;
};
#endif
