#include <iostream>
#include "FibVec.h"
#include <vector>
#include <stdexcept>
using namespace std;

FibVec::FibVec()
{
    fib = new int[1];
}

FibVec::~FibVec()
{
    delete[] fib;
}

int Fibonacci(int n)
{
    if (n <= 1)
    {
        return n;
    }
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

size_t FibVec::capacity() const
{
}

size_t FibVec::count() const
{
    return sizeof(fib) / sizeof(fib[0]);
}

void FibVec::insert(int value, size_t index)
{
    int size = count();
    if (index < size)
    {
        for (int i = size; i > index; i--)
        {
            fib[i] = fib[i - 1];
        }
        fib[index] = value;
    }
    counter++;
}

int FibVec::lookup(size_t index) const
{
    return fib[index];
}

int FibVec::pop()
{
    if (count() > 0)
    {
        int last = fib[counter - 1];
        counter--;
        return last;
    }
}

void FibVec::push(int value)
{
    int size = count();
    fib[size] = value;
}

int FibVec::remove(size_t index)
{
}

FibVec FibVec::slice(size_t index, size_t count)
{
}