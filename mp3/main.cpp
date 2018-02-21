#include "list.h"

int main() {
  List<unsigned> list1, list2, list3;
  for (unsigned i = 8; i  >0; i--) { list1.insertFront(i); }
  for (unsigned i = 1; i < 8; i++) { list2.insertBack(i);
                                     list3.insertBack(i);}
  list1.waterfall();
  list1.print(cout);
  std::cout<<endl;
  list2.reverse();
  list2.print(cout);
  std::cout<<endl;
  list3.reverseNth(3);
  list3.print(cout);
  std::cout<<endl;
  return 0;
}
