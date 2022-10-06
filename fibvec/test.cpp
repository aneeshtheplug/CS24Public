#include "FibVec.h"
#include <iostream>

// Use this file to test your FibVec class!
// This file won't be graded - do whatever you want.

int main()
{
  FibVec fibvec;
  fibvec.insert(5, 0);
  fibvec.insert(7, 0);
  fibvec.push(9);

  std::cout << fibvec.lookup(3);
  return 0;
}
