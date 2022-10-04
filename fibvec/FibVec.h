#include <iostream>
#include <vector>

class FibVec
{
public:
    int const capacity();
    int const count();
    void insert(int value, int index);
    int const lookup(int index);
    void pop();
    void push(int value);
    int remove(int index);
    FibVec slice(int index, int count);
};