#ifndef CORDINATES_H
#define CORDINATES_H
#include <iostream>
#include <string>
#include <math.h>
using namespace std;
class Cordinates
{
public:
    int x;
    int y;
    int z;
    int infected;

public:
    Cordinates(int x, int y, int z);
    friend ostream &operator<<(ostream &stream, const Cordinates &cordinates)
    {
        stream << "z: " << cordinates.z;
        stream << "x: " << cordinates.x;
        stream << "y:" << cordinates.y << endl;
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
    int getDistance(int x1, int y1, int x2, int y2)
    {
        int distance = (int)(pow((x2 - x1), 2) + 0.5) + (int)(pow((y2 - y1), 2) + 0.5);
        return sqrt(distance);
    }
};

#endif