/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num){
  for(int i=0; i< num; i++){
    uptree.push_back(-1);
  }
}
int DisjointSets::find (int elem){
  // if(uptree[elem] < 0)
  //   return elem;
  // return find(uptree[elem]);
  if(uptree[elem] < 0)
    return elem;
  int temp = find(uptree[elem]);
  uptree[elem] = temp;
  return temp;
}
void DisjointSets::setunion(int a, int b){


  int root_a = find(a);
  int root_b = find(b);
  if(root_a == root_b)
    return;
  if(uptree[root_a] >= uptree[root_b]){
    uptree[root_a] = uptree[root_a] + uptree[root_b];
    uptree[root_b] = root_a;
  }
  else{
    uptree[root_b] = uptree[root_a] + uptree[root_b];
    uptree[root_a] = root_b;
  }
}
int DisjointSets::size(int elem){
  int size = find(elem);
  return -1*uptree[size];
}
