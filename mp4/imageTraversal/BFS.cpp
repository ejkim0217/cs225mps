#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  pngbfs = png;
  start_ = start;
  tolerancebfs = tolerance;
  q.push(start_);
  list = new int*[png.width()];
  for(unsigned i=0; i<png.width(); i++){
    list[i] = new int[png.height()];
    for(unsigned j=0; j<png.height(); j++){
      list[i][j] = 0;
    }
  }
}
/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal * traversal = new BFS(pngbfs, start_, tolerancebfs);
  return ImageTraversal::Iterator(traversal);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */

  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  HSLAPixel origin = pngbfs.getPixel(start_.x, start_.y);
  if(point.x < (pngbfs.width()-1)){
    double real_tolr = getcalculateDelta(pngbfs.getPixel(point.x+1, point.y), origin);
    if(real_tolr < tolerancebfs && list[point.x+1][point.y] == 0){
      Point right(point.x+1, point.y);
      q.push(right);
    }
  }
  if(point.y < (pngbfs.height() -1)){
    double real_told = getcalculateDelta(pngbfs.getPixel(point.x, point.y+1), origin);
    if(real_told< tolerancebfs && list[point.x][point.y+1] == 0){
      Point down(point.x, point.y+1);
      q.push(down);
    }
  }
  if(point.x > 0 && point.x <= (pngbfs.width()-1) ){
    double real_toll = getcalculateDelta(pngbfs.getPixel(point.x-1, point.y), origin);
    if(real_toll < tolerancebfs && list[point.x-1][point.y] == 0){
      Point left(point.x-1, point.y);
      q.push(left);
    }
  }
  if(point.y > 0 && point.y <= (pngbfs.height() -1)){
    double real_tolu = getcalculateDelta(pngbfs.getPixel(point.x, point.y-1), origin);
    if(real_tolu < tolerancebfs && list[point.x][point.y-1] == 0){
      Point up(point.x, point.y -1);
      q.push(up);
    }
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point top = q.front();
  q.pop();
  return top;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return q.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  if(q.empty())
    return true;
  else
    return false;
}

BFS::~BFS(){
  for(unsigned i=0; i<pngbfs.width(); i++){
    delete list[i];
  }
  delete list;
}
