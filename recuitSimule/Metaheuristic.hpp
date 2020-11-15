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
    float evolutionFactor;

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

    bool RTexport;
    std::ofstream ofRT;

public:
    Metaheuristic(float initTemp,float thsld,float evoFactor,Graph& loaded,void (*randParam)(std::vector<long>&),std::vector<long> (*initParam)(Graph&,long),std::string oPath,bool RTE):temperature(initTemp),thresold(thsld),evolutionFactor(evoFactor),
                                                                                                                                                                                energy(0),currentPath(),
                                                                                                                                                                                generalBestEnergy(0),generalBestPath(),
                                                                                                                                                                                currentBestEnergy(0),currentBestPath(),
                                                                                                                                                                                toCompute(loaded),randomiser(randParam),initialBuilder(initParam),
                                                                                                                                                                                outputPath(oPath),currentHistory(),currentBestHistory(),bestHistory(),temperatureHistory(),RTexport(RTE)
                                                                                                                                                                                {
                                                                                                                                                                                    if(RTexport)
                                                                                                                                                                                    {
                                                                                                                                                                                        ofRT.open(outputPath);
                                                                                                                                                                                        ofRT << "temperature,current,temporary_best,overall_best,globalBPath" << std::endl;
                                                                                                                                                                                    }
                                                                                                                                                                                };
    const std::vector<long> getCurrentPath();
    const std::vector<long> getGeneralBestPath();
    const std::vector<long> getCurrentBestPath();
    std::vector<long>& solve(int initialIndex = -1);
    void exportData();
    float getTemperature();
    float getEnergy();
    float getBestMeanEnergy();
    ~Metaheuristic(){};
};