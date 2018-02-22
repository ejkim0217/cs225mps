#include "list.h"

int main() {
  List<unsigned> list1, list2, list3;
  for (unsigned i = 8; i > 5; i--) { list1.insertFront(i); }
  for (unsigned i = 1; i<3; i++) { list2.insertFront(i);
                                     list3.insertFront(i);}
  list2.print(cout);
  std::cout<<endl;
  list2.reverse();
  list2.print(cout);
  std::cout<<endl;
  list3.reverseNth(2);
  list3.print(cout);
  std::cout<<endl;
  return 0;
}

//Edge cases that I fail:
//1) ReverseNth fails for a single node
//2) reverse and reverseNth fail for two nodes
//3)I keep failing the fucking test case and I have no clue why
//4) ReverseNth fails where n > length_


//Potential problems: I just return when it's a single node
