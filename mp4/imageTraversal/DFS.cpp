#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  pngdfs = png;
  startdfs = start;
  tolerancedfs = tolerance;
  s.push(startdfs);
  list = new int*[png.width()];
  for(unsigned i=0; i<png.width(); i++){
    list[i] = new int[png.height()];
    for(unsigned j=0; j<png.height(); j++){
      list[i][j] = 0;
    }
  }
  list[startdfs.x][startdfs.y] = 1;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal* traversal = new DFS(pngdfs, startdfs, tolerancedfs);
  return ImageTraversal::Iterator(traversal);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  HSLAPixel origin = pngdfs.getPixel(startdfs.x, startdfs.y);
  if(point.x < (pngdfs.width()-1)){
    double real_tolr = getcalculateDelta(pngdfs.getPixel(point.x+1, point.y), origin);
    if(real_tolr < tolerancedfs && list[point.x+1][point.y] == 0){
      Point right(point.x+1, point.y);
      s.push(right);
      list[right.x][right.y] = 1;
    }
  }
  if(point.y < (pngdfs.height() -1)){
    double real_told = getcalculateDelta(pngdfs.getPixel(point.x, point.y+1), origin);
    if(real_told< tolerancedfs && list[point.x][point.y+1] == 0){
      Point down(point.x, point.y+1);
      s.push(down);
      list[down.x][down.y] = 1;
    }
  }
  if(point.x > 0 && point.x <= (pngdfs.width()-1) ){
    double real_toll = getcalculateDelta(pngdfs.getPixel(point.x-1, point.y), origin);
    if(real_toll < tolerancedfs && list[point.x-1][point.y] == 0){
      Point left(point.x-1, point.y);
      s.push(left);
      list[left.x][left.y] = 1;
    }
  }
  if(point.y > 0 && point.y <= (pngdfs.height() -1)){
    double real_tolu = getcalculateDelta(pngdfs.getPixel(point.x, point.y-1), origin);
    if(real_tolu < tolerancedfs && list[point.x][point.y-1] == 0){
      Point up(point.x, point.y -1);
      s.push(up);
      list[up.x][up.y] = 1;
    }
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point top = s.top();
  s.pop();
  return top;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return s.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  if(s.empty())
    return true;
  else
    return false;
}
