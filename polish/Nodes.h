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
    ~Add();
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
    ~Subtract();
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
    ~Mutliply();
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
    ~Divide();
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
    ~Modulo();
    AST *left;
    AST *right;
    std::string prefix() const;
    std::string postfix() const;
    double value() const;
};

class Negation : public AST
{
public:
    Negation(AST *small);
    ~Negation();
    AST *child;
    std::string prefix() const;
    std::string postfix() const;
    double value() const;
};

#endif
