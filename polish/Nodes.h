#ifndef NODES_H
#define NODES_H

#include "AST.h"
#include <cmath>

// Declare your AST subclasses here.
// Implement their member functions in Nodes.cpp.
class Number : public AST
{
    double num;

public:
    Number(double value);
    std::string prefix() const;
    std::string postfix() const;
    double value() const;
};

class Add : public AST
{
public:
    Add(AST *lhs, AST *rhs);
    AST *left;
    AST *right;
    std::string prefix() const;
    std::string postfix() const;
    double value() const;
};

class Subtract : public AST
{
public:
    Subtract(AST *lhs, AST *rhs);
    AST *left;
    AST *right;
    std::string prefix() const;
    std::string postfix() const;
    double value() const;
};

class Mutliply : public AST
{
public:
    Mutliply(AST *lhs, AST *rhs);
    AST *left;
    AST *right;
    std::string prefix() const;
    std::string postfix() const;
    double value() const;
};

class Divide : public AST
{
public:
    Divide(AST *lhs, AST *rhs);
    AST *left;
    AST *right;
    std::string prefix() const;
    std::string postfix() const;
    double value() const;
};

class Modulo : public AST
{
public:
    Modulo(AST *lhs, AST *rhs);
    AST *left;
    AST *right;
    std::string prefix() const;
    std::string postfix() const;
    double value() const;
};

class Negtation : public AST
{
public:
    AST *left;
    AST *right;
    std::string prefix() const;
    std::string postfix() const;
    double value() const;
};

#endif
