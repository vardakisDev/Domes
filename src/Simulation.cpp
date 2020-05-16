
#include "../headers/Functions.h"
#include "../headers/Simulation.h"
#include "../headers/Menu.h"

using namespace std;

//This method does crreate a vector of pointers of list that represent each day of the running simulation.
//For every loop a new list is created which takes Node of Cordinates and we push it at the back of our Vector of list pointers to keep track of them.
//The while loop runs until the end of each day and generates at the start a random Cordinate.
//note that we are moving on DxD area which is set on our simulation.h and it implements RandomWaypoint Model.
//          Y
//    D   |
//        | _ _ __ _ _ *(this is the random generated point from our GenerateDay method)
//        |           |
//    D   |_ _ _ _ _ _| _ _ _ _ __ _ _ _ _ _ _ _  X
//this random generated point is starting position of every user . After that to keep the user moving we call the RandomCordinates method which returns the
//given cordinates with an increment or disinrement of a given speed which is also random generated and we push the new generated Node of Cordinates on the back of the list.
//At the end of the for all users loop after we have generated all the Days there will be some blank node which simulate the gps lost singal. In order to fill the list we call the
//repair function which add all the missing nodes to the list And at the end of the day we return the vector of lists generated and we push at the Vector of main function.

vector<LinkedList<Cordinates *> *> Simulation::GenerateDay()
{
    Functions function;
    Simulation simulation;
    Cordinates *temp;

    Cordinates *movingCordinates;
    //before this there will be a menu a

    vector<LinkedList<Cordinates *> *> Day; //the generated Day that we will return at the main simulation method  and apush it on the vector of days for all the users

    for (int i = 0; i < simulation.max_users; i++)
    {
        Day.push_back(new LinkedList<Cordinates *>()); //for each user push back a new linklist of Cordinate nodes
        simulation.start = 30;
        while (simulation.start < simulation.day) //run till the end of the day
        //At the start of each day
        //first time we genarate our random points will be the starting position of our "person" so both (x,y) = random() .
        //This will be our starting point so we will initiate our Corindates object and Link List and save them there

        {
            if (simulation.start == 30) //Random STARTING POINT FOR EVERY USER
            {
                int randX = 1 + (rand() % 100);
                int randY = 1 + (rand() % 100);
                //the starting point for each person on each day and then we construct a new cordinate and add it to the back of the list
                Cordinates *startingCordinates = new Cordinates(randX, randY, simulation.start);
                temp = startingCordinates; //save the startingCordinates
                Day[i]->addAtBack(startingCordinates);
            }
            else
            {

                int randomchoice = rand() & 1;
                switch (randomchoice)
                //case 0 means that our user is moving
                //case 1 mean that our user lost GPS singal and our
                {
                case 0:
                    simulation.RandomCordinates(temp);                                     // we pass the starting cordinates  by reference to RandomCordinates and it generates its movement as explained
                    movingCordinates = new Cordinates(temp->x, temp->y, simulation.start); //construct the new Cordinates
                    Day[i]->addAtBack(movingCordinates);                                   //at them at the bback of the list
                    temp = movingCordinates;                                               //save the moving cordinates
                    break;
                case 1:
                    break; //no new node is added it to the list and with these way we simulate the lost singal
                }
            }
            simulation.start = simulation.start + simulation.step;
        }
    }
    for (auto &x : Day) //fill the missinng nodes by calling repair function
    {
        function.REPAIR(x);
    }
    return Day;
}

//This simulation takes the already random generated cordinates from the generated day for each user at a time , and increments it by a given speed in these case 3-6 and it simulates the mcving of each user
//at the caretsian graph . Each time before incrementing or disicrement wwe can check  , if the cordinates run out of DxD variable whiich is the space our users use , if it out of borders it simple
//change the sign of the randomspeed and it adds it to the cordinates
//The model in which we are moving is RandomWaypoint
//This means , we generate a random value of 1-5 .
//case 1,2 means that our users move onn the x - axis which means left or right
//case 3,4 means that our users move on the y - axis which means top or down
//case 5 means that our stays put on his location
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
//Generates a simple vector of bools , for all the max_users of our simulation. 0 is for uninfected and 1 is for the infected
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
//these method is called at the end of each day in order to minimize the memory used by our data stracture.
//If the day which is passed is divided by the daybefores we call the method of functions.SUMMARIZE_TRAJECTORY
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

//At the end of each day our user is promted with these 3 options , 1 call the function CROWEDED PLACES , continue to the next day or exit the simulation.
//in the same time we run the POSSIBLE_COVID19 function for the true feeling of a simulation
void Simulation::PromtUser(vector<vector<LinkedList<Cordinates *> *>> &Users, vector<bool> ListOfCovid19, int Day)
{
    Menu menu;
    Functions functions;
    menu.PromtForFunctions();
    int timeInterval = 900;

    //run the possible infection for all the users inside the simulation

    for (int i = 1; i < Users.size(); i++)
    {
        if (ListOfCovid19[i] == 0)
            functions.POSSIBLE_COVID_19_INFECTION(Users[Day], Users[Day][i], ListOfCovid19, i);
    }
    //save the listofcovid results into a vector
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
            cout << "This users where found inisde the square region :" << functions.CROWDED_PLACES(Users, new Cordinates(point1, point2, 0), new Cordinates(point3, point4, 0), Day, timeInterval) << endl;
            cout << "Would you like to use other pints ? \n Press 1 to input new numbers or 0 to continue the simulation" << endl;
            cin >> flag;
        }
        break;

    case 2:
        break;
    case 3:
        dontPromtUser = 1;
        break;
    case 4:
        exit(0);
    default:
        break;
    }
}

//This is the main function of the simulaton in which we call all the other.
//This methods has a vector of vector of pointers (Users) to list that represents all the days and all the days that we have already generated by our method GenerateDay.
//While our User0 is still uninfected we generate a day and we push it to the vector so we dont lose track of it.
//At the end of the genarated day we call the PossbleCovidFunction which returns true if the user was infected or else false and we print the result.
//After that we promt the user with a menu to continue using the simulation app as it was explained earlier
//The simulation ends when the user0 get infected which means that ListOfCovid 19[0] == 1 and we terminate the method here
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

    int Day = 0;
    while (ListOfCovid19[0] == 0)
    {
        Users.push_back(simulation.GenerateDay());
        cout << "\nDay:" << Day + 1 << endl;
        functions.POSSIBLE_COVID_19_INFECTION(Users[Day], Users[Day][0], ListOfCovid19, 0) ? cout << "Infected" : cout << "Not infected";

        simulation.SummarizeData(Users, Day);
        if (simulation.dontPromtUser == 0)
            simulation.PromtUser(Users, ListOfCovid19, Day);
        Day += 1;
    }
    cout << "User was infected on day: " << Day;
}
//g++ -I../headers Final.cpp Cordinates.cpp Functions.cpp Menu.cpp Simulation.cpp -o main
