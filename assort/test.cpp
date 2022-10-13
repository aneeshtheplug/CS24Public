#include "List.h"
#include <iostream>

// Use this file to test your List class!
// This file won't be graded - do whatever you want.

int main()
{
  List list;
  list.insert("adam");
  list.insert("bella");
  list.insert("abigail");

  std::cout << list.remove(1);
  std::cout << list.remove(1);

  return 0;
}
