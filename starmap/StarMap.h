#ifndef STARMAP_H
#define STARMAP_H

#include "Star.h"

#include <istream>
#include <vector>

class StarMap
{
public:
    // Required Class Function
    static StarMap *create(std::istream &stream);

private:
    float xCord;
    float yCord;
    float zCord;
    std::vector<Star> starVec;

public:
    // Constructor & Destructor
    StarMap(std::istream &stream);
    ~StarMap();

    // Required Member Function
    std::vector<Star> find(size_t n, float x, float y, float z);

    // Other Member Functions
    void pushSpace(std::vector<Star> &close, Star add, float dist, float x, float y, float z);
    void pushFull(std::vector<Star> &close, Star add, float dist, float x, float y, float z);
    float distanceHelp(Star str, float x1, float y1, float z2);
};

#endif
