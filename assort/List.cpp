#include <iostream>
#include "List.h"
using namespace std;

List::List()
{
    head = NULL;
}

List::List(const List &other)
{
    if (other.head == NULL)
    {
        head = NULL;
    }
    else
    {
        Node *old = other.head;
        Node *startNode = new Node();
        startNode->data = old->data;
        head = startNode;

        Node *current = head;
        while (old->next != NULL)
        {
            Node *added = new Node();
            added->data = old->next->data;
            current->next = added;
            current = added;
            old = old->next;
        }
        current->next = NULL;
    }
}

List::List(List &&other)
{
    head = other.head;
    other.head = NULL;
}

List::~List()
{
    Node *current = head;
    while (current != NULL)
    {
        Node *temp = current->next;
        delete current;
        current = temp;
    }
    head = NULL;
}

void printReverse(Node *head)
{
    if (head == NULL)
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
    else if (head->data > newNode->data)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        Node *current = head;
        while (current->next != NULL && current->next->data < newNode->data)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void List::print(bool reverse) const
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
        if (head == NULL)
        {
        }
        else
        {
            printReverse(head->next);
            cout << head->data;
        }
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

const string &List::lookup(size_t index) const
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

string List::remove(size_t index)
{
    if (index >= count())
    {
        throw out_of_range("Invalid index");
    }
    else
    {
        Node *current = head;
        if (index == 0)
        {
            head = current->next;
            string val = current->data;
            delete current;
            return val;
        }
        else
        {
            Node *prev;
            size_t target = 0;
            while (target < index)
            {
                prev = current;
                current = current->next;
                target = target + 1;
            }
            if (current->next != NULL)
            {
                prev->next = current->next;
            }
            else
            {
                prev->next = NULL;
            }
            string val = current->data;
            delete current;
            return val;
        }
    }
}

size_t List::remove(const string &value)
{
    size_t counter = 0;
    size_t index = 0;
    Node *current = head;
    if (head == NULL)
    {
        return counter;
    }
    Node *prev;
    while (current->next != NULL)
    {
        if (current->data == value)
        {
            if (index == 0)
            {
                head = current->next;
                delete current;
                current = head;
                counter = counter + 1;
            }
            else
            {
                prev->next = current->next;
                delete current;
                current = current->next;
                counter = counter + 1;
            }
        }
        else
        {
            index = index + 1;
            prev = current;
            current = current->next;
        }
    }
    if (current->data == value)
    {
        prev->next = NULL;
        delete current;
        counter = counter + 1;
    }
    return counter;
}