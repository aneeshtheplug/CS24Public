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

void postOrderDelete(Node *head)
{
    if (head == NULL)
    {
        return;
    }
    else
    {
        postOrderDelete(head->left);
        postOrderDelete(head->right);
        delete head;
    }
}

size_t Set::clear()
{
    size_t total = count();
    postOrderDelete(mRoot);
    mRoot = NULL;
    return total;
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

void helpPrint(Node *head)
{
    if (head == NULL)
    {
        cout << "-";
    }
    else if (head->right == NULL && head->left == NULL)
    {
        cout << head->data;
    }
    else if (head->right || head->left)
    {
        cout << "(";
        helpPrint(head->left);
        cout << " ";
        cout << head->data;
        cout << " ";
        helpPrint(head->right);
        cout << ")";
    }
}
void Set::print() const
{
    helpPrint(mRoot);
    cout << endl;
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

Node *removeHelp(Node *current, const string &value)
{
    if (current == NULL)
    {
        return 0;
    }
    else if (value < current->data)
    {
        current->left = removeHelp(current->left, value);
    }
    else if (value > current->data)
    {
        current->right = removeHelp(current->right, value);
    }

    else
    {
        if (current->right == NULL && current->left == NULL)
        {
            delete current;
            current = NULL;
        }
        else if (current->right == NULL)
        {
            Node *temp = current;
            current = current->left;
            delete temp;
        }
        else if (current->left == NULL)
        {
            Node *temp = current;
            current = current->right;
            delete temp;
        }
        else
        {
            Node *temp = findSucc(current->right);
            current->data = temp->data;
            current->right = removeHelp(current->right, temp->data);
        }
    }
    return current;
}

size_t Set::remove(const string &value)
{
    if (contains(value) == false)
    {
        return 0;
    }
    size_t prevCount = count();
    removeHelp(mRoot, value);
    size_t afterCount = count();
    if (prevCount == afterCount)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

const string &Set::lookup(size_t n) const
{
    return 5;
}