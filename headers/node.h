
// We will be making a template for a (double) Linked List for c++ using templates and classes
//after this proccess the list should be able to work for every data type and even objects we create.

#ifndef NODE_H
#define NODE_H

#include <iostream>

template <class T> // template <class Type> is pre proccesing our code and the type of data will be decided when compiling the program
class LinkedList;  //so these gives a lot of freedom which c couldnt give . so cheers on cpp

// the difference between class and or  struct Node {               is that by default the members of struct is public
//                                                  T data;          so what you use its up you ,  i prefer classes.
//                                                  Node * next;
//                                                  Node * prev;
//                                                                 }

template <class T>
class Node
{
    friend class LinkedList<T>;

public:
    Node();  //our constructor
    Node(T); //
    T getData();
    Node<T> *getNext() { return next; }
    Node<T> *getPrev() { return prev; }
    friend std::ostream &operator<<(std::ostream &out, const Node<T> &node)
    {
        out << node.data;
        return out;
    }

// private:
    T data;
    Node<T> *next;
    Node<T> *prev;
};
template <class T>
Node<T>::Node()
{
    next = 0;
    prev = 0;
}
template <class T>
Node<T>::Node(T node)
{
    data = node;
    next = 0;
    prev = 0;
}
template <class T>
T Node<T>::getData()
{
    return data;
}
#endif //