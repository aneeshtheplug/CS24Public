#include "Heap.h"
#include <iostream>

Heap::Heap(size_t capacity)
{
    mCapacity = capacity;
    mData = new Entry[capacity];
    mCount = 0;
}

Heap::Heap(const Heap &other)
{
    mCapacity = other.capacity();
    mData = new Entry[mCapacity];
    mCount = 0;
    for (size_t i = 0; i < other.count(); i++)
    {
        mData[i] = other.mData[i];
        mCount++;
    }
}

Heap::Heap(Heap &&other)
{
    mData = other.mData;
    delete[] other.mData;
}

Heap::~Heap()
{
    delete[] mData;
}
size_t Heap::capacity() const
{
    return mCapacity;
}

size_t Heap::count() const
{
    return mCount;
}

size_t parent(size_t i)
{
    return (i - 1) / 2;
}

size_t leftChild(size_t i)
{
    return (2 * i) + 1;
}

size_t rightChild(size_t i)
{
    return (2 * i) + 2;
}

Heap::Entry Heap::pop()
{
    if (mCount == 0)
    {
        throw std::underflow_error("No items in heap");
    }
    else
    {
        Entry smallest = mData[0];
        mData[0] = mData[mCount - 1];
        mCount--;
        size_t it = 0;
        while (true)
        {
            size_t left = leftChild(it);
            size_t right = rightChild(it);
            size_t min = it;
            if (left < mCount && mData[left].score < mData[it].score)
            {
                min = left;
            }
            if (right < mCount && mData[right].score < mData[min].score)
            {
                min = right;
            }
            if (min != it)
            {
                Entry temp = mData[it];
                mData[it] = mData[min];
                mData[min] = temp;
                it = min;
            }
            else
            {
                break;
            }
        }
        Entry *newArray = new Entry[mCount];
        for (size_t i = 0; i < mCount; i++)
        {
            newArray[i] = mData[i];
        }
        delete[] mData;
        mData = newArray;
        return smallest;
    }
}

const Heap::Entry &Heap::lookup(size_t index) const
{
    if (index >= mCount)
    {
        throw std::out_of_range("Invalid index");
    }
    else
    {
        return mData[index];
    }
}
void Heap::push(const std::string &value, float score)
{
    if (mCount >= mCapacity)
    {
        throw std::overflow_error("No space for new item");
    }
    Entry *newEntry = new Entry();
    newEntry->value = value;
    newEntry->score = score;
    mCount++;
    size_t i = mCount - 1;
    mData[i] = *newEntry;
    while (i != 0 && mData[parent(i)].score > mData[i].score)
    {
        Entry temp = mData[parent(i)];
        mData[parent(i)] = mData[i];
        mData[i] = temp;
        i = parent(i);
    }
}

const Heap::Entry &Heap::top() const
{
    if (mCount == 0)
    {
        throw std::underflow_error("No items in heap");
    }
    else
    {
        return mData[0];
    }
}

Heap::Entry Heap::pushpop(const std::string &value, float score)
{
    if (mCount == 0)
    {
        throw std::underflow_error("No items in heap");
    }
    else
    {
        Entry *newEntry = new Entry();
        newEntry->value = value;
        newEntry->score = score;
        Entry smallest = mData[0];
        mData[0] = *newEntry;
        size_t it = 0;
        while (true)
        {
            size_t left = leftChild(it);
            size_t right = rightChild(it);
            size_t min = it;
            if (left < mCount && mData[left].score < mData[it].score)
            {
                min = left;
            }
            if (right < mCount && mData[right].score < mData[min].score)
            {
                min = right;
            }
            if (min != it)
            {
                Entry temp = mData[it];
                mData[it] = mData[min];
                mData[min] = temp;
                it = min;
            }
            else
            {
                break;
            }
        }
        return smallest;
    }
}
