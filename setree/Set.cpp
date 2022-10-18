#include "Set.h"
using namespace std;

Set::Set()
{
    mRoot = NULL;
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
/*
size_t Set::remove(const string &value)
{
    Node *current = mRoot;
    Node *prev = NULL;
    if (current == NULL)
    {
    }
    while (current != NULL)
    {
        if (value < current->data)
        {
            current = current->left;
            prev = current;
        }
        else if (value > current->data)
        {
            current = current->right;
            prev = current;
        }
        else
        {
            if (current->right == NULL && current->left == NULL)
            {
                delete current;
            }
        }
    }
}
*/