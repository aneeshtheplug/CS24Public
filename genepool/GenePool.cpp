#include "GenePool.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
// GenePool Member Functions

GenePool::~GenePool()
{
}
GenePool::GenePool(std::istream &stream)
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
            string token;
            istringstream myExp(line);
            getline(myExp, token, '\t');
            name = token;
            getline(myExp, token, '\t');
            gender = token;
            getline(myExp, token, '\t');
            mother = find(token);
            getline(myExp, token, '\t');
            father = find(token);
        }
        Person *addNew = new Person(name, gender, mother, father);
        gene.insert({name, addNew});
        if (mother != nullptr)
        {
            mother->child.insert(addNew);
        }
        if (father != nullptr)
        {
            father->child.insert(addNew);
        }
    }
}
Person *GenePool::find(const std::string &name) const
{
    if (gene.count(name) == 0)
    {
        return nullptr;
    }
    else
    {
        return gene.at(name);
    }
}
