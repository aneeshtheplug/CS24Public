#include "Set.h"
#include <iostream>
using namespace std;

// Use this file to test your Set class.
// This file won't be graded - do whatever you want.

int main()
{
  Set set;

  set.insert("d");
  set.insert("b");
  set.insert("e");
  set.insert("a");
  set.insert("c");
  set.insert("f");
  cout << set.count();
  cout << set.remove("b");
  set.print();
  cout << set.count();

  return 0;
}
