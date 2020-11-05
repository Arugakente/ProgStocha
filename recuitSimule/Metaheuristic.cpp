#include "Metaheuristic.hpp"
#include<algorithm>
#include<sstream>

#include<iostream>
using namespace std;

const vector<long> Metaheuristic::getCurrentPath()
{
    vector<long> toReturn;
    for(auto current : currentPath)
        toReturn.push_back(toCompute[current].getLogicalNumber());
    return toReturn;
}

const vector<long> Metaheuristic::getGeneralBestPath()
{
    vector<long> toReturn;
    for(auto current : generalBestPath)
        toReturn.push_back(toCompute[current].getLogicalNumber());
    return toReturn;
}

const vector<long> Metaheuristic::getCurrentBestPath()
{
    vector<long> toReturn;
    for(auto current : currentBestPath)
        toReturn.push_back(toCompute[current].getLogicalNumber());
    return toReturn;
}

float Metaheuristic::getTemperature()
{
    return temperature;
}

float Metaheuristic::getEnergy()
{
    return energy;
}

vector<long>& Metaheuristic::solve(int initialIndex)
{
    vector<long> a = initialBuilder(toCompute,1);
    randomiser(a);

    return generalBestPath;
}
