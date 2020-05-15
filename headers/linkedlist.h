#ifndef LINKLIST_H
#define LINKLIST_H
#include "node.h"
#include <iostream>

template <class T>
class LinkedList
{
public:
    LinkedList();
    ~LinkedList();
    int FindNode(T node);
    void InsertAtIndex(int k, T node);
    void InsertAfterNode(T nodeBefore, T toAdd);
    void addAtFront(T node);
    void addAtBack(T Node);
    void addAfterNode(T oldNode, T nodeToInsert);
    void removeNode(T node);
    void printlist();
    void pointerprint();
    void printbyIndex(int index);
    int getSize() { return size; };
    void Sizeup()
    {
        size++;
    };
    void Sizeminus() { size--; };
    bool isEmpty() { return head->next == NULL; };
    Node<T> *getHead() { return head; };
    Node<T> *head;

private:
    int size;
};

template <class T>
LinkedList<T>::LinkedList() : head(0)
{
    size = 0;
}

template <class T>
//decosntruct the link by iterating and deleting   each node
LinkedList<T>::~LinkedList()
{
    Node<T> *temp = head;

    while (head)
    {
        temp = head->next;
        delete head;
        head = temp;
    }
}

template <class T>
int LinkedList<T>::FindNode(T node)
{
    int index = 1;
    Node<T> *temp = head;
    while (temp->data != node)
    {
        temp = temp->next;
        index++;
    }
    if (temp)
        return index;
    return 0;
}

template <class T>
void LinkedList<T>::InsertAfterNode(T nodeBefore, T toAdd)
{
    InsertAtIndex(FindNode(nodeBefore), toAdd);
    return;
}

template <class T>
void LinkedList<T>::InsertAtIndex(int k, T node)
{
    if (k < 0)
    {
        std::cout << "OUTOFBOUNDS" << std::endl;
        return;
    }
    Node<T> *temp = head;
    for (int i = 1; i < k; i++)
        temp = temp->next;
    if (k > 0 && !temp)
        std::cout << "OUTOFBOUNDS" << std::endl;
    Node<T> *toAdd = new Node<T>();
    toAdd->data = node;
    if (k)
    {
        toAdd->next = temp->next;
        temp->next = toAdd;
        Sizeup();
    }
    else
    {
        toAdd->next = head;
        head = toAdd;
        Sizeup();
    }
}

//Add a node at the start of the list
template <class T>
void LinkedList<T>::addAtFront(T node)
{
    if (node)
    {
        Node<T> *newNode = new Node<T>();
        newNode->data = node;

        if (head == NULL)
        {
            head = newNode;
            newNode->next = nullptr;
            newNode->prev = nullptr;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    else
    {
        std::cout << "Node is Null" << std::endl;
        return;
    }
    Sizeup();
    return;
}
//Add a node at the currently last position of a list
template <class T>
void LinkedList<T>::addAtBack(T node)
{
    if (node != NULL)
    {
        Node<T> *newNode = new Node<T>();
        newNode->data = node;
        if (head == nullptr)
        {
            head = newNode;
            return;
        }
        else
        {
            Node<T> *tmpNode = head;
            while (tmpNode->next != nullptr)
            {
                tmpNode = tmpNode->next;
            }
            tmpNode->next = newNode;
            newNode->prev = tmpNode;
        }
        Sizeup();
    }
    else
    {
        std::cout << "Node is Null" << std::endl;
    }
}

//removes a given node from the list
template <class T>
void LinkedList<T>::removeNode(T node)
{
    Node<T> *p = head;
    int indexToDelete = FindNode(node);
    if (indexToDelete <= 0)
    {
        std::cout << "OUTOFBONS";
        return;
    }
    if (indexToDelete == 1)
        head = p->next;
    else
    {
        Node<T> *y = head;
        for (int index = 1; index < indexToDelete - 1; index++)
            y = y->next;
        if (!y || !y->next)
        {
            std::cout << "Throoutofbounds" << std::endl;
            return;
        }
        p = y->next;
        y->next = p->next;
    }
    delete p;
    return;
}

//prints a list of pointers to object
template <class T>
void LinkedList<T>::pointerprint()
{
    Node<T> *temp = head; //We point at the start of the list
    if (temp == NULL)
    {
        std::cout << "List is empty" << std::endl; // if head is null list is empty
        return;
    }
    else
    {
        {
            while (temp)
            {
                std::cout << *(temp->data); // printing temp->data prints the adress so we i just print where it points , take that cpp
                temp = temp->next;          //we iterate through the whole list
            }
        }
    }
    std::cout << "Print List " << std::endl;
}

#endif