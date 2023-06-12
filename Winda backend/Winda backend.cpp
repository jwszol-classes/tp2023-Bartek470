
#include <stdlib.h> //srand, rand
#include <time.h> //time
//potrzebne do zapoczątkowania ziarna losującego oraz wygenerowania liczby losowej
#include <iostream>
#include <queue>
#include<vector>

const unsigned int NUMBER_OF_FLOORS = 5;
const unsigned int ELEVATOR_CAPACITY = 10;
//charakterystyka windy

const unsigned int MIN_PASSANGER_WEIGHT = 60;
const unsigned int MAX_PASSANGER_WEIGHT = 80;
//zakres wagi pasazerow

class Human
{
private:
    unsigned int start_floor;
    unsigned int end_floor;
    unsigned int weight;
public:
    void assign_start_floor(int x)
    {
        start_floor = x;
    }
    void assign_end_floor(int x)
    {
        end_floor = x;
    }
    void assign_weight() //wartość losowa między 60 a 80
    {
        srand(time(NULL));
        weight = MIN_PASSANGER_WEIGHT + rand() % (MAX_PASSANGER_WEIGHT - MIN_PASSANGER_WEIGHT);
    }
};

struct Order
{
    unsigned int get_in;
    unsigned int get_out;
};

void movement(bool *floor,std::queue<unsigned int>& que)
{
    int curentfloor = 0;
    int qorder = 0;
    for (int i = 0; i < NUMBER_OF_FLOORS; i++)
    {
        if (floor[i] == 1) curentfloor = i + 1;
    }
    if (que.size() >= 1)
    {
        qorder = que.front();
        que.pop();
    }
    if (qorder != 0)
    {
        if (qorder == curentfloor)
        {
            //pozostanie na pietrze
        }
        else if (qorder > curentfloor)
        {
            //ruch w gore
        }
        else if (qorder < curentfloor)
        {
            //ruch w dol
        }
    }
}

void get_command(std::queue<Order>&qpas)
{
    unsigned int sfloor;
    unsigned int efloor;
    std::cout << "podaj pietro startowe" << std::endl;
    std::cin >> sfloor;
    std::cout << "podaj pietro koncowe" << std::endl;
    std::cin >> efloor;
    if (0 < sfloor <= NUMBER_OF_FLOORS && 0 < efloor <= NUMBER_OF_FLOORS)
    {
        qpas.push(Order{ sfloor,efloor });
    }
    else
        std::cout << "jedno z podanych pieter nie istnieje" << std::endl;
}

void Q_manger(unsigned int *in, unsigned int *out, unsigned int *result)
{

}

void Ele_manger(unsigned int* result, Human *elev)
{

}

int main()
{
    bool works = 1;
    bool stop = 1;
    Human elevator[ELEVATOR_CAPACITY];
    bool which_floor[NUMBER_OF_FLOORS] = {1,0,0,0,0};
    
    std::queue<Order>qpasangers;
    

    while (works == 1)
    {
        get_command(qpasangers);

    }

    return 0;
}

