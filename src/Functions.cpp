#include "Function.h"
#include <vector>
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

int Functions::CROWDED_PLACES(vector<LinkedList<Cordinates *> *> &Users, Cordinates *point1, Cordinates *point2)
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
    cout << point4->x << point4->y << endl
         << point3->x << point3->y << endl;
    for (int i = 0; i < 3; i++)
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

void Functions::POSSIBLE_COVID_19_INFECTION(vector<LinkedList<Cordinates *> *> &Users, LinkedList<Cordinates *> *&UserTrajectory, vector<bool> ListOfCovid19)
{
    for (int i = 0; i < MAX_USER; i++)
    {
        int time = 0;
        Node<Cordinates *> *head = UserTrajectory->head;
        Node<Cordinates *> *infectedNode = Users[i]->head;
        if (Users[i]->head == head)
        {
            i++;
        }
        else
        {
            while (head)
            {
                time = 0;
                while (deFineCircle(infectedNode->data, head->data))
                {
                    time += 30;
                    infectedNode = infectedNode->next;
                    head = head->next;
                    if (time == 900)
                    {
                        cout << "User infected by user" << i << endl;
                        return;
                    }
                }
                head = head->next;
            }
        }
    }
}

void Functions::SUMMARIZE_TRAJECTORY(LinkedList<Cordinates *> *&UserTrajectory)
{
    Node<Cordinates *> *head = UserTrajectory->head->next, *temp;
    Node<Cordinates *> *centerOfCircle = UserTrajectory->head;
    while (head)
    {
        if (deFineCircle(centerOfCircle->data, head->data))
        {
            temp = head->next;
            UserTrajectory->removeNode(head->data);
            cout << "delted" << endl;
        }
        else
        {
            cout << "nop" << endl;
            centerOfCircle = head;
            temp = head->next;
        }
        head = temp;
    }
    return;
}
