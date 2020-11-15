#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include <cmath>
#include <cassert>
#include <cstdarg>
#include <random>

#include "Node.hpp"


class Graph
{
private:
    std::vector<Node> graphListing;
    std::vector<std::vector<float>> distMat;

    std::string name;
    std::string type;
    std::string comment;
    unsigned long dimension;
    std::string weightType;
    std::string dataType;
    float varianceCoef;

    std::random_device rd{};
    std::mt19937 gen{rd()};
public:
    Graph(std::string inputFile,float varCo):graphListing(),distMat(),name("none"),type("none"),comment("none"),dimension(0),weightType("none"),dataType("none"),varianceCoef(varCo)
    {
        std::ifstream loadingFile (inputFile);

        if (loadingFile.is_open())
        {
            std::string buffer;

            //loading graph metadata
            while(getline(loadingFile,buffer) && buffer != "NODE_COORD_SECTION")
            {
                std::stringstream bufferStream(buffer);
                std::string label;
                getline(bufferStream,label,':');
                getline(bufferStream,buffer,':');
                buffer.erase(0, 1);

                if(label == "NAME " || label == "NAME")
                {
                    name = buffer;
                }
                else if(label == "TYPE " || label == "TYPE" )
                {
                    type = buffer;
                }
                else if(label == "COMMENT " || label == "COMMENT")
                {
                    comment = buffer;
                }
                else if(label == "DIMENSION " || label == "DIMENSION")
                {
                    dimension = std::stol(buffer);
                }
                else if(label == "EDGE_WEIGHT_TYPE " || label == "EDGE_WEIGHT_TYPE" )
                {
                    weightType = buffer;
                }
                else if(label == "DISPLAY_DATA_TYPE " || label == "DISPLAY_DATA_TYPE" )
                {
                    dataType = buffer;
                }
            }
            //loading graph data
            while(getline(loadingFile,buffer) && buffer != "EOF")
            {
                std::stringstream bufferStream(buffer);

                buffer = "";
                while(buffer == "")
                    getline(bufferStream,buffer,' ');
                long id = std::stol(buffer);

                buffer = "";
                while(buffer == "")
                    getline(bufferStream,buffer,' ');
                float x = std::stof(buffer);

                buffer = "";
                while(buffer == "")
                    getline(bufferStream,buffer,' ');
                float y = std::stof(buffer);

                graphListing.push_back(Node(id,x,y));
            }
            loadingFile.close();

            for(unsigned long i = 0;i<dimension ; i++)
            {
                distMat.push_back(std::vector<float>());
                for(unsigned long j = 0; j<dimension ; j++)
                {
                    distMat.back().push_back(graphListing[i].calculateDistance(graphListing[j],weightType=="GEO"));
                }
            }
        }
        else
        {
            std::cout << "Unable to open file";
        }
    };
    const long getNearestNode(long nodeId);
    float getDistanceBetweenNPoints(int nbNodes, long p1, long p2, ...);
    float getPathWeight(const std::vector<long>& nodeList);
    float getPathWeightRandomized(const std::vector<long>& nodeList);
    float getEffectiveDistance(long id1,long id2);

    void setTaken(unsigned long nodeId);
    void reinitTaken();

    const std::vector<Node>& getGraphListing() const ;
    const std::vector<std::vector<float>>& getDistMat() const;

    unsigned long getGraphDim() const;

    const Node& operator[](unsigned long nodeId) const;
    ~Graph(){};
};


