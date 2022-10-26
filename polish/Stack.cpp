#include "Stack.h"

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

void Stack::pop()
{
    if (top == nullptr)
    {
    }
    else
    {
        if (top->next == nullptr)
        {
            delete top;
            top = nullptr;
        }
        else
        {
            Node *temp = top->next;
            delete top;
            top = temp;
        }
    }
}

/*
Stack::Stack()
{
    arr = new char[1];
}
Stack::~Stack()
{
    delete[] arr;
}
void Stack::pop()
{
    if (count - 1 <= capacity / 2)
    {
        size_t arraySize = capacity / 2;
        char *newArr = new char[arraySize];
        top = top - 1;
        for (size_t i = 0; i <= top; ++i)
        {
            newArr[i] = arr[i];
        }
        capacity = arraySize;
        delete[] arr;
        arr = newArr;
    }
    else
    {
        top = top - 1;
    }
    count = count - 1;
}
void Stack::push(AST *node)
{
    if (count < capacity)
    {
        top = top + 1;
        arr[top] = char(node);
    }
    else
    {
        size_t arraySize = capacity * 2;
        char *newArr = new char[arraySize];
        top = top + 1;
        for (size_t i = 0; i < top; ++i)
        {
            newArr[i] = arr[i];
        }
        arr[top] = char(node);
        capacity = arraySize;
        delete[] arr;
        arr = newArr;
    }
    count = count + 1;
}

char Stack::peek()
{
    return arr[top];
}
*/