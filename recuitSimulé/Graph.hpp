#pragma once
#include<string>
#include<vector>
#include<iostream>
#include <fstream>

#include "Node.hpp"


class Graph
{
private:
    std::vector<Node> graphListing;
public:
    Graph(std::string inputFile):graphListing()
    {
        std::ifstream loadingFile (inputFile);

        if (loadingFile.is_open())
        {
            loadingFile.close();
        }
        else
        {
            std::cout << "Unable to open file";
        }
    };
    ~Graph();
};


Graph::~Graph()
{
}
