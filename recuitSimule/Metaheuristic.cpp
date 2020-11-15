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
    currentPath = initialBuilder(toCompute,initialIndex);
    currentBestPath = currentPath;
    generalBestPath = currentPath;

    energy = toCompute.getPathWeight(currentPath);
    generalBestEnergy = energy;
    currentBestEnergy = energy;

    while(temperature >= thresold)
    {
        randomiser(currentPath);

        energy = toCompute.getPathWeight(currentPath);

        //ajouter la question de la containte stochastique ici

        currentHistory.push_back(energy);
        currentBestHistory.push_back(currentBestEnergy);
        bestHistory.push_back(generalBestEnergy);
        temperatureHistory.push_back(temperature);

        if(RTexport)
        {
            ofRT << fixed << temperatureHistory.back() << "," <<currentHistory.back() << "," << currentBestHistory.back() << "," << bestHistory.back() << ",";
            for(auto current : generalBestPath)
            {
                ofRT << current << " " ;
            }
            ofRT << endl;
        }

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

        temperature = temperature*evolutionFactor;
    }

    return generalBestPath;
}

void Metaheuristic::exportData()
{
    ofstream of;
    of.open(outputPath);
    of << "temperature,current,temporary_best,overall_best" << endl;
    for(int i = 0; i<currentHistory.size(); i++)
    {
        of << fixed << temperatureHistory.at(i) << "," <<currentHistory.at(i) << "," << currentBestHistory.at(i) << "," << bestHistory.at(i) << endl;
    }
    of.close();
}

float Metaheuristic::getBestMeanEnergy()
{
    return generalBestEnergy;
}