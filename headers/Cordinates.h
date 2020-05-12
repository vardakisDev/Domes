#ifndef CORDINATES_H
#define CORDINATES_H
#include <iostream>
#include <string>
#include <math.h>

//A simple class about our cordinates . Both X, Y are ints and the represent the X,Y cordinates on the cartesian graph and z its the time of each cordinate of each user
class Cordinates
{
public:
    int x;
    int y;
    int z;
    int infected;

public:
    Cordinates(int x, int y, int z);
    friend std::ostream &operator<<(std::ostream &stream, const Cordinates &cordinates)
    {
        stream << "z: " << cordinates.z;
        stream << "x: " << cordinates.x;
        stream << "y:" << cordinates.y << std::endl;
        return stream;
    }
    int getX()
    {
        return x;
    };
    int getY()
    {
        return y;
    }
    int getZ()
    {
        return z;
    }
    //returns the distance of two given points , using the mathematical equation of maths
    int getDistance(int x1, int y1, int x2, int y2)
    {
        int distance = (int)(pow((x2 - x1), 2) + 0.5) + (int)(pow((y2 - y1), 2) + 0.5);
        return sqrt(distance);
    }
};

#endif