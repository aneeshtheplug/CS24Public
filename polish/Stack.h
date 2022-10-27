#ifndef STACK_H
#define STACK_H
#include "AST.h"

// Use this file to define your Stack type.
// Implement its member functions in Stack.cpp.

struct Node
{
    AST *data;
    Node *next;
};
class Stack
{
    Node *top;

public:
    Stack();
    ~Stack();
    void push(AST *pointer);
    AST *pop();
    Node *topNode();
};
#endif
