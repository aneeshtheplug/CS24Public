#include "Person.h"
#include <string>
// Person Member Functions

using namespace std;
Person::Person(string identity, string sex, Person *mother, Person *father)
{
    strName = identity;
    if (sex == "male")
    {
        gen = Gender::MALE;
    }
    else
    {
        gen = Gender::FEMALE;
    }
    mom = mother;
    dad = father;
}

Person::~Person()
{
}

const string &Person::name() const
{
    return strName;
}

Gender Person::gender() const
{
    return gen;
}

Person *Person::mother()
{
    return mom;
}

Person *Person::father()
{
    return dad;
}

set<Person *> Person::children()
{
    return child;
}

set<Person *> Person::daughters()
{
    set<Person *> daughter;
    for (Person *ch : child)
    {
        if (ch->gender() == Gender::FEMALE)
        {
            daughter.insert(ch);
        }
    }
    return daughter;
}

set<Person *> Person::sons()
{
    set<Person *> son;
    for (Person *ch : child)
    {
        if (ch->gender() == Gender::MALE)
        {
            son.insert(ch);
        }
    }
    return son;
}

set<Person *> Person::grandchildren()
{
    set<Person *> grand;
    for (Person *ch : child)
    {
        for (Person *grandkid : ch->child)
        {
            grand.insert(grandkid);
        }
    }
    return grand;
}

set<Person *> Person::granddaughters()
{
    set<Person *> grandDaughter;
    for (Person *grand : grandchildren())
    {
        if (grand->gender() == Gender::FEMALE)
        {
            grandDaughter.insert(grand);
        }
    }
    return grandDaughter;
}

set<Person *> Person::grandsons()
{
    set<Person *> grandSon;
    for (Person *grand : grandchildren())
    {
        if (grand->gender() == Gender::MALE)
        {
            grandSon.insert(grand);
        }
    }
    return grandSon;
}

std::set<Person *> Person::parents(PMod pmod)
{
    set<Person *> parent;
    if (pmod == PMod::MATERNAL)
    {
        if (mom != nullptr)
        {
            parent.insert(mom);
        }
    }
    else if (pmod == PMod::PATERNAL)
    {
        if (dad != nullptr)
        {
            parent.insert(dad);
        }
    }
    else
    {
        if (mom != nullptr)
        {
            parent.insert(mom);
        }
        if (dad != nullptr)
        {
            parent.insert(dad);
        }
    }
    return parent;
}

std::set<Person *> Person::grandparents(PMod pmod)
{
    set<Person *> grandparent;
    if (pmod == PMod::MATERNAL)
    {
        for (Person *ch : parents(PMod::MATERNAL))
        {
            for (Person *old : ch->parents(PMod::ANY))
            {
                if (old != nullptr)
                {
                    grandparent.insert(old);
                }
            }
        }
    }
    else if (pmod == PMod::PATERNAL)
    {
        for (Person *ch : parents(PMod::PATERNAL))
        {
            for (Person *old : ch->parents(PMod::ANY))
            {
                if (old != nullptr)
                {
                    grandparent.insert(old);
                }
            }
        }
    }
    else
    {
        for (Person *ch : parents(PMod::ANY))
        {
            for (Person *old : ch->parents(PMod::ANY))
            {
                if (old != nullptr)
                {
                    grandparent.insert(old);
                }
            }
        }
    }
    return grandparent;
}

std::set<Person *> Person::grandfathers(PMod pmod)
{
    set<Person *> grandfather;
    return grandfather;
}

std::set<Person *> Person::ancestors(PMod pmod)
{
    return std::set<Person *>();
}

std::set<Person *> Person::aunts(PMod pmod, SMod smod)
{
    return std::set<Person *>();
}

std::set<Person *> Person::brothers(PMod pmod, SMod smod)
{
    return std::set<Person *>();
}

std::set<Person *> Person::cousins(PMod pmod, SMod smod)
{
    return std::set<Person *>();
}

std::set<Person *> Person::descendants()
{
    return std::set<Person *>();
}

std::set<Person *> Person::grandmothers(PMod pmod)
{
    return std::set<Person *>();
}

std::set<Person *> Person::nephews(PMod pmod, SMod smod)
{
    return std::set<Person *>();
}

std::set<Person *> Person::nieces(PMod pmod, SMod smod)
{
    return std::set<Person *>();
}

std::set<Person *> Person::siblings(PMod pmod, SMod smod)
{
    return std::set<Person *>();
}

std::set<Person *> Person::sisters(PMod pmod, SMod smod)
{
    return std::set<Person *>();
}

std::set<Person *> Person::uncles(PMod pmod, SMod smod)
{
    return std::set<Person *>();
}
