#ifndef NODES_H
#define NODES_H

#include "AST.h"

// Declare your AST subclasses here.
// Implement their member functions in Nodes.cpp.
class Number : public AST
{
    double value;
    virtual std::string prefix()
    {
    }
    virtual std::string postfix()
    {
    }
    virtual double value()
    {
    }
};

class Add : public AST
{
    char *add;
    std::unique_ptr left;
    std::unique_ptr right;
    virtual std::string prefix()
    {
        return value(left) + value(right);
    }
    virtual std::string postfix()
    {
        return left + right;
    }
    virtual double value()
    {
        add = "+";
    }
};

class Subtract : public AST
{
public:
    std::string prefix();
    std::string postfix();
    double value();
};

class Mutliply : public AST
{
public:
    std::string prefix();
    std::string postfix();
    double value();
};

class Divide : public AST
{
public:
    std::string prefix();
    std::string postfix();
    double value();
};

class Modulo : public AST
{
public:
    std::string prefix();
    std::string postfix();
    double value();
};

class Negtation : public AST
{
public:
    std::string prefix();
    std::string postfix();
    double value();
};

#endif
