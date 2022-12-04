#include "Atlas.h"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;
Atlas *Atlas::create(std::istream &stream)
{
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new Atlas(stream);
}
Atlas::~Atlas()
{
  for (auto itr = stuff.begin(); itr != stuff.end(); itr++)
  {
    for (size_t i = 0; i < itr->second->vec.size(); i++)
    {
      delete itr->second->vec.at(i);
    }
    delete itr->second;
  }
}
Atlas::Atlas(std::istream &stream)
{
  Station *previous;
  int prevNum = 0;
  std::string currLine;
  std::string line, id, name, numS;
  bool isTrain = true;
  int num;
  while (std::getline(stream, line))
  {
    if (line[0] == '#' || line.empty())
    {
      continue;
    }
    std::istringstream sstream(line);
    sstream >> id;
    if (id == "BUS:" || id == "TRAIN:")
    {
      sstream >> ws;
      std::getline(sstream, currLine);
      if (id == "BUS:")
      {
        isTrain = false;
      }
      else
      {
        isTrain = true;
      }
      previous = nullptr;
    }
    else if (id == "-")
    {
      sstream >> numS;
      num = stoi(numS);
      sstream >> std::ws;
      std::getline(sstream, name);
      auto it = stuff.find(name);
      if (it == stuff.end())
      {
        if (previous != nullptr)
        {
          Station *newStation = new Station;
          newStation->name = name;
          stuff.insert({name, newStation});
          Edge *newEdge = new Edge;
          Edge *newEdge2 = new Edge;
          if (isTrain)
          {
            newEdge->dist = std::abs(prevNum - num);
            newEdge2->dist = std::abs(prevNum - num);
          }
          else
          {
            newEdge->dist = 0;
            newEdge2->dist = 0;
          }
          newEdge->line = currLine;
          newEdge2->line = currLine;
          newEdge->train = isTrain;
          newEdge2->train = isTrain;
          newEdge->src = previous;
          newEdge->dst = newStation;
          newEdge2->src = newStation;
          newEdge2->dst = previous;
          newStation->vec.push_back(newEdge);
          previous->vec.push_back(newEdge2);
          prevNum = num;
          previous = newStation;
        }
        else
        {
          Station *newStation = new Station;
          newStation->name = name;
          stuff.insert({name, newStation});
          prevNum = num;
          previous = newStation;
        }
      }
      else
      {
        Station *obj = stuff.at(name);
        if (previous != nullptr)
        {
          Edge *newEdge = new Edge;
          Edge *newEdge2 = new Edge;
          if (isTrain)
          {
            newEdge->dist = std::abs(prevNum - num);
            newEdge2->dist = std::abs(prevNum - num);
          }
          else
          {
            newEdge->dist = 0;
            newEdge2->dist = 0;
          }
          newEdge->line = currLine;
          newEdge2->line = currLine;
          newEdge->train = isTrain;
          newEdge2->train = isTrain;
          newEdge->src = previous;
          newEdge->dst = obj;
          newEdge2->src = obj;
          newEdge2->dst = previous;
          obj->vec.push_back(newEdge);
          previous->vec.push_back(newEdge2);
          prevNum = num;
          previous = obj;
        }
        else
        {
          previous = obj;
          prevNum = num;
        }
      }
    }
  }
}
Trip Atlas::route(const std::string &src, const std::string &dst)
{
  std::map<Station *, int> map;
  std::map<Station *, Edge *> used;
  std::priority_queue<Pair> heap;
  int breaker = 0;
  // for (auto const &stations : stuff)
  // {
  //   map.insert({stations.second, numeric_limits<int>::max()});
  // }
  // for (auto const &stations : map)
  // {
  //   cout << stations.first->name << " ";
  //   for (auto const &neighbors : stations.first->vec)
  //   {
  //     cout << neighbors->neighbor->name << " ";
  //   }
  //   cout << endl;
  // }
  for (auto it = stuff.begin(); it != stuff.end(); it++)
  {
    if (it->first == src)
    {
      map.insert({stuff.at(it->first), 0});
    }
    else
    {
      map.insert({stuff.at(it->first), INT_MAX});
    }
  }
  Pair source;
  source.distance = 0;
  source.ed = nullptr;
  heap.push(source);
  while (heap.size() > 0)
  {
    Station *top;
    Edge *edge;
    if (heap.top().ed == nullptr)
    {
      top = stuff.at(src);
      edge = nullptr;
    }
    else
    {
      top = heap.top().ed->src; // src
      edge = heap.top().ed;
    }
    heap.pop();
    if (used.find(top) != used.end()) // top is always the same in this case so top can always be found
    {
      continue;
    }
    else
    {
      used.insert({top, edge});
    }
    for (Edge *edges : top->vec)
    {
      if (edges->src->name == dst) // src
      {
        used.insert({edges->src, edges}); // src
        breaker = 1;
        break;
      }
      if (edges->dist + map.at(top) < map.at(edges->src))
      {
        map.at(edges->src) = edges->dist + map.at(top);
        Pair newPair;
        newPair.distance = edges->dist + map.at(top);
        newPair.ed = edges;
        heap.push(newPair);
      }
    }
    if (breaker == 1)
    {
      break;
    }
  }

  Trip trip;
  trip.start = src;
  Station *curr = stuff.at(dst);

  while (curr->name != src)
  {
    Trip::Leg leg;
    Edge *edge = nullptr;
    if (used.at(curr) != nullptr)
    {
      edge = used.at(curr);
    }
    Station *prev = edge->dst; // dst
    leg.line = edge->line;
    leg.stop = used.at(curr)->src->name;
    if (trip.legs.size() == 0)
    {
      trip.legs.push_back(leg);
    }
    else if (trip.legs.back().line != leg.line)
    {
      trip.legs.push_back(leg);
    }
    curr = prev;
  }
  if (trip.legs.size() == 0)
  {
    throw std::runtime_error("No route");
  }
  reverse(trip.legs.begin(), trip.legs.end());
  return trip;
}
