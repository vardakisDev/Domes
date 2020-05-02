#ifndef SIMULATION_H
#define SIMULATION_H

#include "Cordinates.h"
#include <vector>
#include <random>
#include <time.h>

class Simulation
{
public:
    int start = 30;
    int day = 3000;
    int step = 30;
    void RandomCordinates(Cordinates *temp);
    int fixborders(Cordinates *current, int randnumb);
    vector<bool> GetListOfCovid19();
    vector<LinkedList<Cordinates *> *> GenerateDay();
};

#endif