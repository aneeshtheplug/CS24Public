#include "StarMap.h"
#include <sstream>
#include <string>
#include <cmath>
#include "Helpers.h"
#include <iostream>
#include <algorithm>

using namespace std;

StarMap *StarMap::create(std::istream &stream)
{
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new StarMap(stream);
}

StarMap::StarMap(std::istream &stream)
{
  double starId = 0;
  std::string line;
  while (std::getline(stream, line))
  {
    string coord;
    istringstream myExp(line);
    getline(myExp, coord, '\t');
    xCord = stof(coord);
    getline(myExp, coord, '\t');
    yCord = stof(coord);
    getline(myExp, coord, '\t');
    zCord = stof(coord);
    starId++;
    Star newStar;
    newStar.x = xCord;
    newStar.y = yCord;
    newStar.z = zCord;
    newStar.id = starId;
    tree.root = tree.insert(newStar);
  }
}

StarMap::~StarMap()
{
}
std::vector<Star> StarMap::find(size_t n, float x, float y, float z)
{
  std::vector<Star> starVec;
  findHelp(x, y, z, tree.root, 0, n);
  while (!heap.empty())
  {
    starVec.push_back(heap.top().star);
    heap.pop();
  }
  reverse(starVec.begin(), starVec.end());
  return starVec;
}

void StarMap::findHelp(float x1, float y1, float z1, KD_tree::Node *kdRoot, int depth, size_t size)
{
  if (kdRoot == nullptr)
  {
    return;
  }
  kdRoot->dist = sqrt(pow(kdRoot->star.x - x1, 2) + pow(kdRoot->star.y - y1, 2) + pow(kdRoot->star.z - z1, 2));
  if (heap.size() < size)
  {
    Entry n;
    n.star = kdRoot->star;
    n.score = kdRoot->dist;
    heap.push(n);
  }
  else if (heap.top().score > kdRoot->dist)
  {
    Entry n;
    n.star = kdRoot->star;
    n.score = kdRoot->dist;
    heap.push(n);
    heap.pop();
  }
  int cd = depth % 3;
  float comp;
  float target;
  if (cd == 0)
  {
    comp = kdRoot->star.x;
    target = x1;
  }
  else if (cd == 1)
  {
    comp = kdRoot->star.y;
    target = y1;
  }
  else
  {
    comp = kdRoot->star.z;
    target = z1;
  }
  if (target < comp)
  {
    findHelp(x1, y1, z1, kdRoot->left, depth + 1, size);
  }
  else
  {
    findHelp(x1, y1, z1, kdRoot->right, depth + 1, size);
  }
  if (cd == 0)
  {
    if (abs(kdRoot->star.x - x1) < heap.top().score)
    {
      if (x1 < kdRoot->star.x)
      {
        findHelp(x1, y1, z1, kdRoot->right, depth + 1, size);
      }
      else
      {
        findHelp(x1, y1, z1, kdRoot->left, depth + 1, size);
      }
    }
  }
  else if (cd == 1)
  {
    if (abs(kdRoot->star.y - y1) < heap.top().score)
    {
      if (y1 < kdRoot->star.y)
      {
        findHelp(x1, y1, z1, kdRoot->right, depth + 1, size);
      }
      else
      {
        findHelp(x1, y1, z1, kdRoot->left, depth + 1, size);
      }
    }
  }
  else
  {
    if (abs(kdRoot->star.z - z1) < heap.top().score)
    {
      if (z1 < kdRoot->star.z)
      {
        findHelp(x1, y1, z1, kdRoot->right, depth + 1, size);
      }
      else
      {
        findHelp(x1, y1, z1, kdRoot->left, depth + 1, size);
      }
    }
  }
}