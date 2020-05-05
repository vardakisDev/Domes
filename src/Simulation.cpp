
#include "Function.h"
#include "Simulation.h"
#include "Menu.h"

void Simulation::RandomCordinates(Cordinates *temp)
{

    int randomspeed = ((rand() % 2) + 4);
    int result = 1 + (rand() % 5);

    switch (result)
    {
    case 1:
        randomspeed = fixborders(temp, randomspeed);
        temp->x += randomspeed;
        break;
    case 2:
        randomspeed = fixborders(temp, randomspeed);
        temp->x -= randomspeed;
        break;
    case 3:
        randomspeed = fixborders(temp, randomspeed);
        temp->y += randomspeed;
        break;
    case 4:
        randomspeed = fixborders(temp, randomspeed);
        temp->y -= randomspeed;
        break;
    //case 5 and 6 are cases where our stupid dot doesnt move to favour him staying more time in the same area with someone infected , sry dot !
    case 5:
        break;
    }
}

int Simulation::fixborders(Cordinates *current, int randnumb)
{
    if (current->x + randnumb > 100 | current->y + randnumb > 100 | current->y - randnumb < 0 | current->x - randnumb < 0)
    {
        // cout << "Out of border chanign" << randnumb << "to" << -randnumb << endl;
        randnumb = -randnumb;
        return randnumb;
    }
    return randnumb;
}

vector<bool> Simulation::GetListOfCovid19()
{
    vector<bool> ListOfCovid19;
    ListOfCovid19.push_back(0); // we want User0 to always be uninfected because he isthe one simulating our user
    for (int i = 1; i < max_users; i++)
    {
        int randomchoice = (rand() % 2); //might add probablity
        switch (randomchoice)
        {
        case 0:

            ListOfCovid19.push_back(0);
            break;
        case 1:
            ListOfCovid19.push_back(1);
            break;
        }
    }
    return ListOfCovid19;
}
vector<LinkedList<Cordinates *> *> Simulation::GenerateDay()
{
    Functions function;
    Simulation simulation;
    Cordinates *temp;

    Cordinates *movingCordinates;
    //before this there will be a menu a

    vector<LinkedList<Cordinates *> *> Day;

    for (int i = 0; i < simulation.max_users; i++)
    {
        Day.push_back(new LinkedList<Cordinates *>());
        simulation.start = 30;
        while (simulation.start < simulation.day)
        //At the start of each day
        //first time we genarate our random points will be the starting position of our "person" so both (x,y) = random() .
        //This will be our starting point so we will initiate our Corindates object and Link List and save them there

        {
            if (simulation.start == 30) //Random STARTING POINT FOR EVERY USER
            {
                int randnumb = 1 + (rand() % 100);
                //the starting point for each person on each day
                Cordinates *startingCordinates = new Cordinates(randnumb, randnumb, simulation.start);
                temp = startingCordinates;
                Day[i]->addAtBack(startingCordinates);
            }
            else
            {

                int randomchoice = rand() & 1;
                switch (randomchoice)
                {
                case 0:
                    simulation.RandomCordinates(temp);
                    movingCordinates = new Cordinates(temp->x, temp->y, simulation.start);
                    Day[i]->addAtBack(movingCordinates);
                    temp = movingCordinates;
                    break;
                case 1:
                    break;
                }
            }
            simulation.start = simulation.start + simulation.step;
        }
    }
    for (auto &x : Day)
    {
        function.REPAIR(x);
    }
    return Day;
}
void Simulation::SummarizeData(vector<vector<LinkedList<Cordinates *> *>> &Users, int Day)
{
    Functions functions;
    int daysbefore = 4;
    if (Day % 4 == 0 && Day >= 4)
    {
        functions.SUMMARIZE_TRAJECTORY(Users, Day, daysbefore);
    }
    return;
}
void Simulation::PromtUser(vector<vector<LinkedList<Cordinates *> *>> &Users, int Day)
{
    Menu menu;
    Functions functions;
    menu.PromtForFunctions();
    int value;
    cin >> value;
    switch (value)
    {
    case 1:
        cout << functions.CROWDED_PLACES(Users, new Cordinates(25, 10, 0), new Cordinates(12, 10, 0), Day) << endl;
        break;
    case 2:
        break;
    case 3:
        exit(0);
    default:
        break;
    }
}
void Simulation::Simulate()
{

    Simulation simulation;
    Functions functions;
    Menu menu;

    menu.InformUser();
    menu.PrintMenu();
    srand(time(0));

    vector<vector<LinkedList<Cordinates *> *>> Users;
    vector<bool> ListOfCovid19 = simulation.GetListOfCovid19();

    int day = 0;
    while (ListOfCovid19[0] == 0)
    {
        Users.push_back(simulation.GenerateDay());
        cout << "\nDay:" << day + 1 << endl;
        functions.POSSIBLE_COVID_19_INFECTION(Users[day], Users[day][0], ListOfCovid19);
        simulation.SummarizeData(Users, day);
        simulation.PromtUser(Users, day);
        day += 1;
    }
    menu.PromtForSimulation();
}
