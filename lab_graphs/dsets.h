/* Your code here! */
#ifndef _DSETS_H
#define _DSETS_H

#include <vector>

class DisjointSets{
  public:
    void addelements(int num);
    int find (int elem);
    void setunion(int a, int b);
    int size(int elem);
  private:
      std::vector<int> uptree;
};








#endif
