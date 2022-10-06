#include <iostream>
#include <cstddef>
#include <vector>

class FibVec
{
private:
    int *fib;
    size_t counter = 0;
    size_t capacitySize = 1;
    size_t fibNumber = 1;

public:
    FibVec();
    ~FibVec();
    int Fibonnaci(int n);
    size_t capacity() const;
    size_t count() const;
    void insert(int value, size_t index);
    int lookup(size_t index) const;
    int pop();
    void push(int value);
    int remove(size_t index);
    FibVec slice(size_t, size_t) const;
};