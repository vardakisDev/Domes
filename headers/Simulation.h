#ifndef SIMULATION_H
#define SIMULATION_H

#include "Cordinates.h"
#include <vector>
#include <random>
#include <time.h>
#include <ctime>
class Simulation
{
public:
    int start = 30;
    int day = 86000;
    int step = 30;
    int max_users = 50;
    int DxD = 150;
    int timeDiference = 7200;
    int time = 0;
    int timeInside = 1800;

    void RandomCordinates(Cordinates *temp);
    vector<bool> GetListOfCovid19();
    vector<LinkedList<Cordinates *> *> GenerateDay();
    void Simulate();
    void SummarizeData(vector<vector<LinkedList<Cordinates *> *>> &Users, int Day);
    void PromtUser(vector<vector<LinkedList<Cordinates *> *>> &Users, vector<bool> ListOfCovid19, int Day);
};

#endif