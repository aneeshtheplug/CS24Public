#include "Stack.h"
#include <stdexcept>

// Implement your Stack member functions here.

Stack::Stack()
{
    top = nullptr;
}

Stack::~Stack()
{
    Node *current = top;
    while (current != nullptr)
    {
        Node *temp = current->next;
        delete current->data;
        delete current;
        current = temp;
    }
    top = nullptr;
}

void Stack::push(AST *pointer)
{
    Node *newNode = new Node();
    newNode->data = pointer;
    if (top == nullptr)
    {
        newNode->next = nullptr;
        top = newNode;
    }
    else
    {
        newNode->next = top;
        top = newNode;
    }
}

AST *Stack::pop()
{
    if (top == nullptr)
    {
        throw std::runtime_error("Not enough operands.");
    }
    else
    {
        Node *temp = top->next;
        AST *prevTop = top->data;
        delete top;
        top = temp;
        return prevTop;
    }
}

Node *Stack::topNode()
{
    return top;
}

double Stack::count()
{
    double counter = 0;
    if (top == nullptr)
    {
        return counter;
    }
    else
    {
        Node *current = top;
        while (current != nullptr)
        {
            counter++;
            current = current->next;
        }
        return counter;
    }
}