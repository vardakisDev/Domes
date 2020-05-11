
#include "Function.h"
#include "Simulation.h"
#include "Menu.h"

void Simulation::RandomCordinates(Cordinates *temp)
{
    Simulation simulation;
    int randomspeed = rand() % (7 - 3) + 3;
    int result = 1 + (rand() % 5);

    switch (result)
    {
    case 1:
        randomspeed = (temp->x + randomspeed > simulation.DxD) ? -randomspeed : randomspeed;
        temp->x = temp->x + randomspeed;
        break;
    case 2:
        randomspeed = (temp->x - randomspeed < 0) ? -randomspeed : randomspeed;
        temp->x = temp->x - randomspeed;
        break;
    case 3:
        randomspeed = (temp->y + randomspeed > simulation.DxD) ? -randomspeed : randomspeed;
        temp->y = temp->y + randomspeed;
        break;
    case 4:
        randomspeed = (temp->y - randomspeed < 0) ? -randomspeed : randomspeed;
        temp->y = temp->y - randomspeed;
        break;
        //case 5 is  cases where our stupid dot doesnt move to favour him staying more time in the same area with someone infected , sry dot !
    case 5:
        break;
    }
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
                int randnumb = 1 + (rand() % 75);
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
void Simulation::PromtUser(vector<vector<LinkedList<Cordinates *> *>> &Users, vector<bool> ListOfCovid19, int Day)
{
    Menu menu;
    Functions functions;
    menu.PromtForFunctions();
    for (int i = 1; i < Users.size(); i++)
    {
        if (ListOfCovid19[i] == 0)
            functions.POSSIBLE_COVID_19_INFECTION(Users[Day], Users[Day][i], ListOfCovid19, i);
    }
    int value;
    cin >> value;
    switch (value)
    {
    case 1:
        int flag;
        while (flag)
        {
            cout << "Please enter the following cordinates of the square regions you want to search for possible hotspots";
            int point1, point2, point3, point4;
            cout << "\n Enter Point 1 ";
            cin >> point1;
            cout << "\n Enter Point 2 ";
            cin >> point2;
            cout << "\n Enter Point 3 ";
            cin >> point3;
            cout << "\n Enter Point 4 ";
            cin >> point4;
            cout << "This users where found inisde the square region :" << functions.CROWDED_PLACES(Users, new Cordinates(point1, point2, 0), new Cordinates(point3, point4, 0), Day) << endl;
            cout << "Would you like to use other pints ? \n Press 1 to input new numbers or 0 to continue the simulation" << endl;
            cin >> flag;
        }
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
    srand((int)time_t(0));

    vector<vector<LinkedList<Cordinates *> *>> Users;
    vector<bool> ListOfCovid19 = simulation.GetListOfCovid19();

    int day = 0;
    bool flag;
    while (ListOfCovid19[0] == 0)
    {
        Users.push_back(simulation.GenerateDay());
        cout << "\nDay:" << day + 1 << endl;
        functions.POSSIBLE_COVID_19_INFECTION(Users[day], Users[day][0], ListOfCovid19, 0) ? cout << "Infected" : cout << "Not infected";

        simulation.SummarizeData(Users, day);
        simulation.PromtUser(Users, ListOfCovid19, day);
        day += 1;
    }
    cout << "User was infected on day: " << day;
}
//g++ -I../headers Final.cpp Cordinates.cpp Functions.cpp Menu.cpp Simulation.cpp -o main
