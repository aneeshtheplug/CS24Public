#include "FibVec.h"
#include <iostream>

// Use this file to test your FibVec class!
// This file won't be graded - do whatever you want.

int main()
{
  FibVec fibvec;
  fibvec.insert(5, 0);
  fibvec.insert(7, 0);
  fibvec.lookup(0);

  std::cout << fibvec.lookup(0);
  return 0;
}
