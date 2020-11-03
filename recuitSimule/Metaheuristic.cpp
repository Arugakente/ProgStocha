#include "Metaheuristic.hpp"
#include<algorithm>
#include<sstream>

#include<iostream>
using namespace std;

const vector<long>& Metaheuristic::getCurrentPath()
{
    return currentPath;
}

const vector<long>& Metaheuristic::getGeneralBestPath()
{
    return generalBestPath;
}

const vector<long>& Metaheuristic::getCurrentBestPath()
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

