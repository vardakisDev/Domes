#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <random>
#include "linkedlist.h"
#include "Cordinates.h"
#include <vector>

#define R 2

class Functions
{
public:
    void SUMMARIZE_TRAJECTORY(vector<vector<LinkedList<Cordinates *> *>> &Users, int Day, int DaysBefore);
    void REPAIR(LinkedList<Cordinates *> *&UserTrajectory);
    void POSSIBLE_COVID_19_INFECTION(vector<LinkedList<Cordinates *> *> &Users, LinkedList<Cordinates *> *&UserTrajectory, vector<bool> &ListOfCovid19);
    int CROWDED_PLACES(vector<vector<LinkedList<Cordinates *> *>> &Users, Cordinates *point1, Cordinates *point2, int Day);

    int getDistance(Cordinates *temp1, Cordinates *temp2)
    {
        int distance = (int)(pow((temp2->getX() - temp1->getX()), 2) + 0.5) + (int)(pow((temp2->getY() - temp1->getY()), 2) + 0.5);
        return sqrt(distance);
    }
    int getTimeDiffernce(Cordinates *temp1, Cordinates *temp2)
    {
        return temp2->getZ() - temp1->getZ();
    }
    float getLost(Cordinates *temp1, Cordinates *temp2)
    {
        return (float)getDistance(temp1, temp2) / getTimeDiffernce(temp1, temp2);
    }

    bool deFineCircle(Cordinates *center, Cordinates *toFind)
    {
        int distance = (toFind->x - center->x) ^ 2 + (toFind->y - center->y) ^ 2;
        int radius = R * R;
        if (radius >= distance)
        {
            return true;
        }
        else
            return false;
    }
};

#endif