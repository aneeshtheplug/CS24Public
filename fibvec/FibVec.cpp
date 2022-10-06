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
    return capacitySize;
}

size_t FibVec::count() const
{
    return counter;
}

void FibVec::insert(int value, size_t index)
{
    if (count() < capacity())
    {
        for (int i = counter; i > index; i--)
        {
            fib[i] = fib[i - 1];
        }
        fib[index] = value;

        counter++;
    }
    else if (count() == capacity())
    {
        fibNumber = fibNumber + 1;
        int arraySize = Fibonacci(fibNumber);
        int *newFib = new int[arraySize];
        for (int i = 0; i <= count(); i++)
        {
            if (i == index)
            {
                newFib[i] = value;
            }
            else if (i < index)
            {
                newFib[i] = fib[i];
            }
            else
            {
                newFib[i] = fib[i - 1];
            }
            counter++;
            capacitySize = arraySize;
            delete[] fib;
        }
    }
    else
    {
        throw out_of_range("Invalid index");
    }
}

int FibVec::lookup(size_t index) const
{
    if (index < capacity())
    {
        return fib[index];
    }
    else
    {
        throw out_of_range("Index is invalid");
    }
}

int FibVec::pop()
{
    if (count() > 0)
    {
        int last = fib[counter - 1];
        counter--;
        return last;
    }
    else
    {
        throw underflow_error("Vector is emmpty");
    }
}

void FibVec::push(int value)
{
    fib[counter] = value;
}

int FibVec::remove(size_t index)
{
}

FibVec FibVec::slice(size_t index, size_t count)
{
}