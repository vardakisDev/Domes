#ifndef LINKLIST_H
#define LINKLIST_H
#include "node.h"
#include <iostream>
using namespace std;

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

    // template <class TT> //friend enables us to access the private and protective members of the class LinkedList
    // friend std::ostream &operator<<(ostream &out, const LinkedList<TT> &obj) //the mean goal of this code is to be able cout<<LinkedList
    // {
    //     Node<TT> *temp = obj.head;
    //     while (temp != NULL)
    //     {
    //         out << *(temp->getData()) << endl;
    //         temp = temp->getNext();
    //     }
    //     cout << endl;
    //     return out;
    // }
    //give the size of the list without having to iterate the whole list in 0(N) time
    int getSize() { return size; };
    void Sizeup()
    {
        size++;
    };
    void Sizeminus() { size--; };
    void setInfected(int i) { infected = i; }
    int getInfected() { return infected; }
    bool isEmpty() { return head->next == NULL; };
    Node<T> *getHead() { return head; };
    Node<T> *head;

private:
    int size;
    int infected;
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
        cout << "OUTOFBOUNDS" << endl;
        return;
    }
    Node<T> *temp = head;
    for (int i = 1; i < k; i++)
        temp = temp->next;
    if (k > 0 && !temp)
        cout << "OUTOFBOUNDS" << endl;
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
        cout << "Node is Null" << endl;
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
        cout << "Node is Null" << endl;
    }
}
//Needs  fixing
template <class T>
void LinkedList<T>::addAfterNode(T oldNode, T nodeToInsert)
{
    Node<T> *newNode = new Node<T>();
    newNode->data = nodeToInsert;
    Node<T> *oNode = new Node<T>();
    oNode->data = oldNode;
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node<T> *tempNode = head, *temp2;
        while (tempNode->data == oNode->data)
        {
            if (tempNode->next == nullptr)
            {
                cout << "Node not found in data" << endl;
                break;
            }
            else
            {
                tempNode = tempNode->next;
            }
        }
        temp2 = tempNode->next;
        tempNode->next = newNode;
        newNode->prev = tempNode;
        newNode->next = temp2;
        temp2->prev = newNode;
    }
}
//needs fixing
template <class T>
void LinkedList<T>::removeNode(T node)
{
    Node<T> *p = head;
    int indexToDelete = FindNode(node);
    if (indexToDelete <= 0)
    {
        cout << "OUTOFBONS";
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
            cout << "Throoutofbounds" << endl;
            return;
        }
        p = y->next;
        y->next = p->next;
    }
    delete p;
    return;
}

//Gave up on this method ... because it takes a complexity o(n) , i just simply return the sizefrom the object
// //Itarates every node an increment a counter its time data!null by 1 but this takes 0(N) TIME so i implemented a more effiecent way
// template <class T>
// int LinkedList<T>::size()
// {
//     if (head == NULL)
//         return 0;
//     Node<T> *temp = head;
//     int counter = 0;

//     while (temp != NULL)
//     {
//         counter += 1;
//         temp = temp->next;
//     }

//     return counter;
// }
//

//For printing the list i hace to methods ... one prints node data with pointers and the other if the object is just int string etc.
//Maybe i fix it later

//The code works simply , we point a pointer at the start of the list and we print in each loop the node.data and then the pointer points at the node->next and the loop continues
template <class T>
void LinkedList<T>::printlist()
{
    Node<T> *temp = head; //We point at the start of the list
    if (temp == NULL)
    {
        cout << "List is empty" << endl; // if head is null list is empty
        return;
    }
    else
    {
        {
            while (temp)
            {
                cout << temp->data;
                temp = temp->next;
            }
        }
    }
    cout << "Print List " << endl;
}
template <class T>
void LinkedList<T>::pointerprint()
{
    Node<T> *temp = head; //We point at the start of the list
    if (temp == NULL)
    {
        cout << "List is empty" << endl; // if head is null list is empty
        return;
    }
    else
    {
        {
            while (temp)
            {
                cout << *(temp->data); // printing temp->data prints the adress so we i just print where it points , take that cpp
                temp = temp->next;     //we iterate through the whole list
            }
        }
    }
    cout << "Print List " << endl;
}

template <class T>
void LinkedList<T>::printbyIndex(int index)
{
    Node<T> *temp;
}

#endif