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
    int day = 86000;
    int step = 30;
    int max_users = 20;
    void RandomCordinates(Cordinates *temp);
    int fixborders(Cordinates *current, int randnumb);
    vector<bool> GetListOfCovid19();
    vector<LinkedList<Cordinates *> *> GenerateDay();
    void Simulate();
    void SummarizeData(vector<vector<LinkedList<Cordinates *> *>> &Users, int Day);
    void PromtUser(vector<vector<LinkedList<Cordinates *> *>> &Users, int Day);
};

#endif