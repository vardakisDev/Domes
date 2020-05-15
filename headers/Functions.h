#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <random>
#include "../headers/Linkedlist.h"
#include "../headers/Cordinates.h"

#include <vector>

#define R 2

class Functions
{
public:
    void SUMMARIZE_TRAJECTORY(std::vector<std::vector<LinkedList<Cordinates *> *>> &Users, int Day, int DaysBefore);
    void REPAIR(LinkedList<Cordinates *> *&UserTrajectory);
    bool POSSIBLE_COVID_19_INFECTION(std::vector<LinkedList<Cordinates *> *> &Users, LinkedList<Cordinates *> *&UserTrajectory, std::vector<bool> &ListOfCovid19, int possible);
    int CROWDED_PLACES(std::vector<std::vector<LinkedList<Cordinates *> *>> &Users, Cordinates *point1, Cordinates *point2, int Day, int timeInterval);

    //returns the distance of two cordinates cartesian points
    int getDistance(Cordinates *temp1, Cordinates *temp2)
    {
        int distance = (int)(pow((temp2->getX() - temp1->getX()), 2) + 0.5) + (int)(pow((temp2->getY() - temp1->getY()), 2) + 0.5);
        return sqrt(distance);
    }
    //returns the time differnce of two points
    int getTimeDiffernce(Cordinates *temp1, Cordinates *temp2)
    {
        return temp2->getZ() - temp1->getZ();
    }
    //returns the accelaration between two given cordinates
    //          Dx\Dt = accelaration
    float getAcceleration(Cordinates *temp1, Cordinates *temp2)
    {
        return (float)getDistance(temp1, temp2) / getTimeDiffernce(temp1, temp2);
    }
    //returns true whether a point is inside or on the circle or false if it is outside
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