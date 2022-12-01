#ifndef HELPERS_H
#define HELPERS_H
#include <string>
#include <vector>

// If you want to add any helper classes,
// here's some space to do it in.

struct Station;
struct Edge
{
    int dist;
    std::string line;
    Station *neighbor;
    bool train;
};

struct Station
{
    std::string name;
    std::vector<Edge *> vec;
};

#endif
