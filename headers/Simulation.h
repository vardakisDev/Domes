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
    int start = 30;                                        //starting day of each day
    int day = 86000;                                       //duration of each day , 86000 sec = 24 hrour
    int step = 30;                                         //increment our counter (start) which
    int max_users = 50;                                    //total of users
    int DxD = 150;                                         //max area of the cartesian
    int timeDiference = 7200;                              //timeDiference for FIND_POSSIBLE_INFECTION
    int timeInside = 900;                                  //Time that the user has to be found inside the R of an infected user
    bool dontPromtUser = 0;                                //dont promt user to continue or search for crowed places
    void RandomCordinates(Cordinates *temp);               //Generates a randomspeed from 3-6 and increments the random given cordinates of rand() from the simulation
    std::vector<bool> GetListOfCovid19();                  //Generates a list of Covid19 , an array of bool that 0 = uninfected and 1 = infected , our Users which is user0 is always 0
    std::vector<LinkedList<Cordinates *> *> GenerateDay(); //Generates a day for all the max_users
    void Simulate();
    // Each simulation starts from here
    void SummarizeData(std::vector<std::vector<LinkedList<Cordinates *> *>> &Users, int Day);                              //calss SUMMARIZE_TRAJECTORY
    void PromtUser(std::vector<std::vector<LinkedList<Cordinates *> *>> &Users, std::vector<bool> ListOfCovid19, int Day); //Promts the user for the possible actions he can take
};

#endif