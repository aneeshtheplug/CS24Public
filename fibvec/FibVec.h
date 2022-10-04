#include <iostream>
#include <cstddef>
#include <vector>

class FibVec
{
public:
    FibVec();
    int capacity() const;
    int count() const;
    void insert(int value, int index);
    int lookup(int index) const;
    void pop();
    void push(int value);
    int remove(int index);
    FibVec slice(int index, int count);
};