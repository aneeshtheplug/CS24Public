#ifndef HELPERS_H
#define HELPERS_H
#include "Star.h"
// If you want to add any helper classes,
// here's some space to do it in.
const int k = 3;
class KD_tree
{
public:
    // basic node implementation
    struct Node
    {
        Star star;
        float dist;
        Node *left;
        Node *right;
    };
    struct Node *newNode(Star newStar)
    {
        struct Node *temp = new Node;
        temp->star = newStar;
        temp->left = temp->right = nullptr;
        return temp;
    }
    Node *insertHelp(Node *tRoot, Star star, unsigned depth);
    Node *insert(Star star);
    void helpPrint(Node *head);
    void print();
    ~KD_tree();

public:
    Node *root = nullptr;
};
#endif