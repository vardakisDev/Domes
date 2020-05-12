#include "Function.h"
#include <vector>
#include "Simulation.h"

//these methods takes in the given UserTrajectory and fill the missing node that simulated the gps lost singal
//We loop through the list , if we find two nodes that have a time differnce bigger than 30 sec we iniate a loop that runs a loop until the time diference is reduced to 30.
//  tempnode                  time differnce is 60 sec which means there 2 nodes missing            nodeAfterTemp
//      |x,y, z | * |  --->          missing node --->         missing node -->                found node |x1,y1,z+60| * | --- > UserTrajectory
//                      after the newspeed is calculated by the distance between two points we creatte a new cordinate which is calcaluted by the tempNode->data->x +newspeed and the same
//                         goes for the y cordiinate and the z cordinate of the new node is calculated by the temp-data->z+30
//                          then we point to the temp->next to calculate the last missing node
void Functions::REPAIR(LinkedList<Cordinates *> *&UserTrajectory)
{
    Node<Cordinates *> *temp = UserTrajectory->head, *nodeAfterTemp = UserTrajectory->head->next;
    while (nodeAfterTemp)
    {
        if (nodeAfterTemp->data->getZ() - temp->data->getZ() > 30)
        {

            int dt = nodeAfterTemp->data->getZ() - temp->data->getZ();
            while (dt > 30)
            {
                float newSpeed = getAcceleration(temp->data, nodeAfterTemp->data);
                UserTrajectory->InsertAfterNode(temp->getData(), new Cordinates(int(temp->getData()->getX() + newSpeed), int(temp->getData()->getY() + newSpeed), temp->getData()->getZ() + 30));
                dt -= 30;
                temp = temp->next;
            }
        }
        temp = temp->next;
        nodeAfterTemp = nodeAfterTemp->next;
    }
}
//These method takes in two cordinates and builds a square if a user is found innsde the square for a given timeInterval then it increments the user count and at end of its run , it returns it
int Functions::CROWDED_PLACES(std::vector<std::vector<LinkedList<Cordinates *> *>> &Users, Cordinates *point1, Cordinates *point2, int Day, int timeInterval)
{

    //https://math.stackexchange.com/questions/190111/how-to-check-if-a-point-is-inside-a-rectangle
    // https://math.stackexchange.com/questions/506785/given-two-diagonally-opposite-points-on-a-square-how-to-calculate-the-other-two
    int users = 0, time;
    float xc = (point1->x + point2->x) / 2; // Center point
    float xd = (point1->x - point2->x) / 2; // Half-diagonal
    float yc = (point1->y + point2->y) / 2; // Center point
    float yd = (point1->y - point2->y) / 2; // Half-diagonal
    //third corner
    Cordinates *point3 = new Cordinates(int((xc - yd)), int((yc + xd)), 0);
    //fourth corner
    Cordinates *point4 = new Cordinates(int((xc + yd)), int((yc - xd)), 0);
    for (int i = 0; i < Users.size(); i++)
    {
        time = 0;
        Node<Cordinates *> *temp = Users[Day][i]->head;
        while (temp)
        { //if the point lies inside these cordinates increment the ti e
            if ((temp->data->x >= point1->x && temp->data->x <= point4->x) && (temp->data->y >= point2->y && temp->data->y <= point2->y))
            {
                time += 30;
                //if the time is the same as the given timeinterval then increment the user count and break
                if (time == timeInterval)
                {
                    users++;
                    break;
                }
            }

            temp = temp->next;
        }
    }

    return users;
}
//takes in the usertrajectory and iterates through the whole vector of the given day , if the given usertrajectory cordinates ,
//is found inside the the R = 2 diameter of the an infected user and for a given time then , it returns true .
bool Functions::POSSIBLE_COVID_19_INFECTION(std::vector<LinkedList<Cordinates *> *> &Users, LinkedList<Cordinates *> *&UserTrajectory, std::vector<bool> &ListOfCovid19, int possible)
{
    int time = 0;
    Simulation simulation;
    for (int i = 0; i < Users.size(); i++)
    {
        //if its the same list skip it
        if (i == possible)
            i++;
        //head points at the head of the user we want to find out  and the previous visited will be where we save the previous node we visited
        Node<Cordinates *> *head = UserTrajectory->head, *previousVisied = UserTrajectory->head;
        //while the infectedNode will point at the user which is infected
        Node<Cordinates *> *infectedNode = Users[i]->head;
        //if both our user is infected and the user  we look through his trajectory is infected
        if (ListOfCovid19[i] == 1 && ListOfCovid19[possible] == 0)
        {
            while (head && infectedNode)
            {
                //if the point lies outside of the R diameter of th infected user reset the time
                if (!deFineCircle(previousVisied->data, head->data))
                {
                    time = 0;
                }
                //if the point lies inside or on the infected user circle increment time
                if (deFineCircle(infectedNode->data, head->data) && infectedNode->data->z - head->data->z < simulation.timeDiference)
                {
                    previousVisied = head;
                    time += 30;
                    if (infectedNode->next)
                        infectedNode = infectedNode->next;
                    else
                        break;
                }
                //if the user is inside the circle of the infected one for the giventime then he is infected and we return true
                if (time == simulation.timeInside)
                {
                    ListOfCovid19[possible] = 1;
                    return 1;
                }
                head = head->next;
            }
        }
    }
    return 0;
}
//this method takes in the Users vector and minimize the saved data in the list.For the given current day , it runs a loop for DaysBefore .In the loop every point that is inside the center of the previous node it deletes from the list
//if the point is found outside of the center , it takes this point and makes it the new center of the circle and leaves it untouched .
void Functions::SUMMARIZE_TRAJECTORY(std::vector<std::vector<LinkedList<Cordinates *> *>> &Users, int Day, int DaysBefore)
{
    for (int i = Day - DaysBefore; i < Day; i++)
    {
        for (int j = 0; j < Users.size(); j++)
        {
            {
                //the head will be the iterating Node , at first it points at the node after head , while head will be the center at the beggining
                Node<Cordinates *> *head = Users[i][j]->head->next, *temp;
                Node<Cordinates *> *centerOfCircle = Users[i][j]->head;
                while (head)
                {
                    //if the a point lies inside the circle deleted
                    if (deFineCircle(centerOfCircle->data, head->data))
                    {
                        temp = head->next;
                        Users[i][j]->removeNode(head->data);
                    }
                    //else make it the new center and leave it untouched
                    else
                    {
                        centerOfCircle = head;
                        temp = head->next;
                    }
                    head = temp;
                }
            }
        }
    }
    std::cout << "\n Refomarting the previous 4 Days";
    return;
}
