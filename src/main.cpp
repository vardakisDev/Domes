#include <iostream>
#include "linkedlist.h"
#include "song.h"

#include <string>
using namespace std;

int main()
{
    Song *song = new Song("Queen", "1");
    Song *song2 = new Song("Queen", "2");
    Song *song3 = new Song("Queen", "3");
    LinkedList<Song *> newlist;
    newlist.addAtFront(song);
    newlist.addAtBack(song2);
    newlist.InsertAfterNode(song, song3);
    newlist.removeNode(song2);
    newlist.removeNode(song);
    newlist.removeNode(song3);
    newlist.pointerprint();

    // Cordinates *x1 = new Cordinates(1, 2, 3);
    // Cordinates *x2 = new Cordinates(1, 2, 2);
    // Cordinates *x3 = new Cordinates(1, 2, 2);

    // LinkedList<Cordinates *> new2;
    // new2.addAtFront(x1);
    // new2.addAtFront(x2);
    // new2.addAtFront(x3);
    // new2.pointerprint();
    // cout << new2.getSize();

    // LinkedList<int> new3;
    // new3.addAtFront(333232);
    // new3.printlist();

    // vector<LinkedList<Cordinates *> *> array;
    // array.push_back(&new2);
    // array[0]->printlist();
    // array.push_back(&new2);
    // array[1]->addAtBack(x2);
    // ifstream cordinates("test1.csv");
    // string time_of_record;
    // string x_cord;
    // string y_cord;
    // if (cordinates.is_open()) //if the file is open
    // {
    //     //ignore first line
    //     cout << "File opened";
    //     string line, empty;
    //     getline(cordinates, line);
    //     LinkedList<Cordinates *> createdlist;
    //     while (cordinates) //while the end of file is NOT reached
    //     {
    //         getline(cordinates, empty, ',');
    //         getline(cordinates, time_of_record, ',');
    //         getline(cordinates, x_cord, ',');
    //         getline(cordinates, y_cord, '\n');
    //         Cordinates *created = new Cordinates(stod(time_of_record), stod(x_cord), stod(y_cord));
    //         createdlist.addAtBack(created);
    //         cout << *created;
    //     }
    //     array.push_back(&createdlist);
    //     cordinates.close(); //closing the file
    // }
    // else
    //     cout << "Unable to open file"; //if the file is not open output
    // array[3]->printlist();
    return 0;
}