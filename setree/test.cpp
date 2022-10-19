#include "Set.h"
#include <iostream>
using namespace std;

// Use this file to test your Set class.
// This file won't be graded - do whatever you want.

int main()
{
  Set set;

  set.insert("Jack");
  cout << set.count() << endl;
  set.insert("Bob");
  set.insert("Adam");
  set.insert("Zach");
  set.insert("George");
  set.print();
  cout << endl;
  set.remove("George");
  set.print();

  return 0;
}
