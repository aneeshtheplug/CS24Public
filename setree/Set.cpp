#include "Set.h"
using namespace std;

Set::Set()
{
    Node *mRoot = NULL;
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

size_t Set::clear()
{
    postOrderDelete(mRoot);
}
size_t postOrderDelete(Node *head)
{
    size_t counter = 0;
    if (head != NULL)
    {
        postOrderDelete(head->left);
        postOrderDelete(head->right);
        delete head;
        counter = counter + 1;
    }
    return counter;
}

size_t Set::count() const
{
    preorder(mRoot);
}

size_t preorder(Node *head)
{
    size_t counter = 0;
    if (head != NULL)
    {
        counter = counter + 1;
        preorder(head->left);
        preorder(head->right);
    }
    return counter;
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