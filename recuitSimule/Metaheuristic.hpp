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
    float thresold;

    float energy;
    std::vector<long> currentPath;

    float generalBestEnergy;
    std::vector<long> generalBestPath;

    float currentBestEnergy;
    std::vector<long> currentBestPath;

    Graph& toCompute;

    void (*randomiser)(std::vector<long>&) ;
    std::vector<long> (*initialBuilder)(Graph&,long) ;

    std::string outputPath;
    std::vector<float> currentHistory;
    std::vector<float> currentBestHistory;
    std::vector<float> bestHistory;
    std::vector<float> temperatureHistory;

public:
    Metaheuristic(float initTemp,float thsld,Graph& loaded,void (*randParam)(std::vector<long>&),std::vector<long> (*initParam)(Graph&,long),std::string oPath):temperature(initTemp),thresold(thsld),
                                                                                                                                  energy(0),currentPath(),
                                                                                                                                  generalBestEnergy(0),generalBestPath(),
                                                                                                                                  currentBestEnergy(0),currentBestPath(),
                                                                                                                                  toCompute(loaded),randomiser(randParam),initialBuilder(initParam),
                                                                                                                                  outputPath(oPath),currentHistory(),currentBestHistory(),bestHistory(),temperatureHistory(){};
    const std::vector<long> getCurrentPath();
    const std::vector<long> getGeneralBestPath();
    const std::vector<long> getCurrentBestPath();
    std::vector<long>& solve(int initialIndex = -1);
    void exportData();
    float getTemperature();
    float getEnergy();
    float getBestEnergy();
    ~Metaheuristic(){};
};