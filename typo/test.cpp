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
    Heap heap2 = heap;
    heap2.push("James", 7.5);
    std::cout << heap2.count() << std::endl;
    std::cout << heap2.lookup(0).value << std::endl;
    std::cout << heap2.lookup(1).value << std::endl;
    std::cout << heap2.lookup(2).value << std::endl;
    std::cout << heap2.lookup(3).value << std::endl;
    std::cout << heap2.lookup(4).value << std::endl;
    return 0;
}
