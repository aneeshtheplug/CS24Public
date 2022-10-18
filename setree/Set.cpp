#include "Set.h"
using namespace std;
#include <iostream>

Set::Set()
{
    mRoot = NULL;
}

Set::Set(Set &&other)
{
    mRoot = other.mRoot;
    other.mRoot = NULL;
}
Set::~Set()
{
}
size_t Set::insert(const string &value)
{
    if (mRoot == NULL)
    {
        Node *newNode = new Node();
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
        mRoot = newNode;
        return 1;
    }
    else
    {
        Node *newNode = new Node();
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
        Node *current = mRoot;
        Node *prev = NULL;
        while (current != NULL)
        {
            prev = current;
            if (value < current->data)
            {
                current = current->left;
            }
            else if (value > current->data)
            {
                current = current->right;
            }
            else
            {
                return 0;
            }
        }
        if (value < prev->data)
        {
            prev->left = newNode;
        }
        else
        {
            prev->right = newNode;
        }
        return 1;
    }
}

size_t postOrderDelete(Node *head)
{
    if (head == NULL)
    {
        return 0;
    }
    else
    {
        delete head;
        return 1 + postOrderDelete(head->left) + postOrderDelete(head->right);
    }
}

size_t Set::clear()
{
    return postOrderDelete(mRoot);
}

size_t preorder(Node *head)
{
    if (head == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + preorder(head->left) + preorder(head->right);
    }
}

size_t Set::count() const
{
    return preorder(mRoot);
}

bool Set::contains(const string &value) const
{
    Node *current = mRoot;
    if (current == NULL)
    {
        return false;
    }
    while (current != NULL)
    {
        if (value < current->data)
        {
            current = current->left;
        }
        else if (value > current->data)
        {
            current = current->right;
        }
        else
        {
            return true;
        }
    }
    return false;
}

Node *findSucc(Node *current)
{
    while (current && current->left != NULL)
    {
        current = current->left;
    }
    return current;
}
size_t Set::remove(const string &value)
{
    Node *current = mRoot;
    while (current != NULL)
    {
        if (value < current->data)
        {
            current = current->left;
        }
        else if (value > current->data)
        {
            current = current->right;
        }
        else
        {
            if (current->right == NULL && current->left == NULL)
            {
                delete current;
            }
            else if (current->right == NULL)
            {
                Node *temp = current->left;
                delete current;
                current = temp;
            }
            else if (current->left == NULL)
            {
                Node *temp = current->right;
                delete current;
                current = temp;
            }
            else
            {
                Node *temp = findSucc(current->right);
                string tempData = temp->data;
                remove(temp->data);
                current->data = tempData;
                return 1;
            }
        }
    }
    return 0;
}
