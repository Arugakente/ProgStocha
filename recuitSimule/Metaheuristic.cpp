#include "Metaheuristic.hpp"
#include<algorithm>
#include<sstream>

#include<iostream>
using namespace std;

const vector<const Node&>& Metaheuristic::getCurrentPath()
{
    return currentPath;
}

const vector<const Node&>& Metaheuristic::getGeneralBestPath()
{
    return generalBestPath;
}

const vector<const Node&>& Metaheuristic::getCurrentBestPath()
{
    return currentBestPath;
}

float Metaheuristic::getTemperature()
{
    return temperature;
}

float Metaheuristic::getEnergy()
{
    return energy;
}

