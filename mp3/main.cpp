#include "list.h"

int main() {
  List<unsigned> list1, list2, list3;
  for (unsigned i = 1; i < 10; i++) { list1.insertBack(i); }
  for (unsigned i = 1; i<8; i++) { list2.insertBack(i);}
  // list1.insertBack(3);
  // list1.insertBack(8);
  // list1.insertBack(100);
  // list2.insertBack(2);
  // list2.insertBack(8);
  // list2.insertBack(99);
  list1.print(cout);
  std::cout<<endl;
  list2.print(cout);
  std::cout<<endl;
  list1.mergeWith(list2);
  list1.print(cout);
  std::cout<<endl;


  return 0;
}
