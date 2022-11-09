#include "Heap.h"
#include <iostream>

// Use this file to test your Heap class!
// This file won't be graded - do whatever you want.

int main()
{
    Heap heap(7);

    std::cout << "This program doesn't do anything interesting yet...\n";
    heap.push("David", 9.5);
    heap.push("Alex", 8.5);
    heap.push("Jose", 6.9);
    heap.push("Henry", 3.7);
    std::cout << heap.pop().value << std::endl;

    return 0;
}
