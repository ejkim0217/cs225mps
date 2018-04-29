/* Your code here! */
#include "maze.h"
#include "dsets.h"
#include "cs225/PNG.h"

SquareMaze::SquareMaze(){

}
void SquareMaze::makeMaze(int width, int height){
  //Makes vector the correct rectangular size with walls
  /*
  0 = no walls
  1 = right wall
  2 = down wall
  3 = right + down wall
  */
  //Make maze vector
  maze.clear();
  maze.resize(width * height);
  width_ = width;
  height_ = height;
  for(int i=0; i < width*height; i++){
    maze[i] = 3;
  }
  //Generate a DisjointSets to detect cycles
  DisjointSets cycle_detection;
  cycle_detection.addelements(width * height);
  //Remove walls till there is only one uptree, which size
  while(cycle_detection.size(0) < (width * height)){
    //Get random element
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
      if(rando == 1)
        setWall(element%width, element/width, 0, false);
      else
        setWall(element%width, element/width, 1, false);
    }
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
  int value = maze[y*width_+x];
  //Check right
  if(dir == 0 && (value == 0 || value == 2))
    return true;
  //Check down
  if(dir == 1 && (value == 0 || value == 1))
    return true;
  //Check left
  if(dir == 2 && (maze[y*width_ + x -1] == 0 || maze[y*width_ + x -1] == 2))
    return true;
  //Check up
  if(dir == 3 && (maze[(y-1)*(width_) + x] == 0 || maze[(y-1)*(width_) + x] == 1))
    return true;

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
    //Insert left wall
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
  vector<int> path;
  return path;
}
PNG * SquareMaze::drawMaze() const{
  PNG * mazePNG = new PNG(width_*10+1, height_*10+1);
  //Blacken top row
  for(int i =0; i<width_*10+1; i++){
    HSLAPixel pix = mazePNG->getPixel(i, 0);
    if(i > 0 && i < 10)
      pix.l = 0;
  }
  //Blacken left most row
  for(int i=0; i<height_*10+1; i++){
    HSLAPixel pix = mazePNG->getPixel(0, i);
    pix.l = 0;
  }
  //Build walls
  for(int i =0; i < height_; i++){
    for(int j=0; j< width_; j++){
      int value = maze[i*width_+j];
      //Check for right wall
      if(value == 3 || value == 1){
        for(int k = 0; k <= 10; k++){
          HSLAPixel pix = mazePNG->getPixel((j+1)*10, i*10+k);
          pix.l = 0;
        }
      }
      //Check for left wall
      if(value == 3 || value == 2){
        for(int k = 0; k <= 10; k++){
          HSLAPixel pix = mazePNG->getPixel(j*10+k, (i+1)*10);
          pix.l = 0;
        }
      }
    }
  }

  return mazePNG;
}
PNG * SquareMaze::drawMazeWithSolution(){
  PNG * solPNG = new PNG();
  return solPNG;
}
