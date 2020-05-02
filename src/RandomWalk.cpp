#include <iostream>
#include <random>
#include <time.h>
#include "Cordinates.h"
#include "linkedlist.h"
#include <chrono>
#include <ctime>
using namespace std;
#define MAX_USER 3
#define R 2
#define t1 150  // t1 is the minimum a user stayed in R - distance of infected user
#define t2 7200 //t2 is  minimum time a user stayed in R - distance of infected user

int getDistance(Cordinates *temp1, Cordinates *temp2)
{
    int distance = (int)(pow((temp2->getX() - temp1->getX()), 2) + 0.5) + (int)(pow((temp2->getY() - temp1->getY()), 2) + 0.5);
    return sqrt(distance);
}
int getTimeDiffernce(Cordinates *temp1, Cordinates *temp2)
{
    return temp2->getZ() - temp1->getZ();
}
float getLost(Cordinates *temp1, Cordinates *temp2)
{
    return (float)getDistance(temp1, temp2) / getTimeDiffernce(temp1, temp2);
}

bool deFineCircle(Cordinates *center, Cordinates *toFind)
{
    int distance = int(pow(toFind->x - center->x, 2) + 0.5) + int(pow(toFind->y - center->y, 2) + 0.5);
    int r = R * R;
    if (distance = r || distance < R)
    {
        return true;
    }
    return false;
}

int fixborders(Cordinates *current, int randnumb)
{
    if (current->x + randnumb > 100 | current->y + randnumb > 100 | current->y - randnumb < 0 | current->x - randnumb < 0)
    {
        // cout << "Out of border chanign" << randnumb << "to" << -randnumb << endl;
        randnumb = -randnumb;
        return randnumb;
    }
    return randnumb;
}

void RandomCordinates(Cordinates *temp)
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

//  Στο τέλος μίας συγκεκριμένης
// ημέρας, η τροχιά της ημέρας που απέχει ένα πλήθος ημερών από τη συγκεκριμένη θα αντικαθίσταται
// από μία σύνοψή της. Συγκεκριμένα, έστω (x,y) το πρώτο στίγμα που καταγράφηκε την ημέρα που μας
// ενδιαφέρει. Όλα τα επόμενα στίγματα που απέχουν λιγότερο από R από το στίγμα (x,y) διαγράφονται
// από την αλυσίδα μέχρι να εντοπιστεί το πρώτο στίγμα (x1,y1) που θα είναι εκτός του παραπάνω κύκλου.
// Στη συνέχεια με κέντρο το (x1,y1) η προηγούμενη διαδικασία επαναλαμβάνεται μέχρι να φτάσουμε στο
// τέλος της ημέρας.
LinkedList<Cordinates *> SUMMARIZE_TRAJECTORY(LinkedList<Cordinates *> UserTrajectory)
{
    Node<Cordinates *> *head = UserTrajectory.head->next;
    Node<Cordinates *> *centerOfCircle = head;
    while (head->next)
    {
        if (deFineCircle(centerOfCircle->data, head->data))
        {
            UserTrajectory.removeNode(head->data);
            cout << "deleted" << endl;
            head = head->next;
        }
        else
        {
            centerOfCircle = head;
            head = head->next;
        }
    }
    return UserTrajectory;
}

