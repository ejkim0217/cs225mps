#include "maze.h"
#include <vector>
#include <iostream>
#include "cs225/HSLAPixel.h"
#include <list>
#include <math.h>
#include <queue>
#include <map>
#include "maze.h"
#include "dsets.h"
#include "cs225/PNG.h"


SquareMaze::SquareMaze(){

}
void SquareMaze::makeMaze(int width, int height){
  //Makes vector the correct rectangular size with walls
  /*
	  	00 = 0 = no walls
	  	01 = 1 = right wall
	  	10 = 2 = down wall
	  	11 = 3 = right + down wall
  */
	//Make maze vector
	maze.clear();
	maze.resize(width * height);
	width_ = width;
	height_ = height;
	for(int i=0; i < width*height; i++){	//Initialize all maze pieces to have right and downs
		maze[i] = 3;
	}
	//Generate a DisjointSets to detect cycles
	cycle_detection.addelements(width * height);
	//Remove walls till there is only one uptree, which size
	while(cycle_detection.size(0) < (width * height)){
		//Get random index
		int element = rand() % (width * height);
		// 0 = down, 1 = right
		int rando = rand() % 2;
		//If down, add by width to get down value
		if(rando == 0)
			rando = width;
		//Checks if we are on the far right perimeter case
		if((element+1) % width == 0){
			rando = width;
		}
		//Checks if we are on the bottom row case
		if(element >= width* (height-1)){
			rando = 1;
		}
		if(element == width * height -1)
			continue;

		//Remove wall between element and rando
		int a = cycle_detection.find(element);
		int b = cycle_detection.find(element + rando);
		if(a != b){
			//Update DisjointSets
			cycle_detection.setunion(a, b);
			//Update maze vector
			if(rando == 1){
				setWall(element%width, element/width, 0, false);
			}
			else{
				setWall(element%width, element/width, 1, false);
			}
		}
	}
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
	if ((0 <= x)&&(x < width_)&&(0 <= y)&&(y < height_)){	//If within dimensions
		int value = maze[(y*width_) + x];
		//CHECK RIGHT. If stays within dimensions
		if ((dir == 0)&&((x+1) < width_)){
			if (value == 0 || value == 2){return true;}
		}
		//CHECK DOWN. If stays within
		else if ((dir == 1)&&((y+1) < height_)){
			if (value == 0 || value == 1){return true;}
		}
		//CHECK LEFT
		else if ((dir == 2)&&(0 <= (x-1))){
			if (maze[(y*width_) + x-1] == 0 || maze[(y*width_) + x-1] == 2){return true;}
		}
		//CHECK UP
		else if ((dir == 3)&&(0 <= (y-1))){
			if (maze[(y-1)*(width_) + x] == 0 || maze[(y-1)*(width_) + x] == 1){return true;}
		}
	}

	return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
  int value = maze[y*width_+x];
  //Insert wall
  if(exists){
    //Insert right wall
    if(dir == 0){
      if(value == 0 || value == 1){
        maze[y*width_+x] = 1;
        return;
      }
      else{
        maze[y*width_+x] = 3;
        return;
      }
    }
    //Insert down wall
    else{
      if(value == 0 || value == 2){
        maze[y*width_+x] = 2;
        return;
      }
      else{
        maze[y*width_+x] = 3;
        return;
      }
    }
  }
  //Erase wall
  else{
    //Erase right wall
    if(dir == 0){
      if(value == 3){
        maze[y*width_+x] = 2;
        return;
      }
      else if (value == 1){
        maze[y*width_+x] = 0;
        return;
      }
    }
    //Erase down wall
    else{
      if(value == 3){
        maze[y*width_+x] = 1;
        return;
      }
      else if (value == 2){
        maze[y*width_+x] = 0;
        return;
      }
    }
  }
}

