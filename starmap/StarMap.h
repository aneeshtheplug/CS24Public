#ifndef STARMAP_H
#define STARMAP_H

#include "Star.h"
#include "Helpers.h"
#include <istream>
#include <vector>
#include <queue>

class StarMap
{
public:
    // Required Class Function
    static StarMap *create(std::istream &stream);

private:
    float xCord;
    float yCord;
    float zCord;
    KD_tree tree;
    struct Entry
    {
        float score;
        Star star;

        bool operator<(const Entry &other) const
        {
            return this->score < other.score;
        }
    };
    std::priority_queue<Entry> heap;

public:
    // Constructor & Destructor
    StarMap(std::istream &stream);
    ~StarMap();
    // Required Member Function
    std::vector<Star> find(size_t n, float x, float y, float z);
    void findHelp(float x1, float y1, float z1, KD_tree::Node *kdRoot, int depth, size_t size);

    // Other Member Functions
};

#endif
