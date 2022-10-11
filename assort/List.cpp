#include <iostream>
#include "List.h"
using namespace std;

void printReverse(Node *head)
{
    if (head->next == NULL)
    {
        return;
    }
    printReverse(head->next);

    cout << head->data << ", ";
}
void List::insert(const std::string &value) // question about namespace std
{
    Node *newNode = new Node();
    newNode->data = value;
    if (head == NULL)
    {
        newNode->next = NULL;
        head = newNode;
    }
    Node *current = head;
    Node *prev = NULL;
    while (current->next != NULL && current->next->data < newNode->data)
    {
        current = current->next;
        prev = current;
    }
    prev->next = newNode;
    newNode->next = current->next;
}

void List::print(bool reverse = false) const
{
    cout << "[";
    if (reverse == false)
    {
        Node *current = head;
        while (current != NULL)
        {
            if (current->next != NULL)
            {
                cout << current->data << ", ";
                current = current->next;
            }
            else
            {
                cout << current->data;
                current = current->next;
            }
        }
    }
    else
    {
        Node *current = head;
        printReverse(current);
        Node *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        cout << current->data;
    }
    cout << "]";
    cout << endl;
}

size_t List::count() const
{
    Node *current = head;
    size_t counter = 0;
    while (current != NULL)
    {
        counter = counter + 1;
        current = current->next;
    }
    return counter;
}

string List::lookup(size_t index) const
{
    if (index >= count())
    {
        throw out_of_range("Invalid index");
    }
    else
    {
        size_t target = 0;
        Node *current = head;
        while (target < index)
        {
            current = current->next;
            target = target + 1;
        }
        return current->data;
    }
}