vector<int> SquareMaze::solveMaze(){
  vector<int> bestpath;
  queue<int> q;
  q.push(0);		//Starting Index
  //Initialize to -1
  //Write down once visited
  std::map<int, int> my_map;
  my_map.insert(std::pair<int,int>(0, 0));
  std::map<int, int> parent;	//For backtracing purposes
  int count = 0;

  while (!q.empty()){	//Initial BFS
      int element = q.front();
      q.pop();
      int x = element % width_;
      int y = element / width_;
      for (int dir = 0; dir < 4; ++dir){
      	int nelement;
      	if (dir == 0){ nelement = (y*width_) + (x+1);}	//RIGHT
      	if (dir == 1){ nelement = ((y+1)*width_) + x;}	//DOWN
      	if (dir == 2){ nelement = (y*width_) + (x-1);}	//LEFT
      	if (dir == 3){ nelement = ((y-1)*width_) + x;}	//UP
      	if (canTravel(x,y,dir) && my_map.find(nelement) == my_map.end()){
      		q.push(nelement);
      		my_map.insert(std::pair<int, int>(nelement, my_map[element]+1));
      		parent[nelement] = element;
      	}
      }
      /*  SAME SHIT BUT JUST MESSIER
      if(canTravel(x, y, 0) && my_map.find(y*width_+x+1) == my_map.end()){
        q.push((y*width_) + x+1);		//PUSH NEXT
        my_map.insert(std::pair<int, int>(y*width_+x+1, my_map[element]+1));
        parent.insert(std::pair<int, int>(y*width_+x+1, element));
      }
      if(canTravel(x, y, 1) && my_map.find((y+1)*width_+x) == my_map.end()){
        q.push(((y+1)*width_) + x);		//PUSH NEXT
        my_map.insert(std::pair<int, int>((y+1)*width_+x, my_map[element]+1));
        parent.insert(std::pair<int, int>((y+1)*width_+x, element));
      }
      if(canTravel(x, y, 2) && my_map.find(y*width_+x-1) == my_map.end()){
        q.push((y*width_) + x-1);		//PUSH NEXT
        my_map.insert(std::pair<int, int>(y*width_+x-1, my_map[element]+1));
        parent.insert(std::pair<int, int>(y*width_+x-1, element));
      }
      if(canTravel(x, y, 3) && my_map.find((y-1)*width_+x) == my_map.end()){
        q.push(((y-1)*width_) + x);		//PUSH NEXT
        my_map.insert(std::pair<int, int>((y-1)*width_+x, my_map[element]+1));
        parent.insert(std::pair<int, int>((y-1)*width_+x, element));
      }*/
	}
	unsigned max_dist = 0;
	int bestdest = 0;
	for(int x = 0; x < width_ ; ++x){		//for each square on bottom row
		int dest = ((height_-1)*width_) + x;	//bottom row element
		vector<int> temppath;
		//walk backwards to find the largest path
		while(dest != 0){
			int rdir = dest - parent[dest];	//check reverse direction
			//INDEX DELTA RIGHT
			if(rdir == 1){
				temppath.push_back(0);	//RIGHT dir = 0
			}
			//INDEX DELTA LEFT
			else if(rdir == -1){
				temppath.push_back(2);	//LEFT dir = 2
			}
			//INDEX DELTA DOWN
			else if(rdir == width_){
				temppath.push_back(1);	//DOWN dir = 1
			}
			//INDEX DELTA UP
			else if(rdir == -width_){
				temppath.push_back(3);	//UP dir = 1
			}
			dest = parent[dest];
		}
		if(max_dist < temppath.size()){	//If temppath size is larger than current max
			max_dist = temppath.size();	//Replace the current max with the temp path size
			bestpath = temppath;					//Set bestpath to temppath
			bestdest = dest;					//Mark bestdest with temp dest of bottom row
		}
	}

  //Reverse the vector path
  std::reverse(bestpath.begin(), bestpath.end());
  return bestpath;
}

PNG * SquareMaze::drawMaze() const{
  PNG * mazePNG = new PNG(width_*10+1, height_*10+1);
  //Blacken top row
  for(int i = 10; i<width_*10+1; i++){
    HSLAPixel & pix = mazePNG->getPixel(i, 0);
    pix.l = 0;
  }
  //Blacken left most row
  for(int i=0; i<height_*10+1; i++){
    HSLAPixel & pix = mazePNG->getPixel(0, i);
    pix.l = 0;
  }
  //Build walls
  for(int x = 0; x < width_; x++){
    for(int y = 0; y < height_; y++){
      int value = maze[(y*width_) + x];	//Get value for index

      //CHECK RIGHT WALL
      if(value == 3 || value == 1){			//if both or just right
        for(int k = 0; k <= 10; k++){		//DRAW RIGHT
          HSLAPixel& pix = mazePNG->getPixel((x+1)*10, y*10+k);
          pix.l = 0;
        }
      }
      //CHECK DOWN WALL
      if(value == 3 || value == 2){			//If both or just down
        for(int k = 0; k <= 10; k++){		//DRAW DOWN
          HSLAPixel& pix = mazePNG->getPixel(x*10+k, (y+1)*10);
          pix.l = 0;
        }
      }
    }
  }

  return mazePNG;
}

PNG * SquareMaze::drawMazeWithSolution(){
	PNG * sol = drawMaze();
	vector<int> bestpath;
	int x = 5;
  int y = 5;
  bestpath = solveMaze();
	for (int dir : bestpath){
      for (int p = 1; p < 11; ++p){//color 11 pixels in a line
			HSLAPixel& pix = sol->getPixel(x,y);
			pix.h = 0;
			pix.s = 1;
			pix.l = .5;
			pix.a = 1;

			if (dir == 0){			//RIGHT
				x++;	//update x
			}
			if (dir == 1){			//DOWN
				y++;	//update y
			}
			if (dir == 2){			//LEFT
				x--;	//update x
			}
			if (dir == 3){			//UP
				y--;	//update y
			}
		}
		HSLAPixel& pix = sol->getPixel(x,y);
		pix.h = 0;
		pix.s = 1;
		pix.l = .5;
		pix.a = 1;
	}
	for(int k =1; k < 10; k++){
		HSLAPixel& pix = sol->getPixel(x+k-5, y+5);
		pix.l = 1;
	}
  return sol;
}
