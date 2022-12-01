#include "Atlas.h"
#include <sstream>

Atlas *Atlas::create(std::istream &stream)
{
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new Atlas(stream);
}

Atlas::~Atlas()
{
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
  std::string test = src;
  std::string test2 = dst;
  Trip *newTrip = new Trip;
  return *newTrip;
}

// station new station, edge new edge,