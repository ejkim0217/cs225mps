/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <math.h>
#include "point.h"

using namespace std;
// Compares two points and returns bool of first < second
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     //checks if values are equal first
     if(first[curDim] == second[curDim])
      return first < second;
    //Otherwise, greater than or less than
    if(first[curDim] < second[curDim])
      return true;
    else
      return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double pot_sum = 0;
     double curr_sum = 0;
     for(int i=0; i< Dim; i++){
       pot_sum = pot_sum + (potential[i]-target[i])*(potential[i]-target[i]);
       curr_sum = curr_sum + (currentBest[i]-target[i])*(currentBest[i]-target[i]);
     }

     if(pot_sum == curr_sum){
      return potential < currentBest;}

     return pot_sum < curr_sum;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     vector<Point<Dim>> points = newPoints;

     root = buildKDTree(points, 0, newPoints.size()-1, 0);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
   unsigned long radius = getDistanceSquared(root->point, query);
   return findNearest(root, query, radius, root->point, 0);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::buildKDTree(vector<Point<Dim>>&points, int begin, int end, int d) //Potentially needs to be const
{
  //Terminal case -- NOT DONE
  if(end - begin < 0)
    return NULL;
  //Find median value
  int mid = floor((begin + end)/2);
  get_median(points, begin, end, mid, d);
  //Make node
  KDTreeNode *curr = new KDTreeNode(points[mid]);
  //make left and right vectors
  //update splitting dimension
  d = d +1;
  if(d == Dim)
    d = 0;
  //Recursive calls
  curr->left = buildKDTree(points, begin, mid-1, d);
  curr->right = buildKDTree(points, mid+1, end, d);
  return curr;

}
template <int Dim>
void KDTree<Dim>::get_median(vector<Point<Dim>>& points, int begin, int end, int mid, int d)
{
  if (begin == end)
    return;
  int fake_mid = partition(points, begin, end, mid, d);
  if(mid == fake_mid)
    return;
  else if (mid < fake_mid){
    get_median(points, begin, fake_mid -1, mid, d);
    return;
  }
  else{
    get_median(points, fake_mid+1, end, mid, d);
    return;
  }
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& points, int begin, int end, int pivot, int d){
  Point<Dim> value = points[pivot];
  swap(points, pivot, end);
  int iterator = begin;
  for(int i = begin; i < end; i++){
    //Equal case
    if(points[i][d] == value[d]){
      if(points[i] < value){
        swap(points, iterator, i);
        iterator++;
      }
    }
    //Generic less than case
    if (points[i][d] < value[d]){
      swap(points, iterator, i);
      iterator++;
    }
  }
  swap(points, end, iterator);
  return iterator;
}

template <int Dim>
void KDTree<Dim>::swap(vector<Point<Dim>>& points, int one, int two)
{
  Point<Dim> value = points[one];
  points[one] = points[two];
  points[two] = value;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearest(KDTreeNode* currentNode, const Point<Dim> targetPoint, unsigned long radius, Point<Dim> bestPoint, int curDim) const
{
  Point<Dim> nearest = bestPoint;
  bool isLeft = false;    //used to check later which subtree to recurse into if it potentially contains a closer point

  //Base case -- goes down correct path to leaf (!= NULL guarantees continuation till leaf)
  if(smallerDimVal(targetPoint, currentNode->point, curDim))//recursing into left subtree if true
  {
    if(currentNode->left != NULL){
      nearest = findNearest(currentNode->left, targetPoint, radius, nearest, (curDim + 1) % Dim);
      isLeft = true;
    }
  }
  else if(smallerDimVal(currentNode->point, targetPoint, curDim)){//recursing into right subtree if true
    if(currentNode->right != NULL)
      nearest = findNearest(currentNode->right, targetPoint, radius, nearest, (curDim + 1) % Dim);
  }
  //Compares leaf
  radius = getDistanceSquared(nearest, targetPoint);
  nearest = getBetterPoint(currentNode->point, nearest, targetPoint);
  radius = getDistanceSquared(nearest, targetPoint);

  if((((currentNode->point)[curDim] - nearest[curDim]) * ((currentNode->point)[curDim] - nearest[curDim])) <= radius)//checking to see if we should recurse into subtree we didn't look at earlier
  {
    if(isLeft){
      if(currentNode->right != NULL)
        nearest = findNearest(currentNode->right, targetPoint, radius, nearest, (curDim + 1) % Dim);
    }
    else{
      if(currentNode->left != NULL){
        nearest = findNearest(currentNode->left, targetPoint, radius, nearest, (curDim + 1) % Dim);
      }
    }
  }
  return nearest;

  // //leaf node
  // if(currentNode->left == NULL && currentNode->right == NULL){
  //   return bestPoint = currentNode->point;
  // }
  // //Traverse left
  // if(currentNode->left != NULL && smallerDimVal(targetPoint, currentNode->point,curDim)){
  //   bestPoint = findNearest(currentNode->left, targetPoint, radius, bestPoint, (curDim+1)% Dim);
  // }
  // //Traverse right
  // if(currentNode->right != NULL && smallerDimVal(currentNode->point, targetPoint, curDim)){
  //   bestPoint = findNearest(currentNode->right, targetPoint, radius, bestPoint, (curDim+1)% Dim);
  // }
  //
  // if(shouldReplace(targetPoint, bestPoint, currentNode->point))
  //   bestPoint = currentNode->point;
  //
  // return bestPoint;
}

template <int Dim>
Point<Dim> KDTree<Dim>::getBetterPoint(Point<Dim> currentPoint, Point<Dim> bestPoint, const Point<Dim> targetPoint) const
{
  if(shouldReplace(targetPoint, bestPoint, currentPoint))
    return currentPoint;

  return bestPoint;

  /*
  unsigned long curDist = getDistanceSquared(currentPoint, targetPoint);
  if(curDist < radius){
    //radius = curDist;
    return currentPoint;
  }
  else if(curDist == radius){
    if(currentPoint < bestPoint)
      return currentPoint;
  }
  return bestPoint;*/
}

template <int Dim>
unsigned long KDTree<Dim>::getDistanceSquared(Point<Dim> point1, Point<Dim> point2) const
{
  unsigned long dist = 0;
  for(int curDim = 0; curDim < Dim; curDim++){
    dist += ((point1[curDim] - point2[curDim]) * (point1[curDim] - point2[curDim]));
  }
  return dist;
}
