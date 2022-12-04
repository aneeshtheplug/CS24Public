#include "Atlas.h"
#include <sstream>
#include <stdexcept>
#include <iostream>
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
          newEdge->neighbor = previous;
          newEdge2->neighbor = newStation;
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
          newEdge->neighbor = previous;
          newEdge2->neighbor = obj;
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
  std::cout << "map created" << endl;
  Pair source;
  source.distance = 0;
  source.id = stuff.at(src);
  source.previous = nullptr;
  heap.push(source);
  while (heap.size() > 0)
  {
    Station *top = heap.top().id;
    heap.pop();
    if (used.find(top) != used.end())
    {
      continue;
    }
    for (Edge *edges : top->vec)
    {
      if (edges->neighbor->name == dst)
      {
        Station *newStation = new Station;
        newStation->name = edges->neighbor->name;
        Edge *newEdge = new Edge;
        newEdge->neighbor = top;
        used.insert({newStation, newEdge});
        breaker = 1;
        break;
      }
      if (used.find(edges->neighbor) == used.end())
      {
        used.insert({top, edges});
      }
      if (edges->dist + map.at(top) < map.at(edges->neighbor))
      {
        map.at(edges->neighbor) = edges->dist + map.at(top);
        Pair newPair;
        newPair.distance = edges->dist + map.at(top);
        newPair.previous = top;
        newPair.id = edges->neighbor;
        heap.push(newPair);
      }
    }
    if (breaker == 1)
    {
      break;
    }
  }
  std::cout << used.size() << endl;
  std::cout << map.size() << endl;
  for (auto [k, v] : used)
  {
    std::cout << k->name << ": " << v->neighbor->name << endl;
  }
  Trip trip;
  trip.start = src;
  auto itr = used.at(stuff.at(dst));

  while (itr->neighbor->name != src)
  {
    Trip::Leg leg;
    leg.line = itr->line;
    leg.stop = itr->neighbor->name;
    trip.legs.push_back(leg);
    itr = used.at(stuff.at(itr->neighbor->name));
  }
  if (trip.legs.size() == 0)
  {
    throw std::runtime_error("No route");
  }
  reverse(trip.legs.begin(), trip.legs.end());
  return trip;
}
// std::string test = src;
// std::string test2 = dst;
// Trip *newTrip = new Trip;
// return *newTrip;
// station new station, edge new edge,