#include "Function.h"
#include "Simulation.h"
int main()
{
    Simulation simulation;
    Functions functions;
    vector<LinkedList<Cordinates *> *> Day;
    srand(time(0));

    vector<bool> ListOfCovid19 = simulation.GetListOfCovid19();
    vector<vector<LinkedList<Cordinates *> *>> Users;
    for (int x = 0; x < 2; x++)
    {
        Users.push_back(simulation.GenerateDay());
        3
    }

    Users[1][1]->pointerprint();
}

//     vector<LinkedList<Cordinates *> *> Day;
//     Cordinates *temp;

//     Cordinates *movingCordinates;
//     //before this there will be a menu asking if i want to continue using the app but for now lets focus on each day seperately

//     for (int i = 0; i < MAX_USER; i++)
//     {
//         Day.push_back(new LinkedList<Cordinates *>());
//         start = 30;
//         while (start < day)
//         //At the start of each day
//         //first time we genarate our random points will be the starting position of our "person" so both (x,y) = random() .
//         //This will be our starting point so we will initiate our Corindates object and Link List and save them there

//         {
//             if (start == 30) //Random STARTING POINT FOR EVERY USER
//             {
//                 int randnumb = 1 + (rand() % 50);
//                 //the starting point for each person on each day
//                 Cordinates *startingCordinates = new Cordinates(randnumb, randnumb, start);
//                 temp = startingCordinates;
//                 Day[i]->addAtBack(startingCordinates);
//             }
//             else
//             {

//                 int randomchoice = rand() & 1;
//                 switch (randomchoice)
//                 {
//                 case 0:
//                     simulation.RandomCordinates(temp);
//                     movingCordinates = new Cordinates(temp->x, temp->y, start);
//                     Day[i]->addAtBack(movingCordinates);
//                     temp = movingCordinates;
//                     break;
//                 case 1:
//                     break;
//                 }
//             }
//             start = start + step;
//         }
//     }
//     Users.push_back(Day);
// }