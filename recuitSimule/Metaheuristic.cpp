#include "Metaheuristic.hpp"
#include <algorithm>
#include <sstream>
#include <cmath>
#include <omp.h>

#include <iostream>
using namespace std;

const vector<long> Metaheuristic::getCurrentPath()
{
    vector<long> toReturn;
    for (auto current : currentPath)
        toReturn.push_back(toCompute[current].getLogicalNumber());
    return toReturn;
}

const vector<long> Metaheuristic::getGeneralBestPath()
{
    vector<long> toReturn;
    for (auto current : generalBestPath)
        toReturn.push_back(toCompute[current].getLogicalNumber());
    return toReturn;
}

const vector<long> Metaheuristic::getCurrentBestPath()
{
    vector<long> toReturn;
    for (auto current : currentBestPath)
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

vector<long> &Metaheuristic::solve(int initialIndex)
{
    currentPath = initialBuilder(toCompute, initialIndex);
    currentBestPath = currentPath;
    generalBestPath = currentPath;

    energy = toCompute.getPathWeight(currentPath);
    generalBestEnergy = energy;
    currentBestEnergy = energy;

    float energyRandom;
    bool bestChanged = true;
    bool solutionValid = true;

    while (temperature >= thresold)
    {
        randomiser(currentPath);

        //cout << temperature << endl;

        energy = toCompute.getPathWeight(currentPath);

        currentHistory.push_back(energy);
        currentBestHistory.push_back(currentBestEnergy);
        bestHistory.push_back(generalBestEnergy);
        temperatureHistory.push_back(temperature);

        if (RTexport)
        {
            ofRT << fixed << temperatureHistory.back() << "," << currentHistory.back() << "," << currentBestHistory.back() << "," << bestHistory.back() << ",";
            if (bestChanged)
            {
                for (auto current : generalBestPath)
                {
                    ofRT << current << " ";
                }
                bestChanged = false;
            }
            else
            {
                ofRT << "NC";
            }
            ofRT << endl;
        }

        if ((energy < currentBestEnergy) || (float(rand()) / float((RAND_MAX))) < exp(-(abs(energy - currentBestEnergy) / temperature)))
        {
            if (!((float(rand()) / float((RAND_MAX))) < exp(-(abs(energy - currentBestEnergy) / temperature))))
            {
                int cptEnergyUp = 0;

                #pragma omp parallel for reduction(+: cptEnergyUp)
                for (int i = 0; i < 100; ++i)
                {
                    energyRandom = toCompute.getPathWeightRandomized(currentPath);

                    if (currentBestEnergy * 1.30 > energyRandom)
                    {
                        cptEnergyUp += 1;
                    }
                }

                if ((float)cptEnergyUp / (float)100 < 0.90f)
                {
                    solutionValid = false;
                }
                else
                {
                    solutionValid = true;
                }
            }
            else
            {
                solutionValid = true;
            }

            if (solutionValid)
            {
                if (energy < generalBestEnergy)
                {
                    generalBestPath = currentPath;
                    generalBestEnergy = energy;
                    bestChanged = true;
                }
                currentBestPath = currentPath;
                currentBestEnergy = energy;
            }
        }
        else
        {
            currentPath = currentBestPath;
            energy = currentBestEnergy;
        }

        temperature = temperature * evolutionFactor;
    }

    return generalBestPath;
}

void Metaheuristic::exportData()
{
    ofstream of;
    of.open(outputPath);
    of << "temperature,current,temporary_best,overall_best" << endl;
    for (size_t i = 0; i < currentHistory.size(); i++)
    {
        of << fixed << temperatureHistory.at(i) << "," << currentHistory.at(i) << "," << currentBestHistory.at(i) << "," << bestHistory.at(i) << endl;
    }
    of.close();
}

float Metaheuristic::getBestMeanEnergy()
{
    return generalBestEnergy;
}