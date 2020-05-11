#include "Function.h"
#include <vector>
#include "Simulation.h"
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

int Functions::CROWDED_PLACES(vector<vector<LinkedList<Cordinates *> *>> &Users, Cordinates *point1, Cordinates *point2, int Day)
{

    //https://math.stackexchange.com/questions/190111/how-to-check-if-a-point-is-inside-a-rectangle
    // https://math.stackexchange.com/questions/506785/given-two-diagonally-opposite-points-on-a-square-how-to-calculate-the-other-two
    int users = 0;
    float xc = (point1->x + point2->x) / 2;
    float xd = (point1->x - point2->x) / 2;
    float yc = (point1->y + point2->y) / 2;
    float yd = (point1->y - point2->y) / 2;

    Cordinates *point3 = new Cordinates(int((xc - yd)), int((yc + xd)), 0);
    Cordinates *point4 = new Cordinates(int((xc + yd)), int((yc - xd)), 0);
    for (int i = 0; i < Users.size(); i++)
    {

        Node<Cordinates *> *temp = Users[Day][i]->head;
        while (temp)
        {
            if ((temp->data->x >= point1->x && temp->data->x <= point4->x) && (temp->data->y >= point2->y && temp->data->y <= point2->y))
            {
                users++;
                break;
            }

            temp = temp->next;
        }
    }

    return users;
}

bool Functions::POSSIBLE_COVID_19_INFECTION(vector<LinkedList<Cordinates *> *> &Users, LinkedList<Cordinates *> *&UserTrajectory, vector<bool> &ListOfCovid19, int possible)
{
    Simulation simulation;
    for (int i = 0; i < Users.size(); i++)
    {
        if (i == possible)
            i++;

        Node<Cordinates *> *head = UserTrajectory->head, *previousVisied = UserTrajectory->head;
        Node<Cordinates *> *infectedNode = Users[i]->head;
        if (ListOfCovid19[i] == 1 && ListOfCovid19[possible] == 0)
        {
            while (head && infectedNode)
            {
                if (!deFineCircle(previousVisied->data, head->data))
                {
                    simulation.time = 0;
                }
                if (deFineCircle(infectedNode->data, head->data) && infectedNode->data->z - head->data->z < simulation.timeDiference)
                {
                    previousVisied = head;
                    simulation.time += 30;
                    if (infectedNode->next)
                        infectedNode = infectedNode->next;
                    else
                        break;
                }
                if (simulation.time == simulation.timeInside)
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

void Functions::SUMMARIZE_TRAJECTORY(vector<vector<LinkedList<Cordinates *> *>> &Users, int Day, int DaysBefore)
{
    for (int i = Day - DaysBefore; i < Day; i++)
    {
        for (int j = 0; j < Users.size(); j++)
        {
            {
                Node<Cordinates *> *head = Users[i][j]->head->next, *temp;
                Node<Cordinates *> *centerOfCircle = Users[i][j]->head;
                while (head)
                {
                    if (deFineCircle(centerOfCircle->data, head->data))
                    {
                        temp = head->next;
                        Users[i][j]->removeNode(head->data);
                    }
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
    cout << "\n Refomarting the previous 4 Days";
    return;
}
