#include "Atlas.h"
#include <sstream>
#include <iostream>
#include <climits>
#include <stdexcept>
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
  std::map<Station *, int> map; // distance from src to every station in the map
  std::map<Station *, Pair> used;
  std::priority_queue<Pair> heap;
  int breaker = 0;
  // for (auto const &stations : stuff)
  // {
  //   map.insert({stations.second, numeric_limits<int>::max()});
  // }
  // for (auto const &stations : map)
  // {
  //   std::cout << stations.first->name << " ";
  //   for (auto const &neighbors : stations.first->vec)
  //   {
  //     std::cout << neighbors->neighbor->name << " ";
  //   }
  //   std::cout << endl;
  // }
  for (auto const &stations : stuff)
  {
    map.insert({stations.second, std::numeric_limits<int>::max()});
  }
  map.at(stuff.at(src)) = 0;

  Pair start;
  start.id = stuff.at(src);
  start.distance = map.at(stuff.at(src));
  start.previous = nullptr;
  heap.push(start);
  // //print out map
  //  for(auto const& stations : map){
  //   cout << stations.first->name << " " << stations.second << endl;
  //  }

  // while the top of our heap is not our destination & our heap size is not 0
  while (heap.top().id != stuff.at(dst) && heap.size() != 0)
  {
    // Iteratore through all of the neighbors at the top of our heap
    for (size_t i = 0; i < heap.top().id->vec.size(); i++)
    {
      if (heap.top().id->vec.at(i)->neighbor->name == dst)
      { // if dst is one of the neighbors of heap.top()
        Pair destination;
        destination.id = stuff.at(dst);
        destination.distance = map.at(heap.top().id) + heap.top().id->vec.at(i)->dist;
        destination.line = heap.top().id->vec.at(i)->line;
        destination.previous = heap.top().id;
        if (destination.distance < map.at(destination.id))
        {
          map.at(destination.id) = destination.distance;
        }
        used.insert({destination.id, destination});
        breaker = 1;
        break;
      }
      else
      {
        if (used.count(heap.top().id->vec.at(i)->neighbor) == 0)
        { // if the current neighbor i am analyzing is not in my visited...
          cout << "this" << endl;
          Pair newPair;
          newPair.id = heap.top().id->vec.at(i)->neighbor;
          newPair.distance = map.at(heap.top().id) + heap.top().id->vec.at(i)->dist;
          newPair.line = heap.top().id->vec.at(i)->line;
          newPair.previous = heap.top().id;
          if (newPair.distance < map.at(newPair.id))
          { // if the distance of the new pair is less than the distance associated to it in the map...add it to the heap
            map.at(newPair.id) = newPair.distance;
            heap.push(newPair);
            cout << heap.size() << endl;
          }
          else
          {
            cout << "that" << endl;
            continue;
          }
        }
        else
        { // The current neighbor I am analyzing is in my visited
          continue;
        }
      }
      // if the top of my heap is in my visited
      if (used.count(heap.top().id) != 0)
      {
        cout << "none" << endl;
        heap.pop();
        continue;
      }
      else
      { // if the top of my heap is not in my visited.
        used.insert({heap.top().id, heap.top()});
        heap.pop();
      }
    }
    if (breaker == 1)
    {
      cout << "breaker" << endl;
      break;
    }
  }

  // FIX MAP?? MAYBE HOLD PAIR INSTEAD?????? Or not because it is sitting in heap.top()

  //  cout << heap.top().previous->name << endl;
  //  //used print
  //  for(auto const& stations : used){
  //   cout << stations.first->name << " Previous:: ";
  //   if(stations.second.previous != nullptr){
  //     cout << stations.second.previous->name << endl;
  //   }
  //  }
  cout << used.size() << endl;
  used.insert({heap.top().id, heap.top()});

  Trip trip;
  trip.start = src;
  Station *curr = stuff.at(dst);

  while (curr->name != trip.start)
  {
    Trip::Leg leg;
    Pair edge = used.at(curr);
    Station *prev = edge.previous;
    leg.line = edge.line;
    leg.stop = prev->name;
    trip.legs.push_back(leg);
    curr = prev;
  }
  if (trip.legs.size() == 0)
  {
    throw std::runtime_error("No route");
  }
  reverse(trip.legs.begin(), trip.legs.end());

  return trip;
}