//This function generates a random list of covid-19 patients , sry for the guys that got 1 meaning positive !!!
vector<bool> GetListOfCovid19()
{

    vector<bool> ListOfCovid19;
    for (int i = 0; i < MAX_USER; i++)
    {
        int randomchoice = (rand() % 2);
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
//(leadingNode->data->getX() + 2 < temp->data->getX()) && (leadingNode->data->x > temp->data->x) && (leadingNode->data->y + 2 < temp->data->y) && (leadingNode->data->y > temp->data->y))
void PosibleCovid19Infection(vector<LinkedList<Cordinates *> *> &Users, LinkedList<Cordinates *> *&UserTrajectory, vector<bool> ListOfCovid19)
{
    for (int i = 0; i < MAX_USER; i++)
    {
        if (Users[i] != UserTrajectory)
        {
            Node<Cordinates *> *leadingNode = UserTrajectory->head; //leading node that will be checked for ebvery cordinates on all the lists
            while (leadingNode)
            {
                Node<Cordinates *> *temp = Users[i]->head;
                while (temp)
                {
                    if (deFineCircle(temp->data, leadingNode->data))
                    {
                        cout << "in R" << endl;
                        cout << temp->data->x << "   " << temp->data->y << endl;
                        cout << leadingNode->data->x << "   " << leadingNode->data->y << endl;
                    }
                    temp = temp->next;
                }
                leadingNode = leadingNode->next;
            }
        }
        else
        {
            i++;
        }
    }
};

void REPAIR(LinkedList<Cordinates *> *&UserTrajectory)
{
    Node<Cordinates *> *temp = UserTrajectory->head, *nodeAfterTemp = UserTrajectory->head->next;
    while (nodeAfterTemp)
    {
        if (nodeAfterTemp->data->getZ() - temp->data->getZ() > 30)
        {

            int dt = nodeAfterTemp->data->getZ() - temp->data->getZ();
            while (dt > 30)
            {
                float newSpeed = getLost(temp->data, nodeAfterTemp->data);
                UserTrajectory->InsertAfterNode(temp->getData(), new Cordinates(int(temp->getData()->getX() + newSpeed), int(temp->getData()->getY() + newSpeed), temp->getData()->getZ() + 30));
                dt -= 30;
                temp = temp->next;
            }
        }
        temp = temp->next;
        nodeAfterTemp = nodeAfterTemp->next;
    }
}

int FIND_CROWDED_PLACES(vector<LinkedList<Cordinates *> *> &Users, Cordinates *point1, Cordinates *point2)
{
    // https://math.stackexchange.com/questions/506785/given-two-diagonally-opposite-points-on-a-square-how-to-calculate-the-other-two
    int users = 0;
    float xc = (point1->x + point2->x) / 2;
    float xd = (point1->x - point2->x) / 2;
    float yc = (point1->y + point2->y) / 2;
    float yd = (point1->y - point2->y) / 2;

    Cordinates *point3 = new Cordinates(int((xc - yd)), int((yc + xd)), 0);
    Cordinates *point4 = new Cordinates(int((xc + yd)), int((yc - xd)), 0);
    cout << point4->x << point4->y << endl
         << point3->x << point3->y << endl;
    for (int i = 0; i < MAX_USER; i++)
    {

        Node<Cordinates *> *temp = Users[i]->head;
        while (temp)
        {
            if ((temp->data->x >= point1->x && temp->data->x <= point4->x) && (temp->data->y >= point2->y && temp->data->y <= point2->y))
            {
                users++;
            }

            temp = temp->next;
        }
    }

    return users;
}

int main()
{
    vector<LinkedList<Cordinates *> *> Users;

    auto lol = chrono::system_clock::now();
    time_t startingTime = chrono::system_clock::to_time_t(lol);
    cout << ctime(&startingTime);

    int step = 30;  //SECONDS BY WHICH WE INCREMENT OUR LOOP , STEP = SEC
    int day = 3000; //each day  == FULL DAY
    int start = 30; //THE APP STARTS FROM THE 30SEC OF EACH DAY
    int max = 50;   //MAX  ?
                    //SO WE WILL HAVE TO DEFINE DxD  WHICH WILL BE THE  area in which our simulated persons will be "walking" . Also Dxd Will be our borders
                    //if a user tries to crosses them will change the cordinates by inversing the prosimo and then add them to the previous cordinates in
                    //order to add them to the new node of list after all
    vector<bool> ListOfCovid19 = GetListOfCovid19();
    Cordinates *temp;
    srand(time(0));
    Cordinates *movingCordinates;
    //before this there will be a menu asking if i want to continue using the app but for now lets focus on each day seperately

    for (int i = 0; i < MAX_USER; i++)
    {
        Users.push_back(new LinkedList<Cordinates *>());
        start = 30;
        while (start < day)
        //At the start of each day
        //first time we genarate our random points will be the starting position of our "person" so both (x,y) = random() .
        //This will be our starting point so we will initiate our Corindates object and Link List and save them there

        {
            if (start == 30) //Random STARTING POINT FOR EVERY USER
            {
                int randnumb = 1 + (rand() % 50);
                //the starting point for each person on each day
                Cordinates *startingCordinates = new Cordinates(randnumb, randnumb, start);
                temp = startingCordinates;
                Users[i]->addAtBack(startingCordinates);
            }
            else
            {

                int randomchoice = rand() & 1;
                switch (randomchoice)
                {
                case 0:
                    RandomCordinates(temp);
                    movingCordinates = new Cordinates(temp->x, temp->y, start);
                    Users[i]->addAtBack(movingCordinates);
                    temp = movingCordinates;
                    break;
                case 1:
                    // Users[i]->addAtBack(new Cordinates(0, 0, start));
                    break;
                }
            }
            start = start + step;
        }
    }
    Users[0] = SUMMARIZE_TRAJECTORY(Users[0]);
    for (auto &&x : Users)
    {
        REPAIR(x);

        x->pointerprint();
    }
    cout << FIND_CROWDED_PLACES(Users, new Cordinates(0, 4, 0), new Cordinates(6, 8, 0));

    // PosibleCovid19Infection(Users, Users[0], ListOfCovid19);

    ///repair
    // for (int i = 0; i < 1; i++)
    // {
    //     Node<Cordinates *> *temp = Users[i]->head, *nodeAfterTemp = Users[i]->head->next;
    //     Users[i]->pointerprint();
    //     while (nodeAfterTemp)
    //     {
    //         if (nodeAfterTemp->data->getZ() - temp->data->getZ() > 30)
    //         {

    //             int dt = nodeAfterTemp->data->getZ() - temp->data->getZ();
    //             while (dt > 30)
    //             {
    //                 float newSpeed = getLost(temp->data, nodeAfterTemp->data);
    //                 Users[i]->InsertAfterNode(temp->getData(), new Cordinates(int(temp->getData()->getX() + newSpeed), int(temp->getData()->getY() + newSpeed), temp->getData()->getZ() + 30));
    //                 dt -= 30;
    //                 temp = temp->next;
    //             }
    //         }
    //         temp = temp->next;
    //         nodeAfterTemp = nodeAfterTemp->next;
    //     }

    //     Users[i]->pointerprint();
    // }
}
