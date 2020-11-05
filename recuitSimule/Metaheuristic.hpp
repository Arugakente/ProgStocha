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
public:
    Metaheuristic(float initTemp):temperature(initTemp),energy(INT32_MAX),currentPath(),generalBestPath(),currentBestPath(){};
    const std::vector<long>& getCurrentPath();
    const std::vector<long>& getGeneralBestPath();
    const std::vector<long>& getCurrentBestPath();
    std::vector<long> solve();
    float getTemperature();
    float getEnergy();
    ~Metaheuristic(){};
};