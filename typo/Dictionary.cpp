#include "Dictionary.h"
using namespace std;

Dictionary::Dictionary(std::istream &stream)
{
    std::string line;
    while (std::getline(stream, line))
    {
        if (line[0] == '#' || line.empty())
        {
            continue;
        }
        else
        {
            mWords.push_back(line);
        }
    }
}

Heap Dictionary::correct(const std::vector<Point> &points, size_t maxcount, float cutoff) const
{
    cutoff++;
    maxcount++;
    Heap deez(7);
    return deez;
    points.capacity();
}