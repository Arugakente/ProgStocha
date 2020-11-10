#include "Metaheuristic.hpp"
#include<algorithm>
#include<sstream>
#include<cmath>

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
    vector<long> currentPath = initialBuilder(toCompute,initialIndex);
    currentBestPath = currentPath;
    generalBestPath = currentPath;
    cout << "original solution" << endl;
    for(auto current : currentPath)
    {
        cout << current << " ";
    }

    energy = toCompute.getDistanceBetweenNPoints(currentPath);
    generalBestEnergy = energy;
    currentBestEnergy = energy;

    while(temperature >= thresold)
    {
        cout << endl;

        randomiser(currentPath);
        energy = toCompute.getDistanceBetweenNPoints(currentPath);
        if(energy < currentBestEnergy || (float(rand())/float((RAND_MAX))) < exp(-(abs(energy-currentBestEnergy)/temperature) ) )
        {
            if(energy < generalBestEnergy)
            {
                generalBestPath = currentPath;
                generalBestEnergy = energy;
            }
            currentBestPath = currentPath;
            currentBestEnergy = energy;
        }
        else
        {
            currentPath = currentBestPath;
            energy = currentBestEnergy;

        }

        cout << temperature << endl;
        cout << "current energy : " << energy << endl;
        cout << "current best energy : " << currentBestEnergy << endl;
        cout << "best energy : " << generalBestEnergy << endl;

        temperature = temperature*0.99999;
    }

    return generalBestPath;
}
