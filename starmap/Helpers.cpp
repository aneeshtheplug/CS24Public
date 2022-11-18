#include "Helpers.h"
#include <iostream>
using namespace std;

// Space to implement helper class member functions.

void destruct(KD_tree::Node *treeRoot)
{
    if (treeRoot == NULL)
    {
        return;
    }
    else
    {
        destruct(treeRoot->left);
        destruct(treeRoot->right);
        delete treeRoot;
    }
}
KD_tree::~KD_tree()
{
    destruct(root);
}
KD_tree::Node *KD_tree::insertHelp(Node *tRoot, Star newStar, unsigned depth)
{
    // Tree is empty?
    if (tRoot == nullptr)
    {
        return newNode(newStar);
    }
    // Calculate current dimension (cd) of comparison
    unsigned cd = depth % k;
    float starVal;
    float starVal2;
    if (cd == 0)
    {
        starVal = newStar.x;
        starVal2 = tRoot->star.x;
    }
    else if (cd == 1)
    {
        starVal = newStar.y;
        starVal2 = tRoot->star.y;
    }
    else
    {
        starVal = newStar.z;
        starVal2 = tRoot->star.z;
    }

    // Compare the new point with root on current dimension 'cd'
    // and decide the left or right subtree
    if (starVal < starVal2)
        tRoot->left = insertHelp(tRoot->left, newStar, depth + 1);
    else
        tRoot->right = insertHelp(tRoot->right, newStar, depth + 1);
    return tRoot;
}

KD_tree::Node *KD_tree::insert(Star star)
{
    return insertHelp(root, star, 0);
}

void KD_tree::helpPrint(Node *head)
{
    if (head == NULL)
    {
        cout << "-";
    }
    else if (head->right == NULL && head->left == NULL)
    {
        cout << head->star.id;
    }
    else if (head->right || head->left)
    {
        cout << "(";
        helpPrint(head->left);
        cout << " ";
        cout << head->star.id;
        cout << " ";
        helpPrint(head->right);
        cout << ")";
    }
}

void KD_tree::print()
{
    helpPrint(root);
}