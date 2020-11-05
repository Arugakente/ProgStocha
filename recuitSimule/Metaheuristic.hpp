#pragma once
#include "Graph.hpp"
#include<vector>
#include<algorithm>
#include<sstream>
#include<limits>

#include<iostream>

class Metaheuristic
{
private:
    float temperature;
    float energy;
    std::vector<long> currentPath;
    std::vector<long> generalBestPath;
    std::vector<long> currentBestPath;

    Graph& toCompute;

    void (*randomiser)(std::vector<long>&) ;
    std::vector<long> (*initialBuilder)(Graph&,long) ;
public:
    Metaheuristic(float initTemp,Graph& loaded,void (*randParam)(std::vector<long>&),std::vector<long> (*initParam)(Graph&,long)):temperature(initTemp),energy(std::numeric_limits<float>::max()),currentPath(),generalBestPath(),currentBestPath(),toCompute(loaded),randomiser(randParam),initialBuilder(initParam){};
    const std::vector<long> getCurrentPath();
    const std::vector<long> getGeneralBestPath();
    const std::vector<long> getCurrentBestPath();
    std::vector<long>& solve(int initialIndex = -1);
    float getTemperature();
    float getEnergy();
    ~Metaheuristic(){};
};