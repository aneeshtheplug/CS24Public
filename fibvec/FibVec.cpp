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
    if (index > count())
    {
        throw out_of_range("Invalid index");
    }
    else
    {
        if (count() < capacity())
        {
            for (size_t i = count(); i > index; --i)
            {
                fib[i] = fib[i - 1];
            }
            fib[index] = value;
        }
        else if (count() == capacity())
        {
            int fibVal = Fibonacci(fibNumber);
            while (size_t(fibVal) < count() + 1)
            {
                fibNumber = fibNumber + 1;
                fibVal = Fibonacci(fibNumber);
            }
            int arraySize = fibVal;
            int *newFib = new int[arraySize];
            for (size_t i = 0; i < index; i++)
            {
                newFib[i] = fib[i];
            }
            newFib[index] = value;
            for (size_t i = index + 1; i <= count(); i++)
            {
                newFib[i] = fib[i - 1];
            }
            capacitySize = arraySize;
            delete[] fib;
            fib = newFib;
        }
        counter++;
    }
}

int FibVec::lookup(size_t index) const
{
    if (index < count())
    {
        return fib[index];
    }
    else
    {
        throw out_of_range("Index is invalid");
        return -1;
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
        throw underflow_error("Vector is empty");
        return -1;
    }
}

void FibVec::push(int value)
{
    if (count() < capacity())
    {
        fib[counter] = value;
    }
    else if (count() == capacity())
    {
        int fibVal = Fibonacci(fibNumber);
        while (size_t(fibVal) < count() + 1)
        {
            fibNumber = fibNumber + 1;
            fibVal = Fibonacci(fibNumber);
        }
        int arraySize = fibVal;
        int *newFib = new int[arraySize];
        for (size_t i = 0; i < count(); i++)
        {
            newFib[i] = fib[i];
        }
        newFib[counter] = value;
        capacitySize = arraySize;
        delete[] fib;
        fib = newFib;
    }
    counter++;
}

int FibVec::remove(size_t index)
{
    if (index >= count())
    {
        throw out_of_range("Index invalid");
    }
    else
    {
        if ((fibNumber > size_t(2)) && (count() - size_t(1)) < size_t(Fibonacci(fibNumber - 2)))
        {
            int val = fib[index];
            fibNumber = fibNumber - 1;
            int arraySize = Fibonacci(fibNumber);
            int *newFib = new int[arraySize];
            for (size_t i = 0; i < (count() - size_t(1)); i++)
            {
                if (i < index)
                {
                    newFib[i] = fib[i];
                }
                else
                {
                    newFib[i] = fib[i + 1];
                }
            }
            counter--;
            capacitySize = arraySize;
            delete[] fib;
            fib = newFib;
            return val;
        }
        else
        {
            int val = fib[index];
            for (size_t i = 0; i < (count() - size_t(1)); i++)
            {
                if (i >= index)
                {
                    fib[i] = fib[i + 1];
                }
            }
            counter--;
            return val;
        }
    }
}

FibVec FibVec::slice(size_t, size_t) const
{
    FibVec newfib;
    return newfib;
}