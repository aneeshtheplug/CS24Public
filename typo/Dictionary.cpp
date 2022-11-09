#include "Dictionary.h"
#include <cmath>
using namespace std;

bool isLower(string word)
{
    for (size_t i = 0; i < word.length(); i++)
    {
        if (islower(word[i]) == true)
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

Dictionary::Dictionary(std::istream &stream)
{
    std::string line;
    while (std::getline(stream, line))
    {
        if (isLower(line))
        {
            mWords.push_back(line);
        }
    }
}

float distanceCalc(string str, const std::vector<Point> &ptr)
{
    float match = 0;
    size_t i = 0;
    for (auto itr = ptr.begin(); itr != ptr.end(); itr++)
    {
        int index = (str[i] - 97);
        float distance = sqrt(pow((QWERTY[index].x - itr->x), 2) + pow((QWERTY[index].y - itr->y), 2));
        float score = 1.0 / (10.0 * pow(distance, 2) + 1.0);
        match = match + score;
        i++;
    }
    float avg = match / float(str.length());
    return avg;
}

Heap Dictionary::correct(const std::vector<Point> &points, size_t maxcount, float cutoff) const
{
    Heap heap(maxcount);
    size_t len = points.size();
    std::vector<std::string> compare;
    auto itr = mWords.begin();
    while (itr != mWords.end())
    {
        if ((*itr).length() == len)
        {
            compare.push_back(*itr);
        }
        ++itr;
    }
    for (auto it = compare.begin(); it != compare.end(); it++)
    {
        float newScore = distanceCalc(*it, points);
        if (newScore >= cutoff)
        {
            if (heap.count() < heap.capacity())
            {
                heap.push(*it, newScore);
            }
            else if (heap.top().score < newScore)
            {
                heap.pushpop(*it, newScore);
            }
        }
    }
    return heap;
}
