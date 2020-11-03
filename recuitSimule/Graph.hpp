#pragma once
#include<string>
#include<map>
#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>

#include "Node.hpp"


class Graph
{
private:
    std::map<long,Node> graphListing;
    std::vector<std::vector<float>> distMat;

    std::string name;
    std::string type;
    std::string comment;
    long dimention;
    std::string weightType;
    std::string dataType;
public:
    Graph(std::string inputFile):graphListing(),distMat(),name("none"),type("none"),comment("none"),dimention(0),weightType("none"),dataType("none")
    {
        std::ifstream loadingFile (inputFile);

        if (loadingFile.is_open())
        {
            std::string buffer;

            //loading graph metadata
            while(getline(loadingFile,buffer) && buffer.substr() != "NODE_COORD_SECTION")
            {
                std::stringstream bufferStream(buffer);
                std::string label;
                getline(bufferStream,label,':');
                getline(bufferStream,buffer,':');
                buffer.erase(0, 1);

                if(label == "NAME")
                {
                    name = buffer;
                }
                else if(label == "TYPE")
                {
                    type = buffer;
                }
                else if(label == "COMMENT")
                {
                    comment = buffer;
                }
                else if(label == "DIMENSION")
                {
                    dimention = std::stoi(buffer);
                }
                else if(label == "EDGE_WEIGHT_TYPE")
                {
                    weightType = buffer;
                }
                else if(label == "DISPLAY_DATA_TYPE")
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

                graphListing.insert(std::pair<long,Node>(id,Node(id,x,y)));
            }
            loadingFile.close();

            for(auto const& [key1, val1] : graphListing)
            {
                distMat.push_back(std::vector<float>());
                for(auto const& [key2, val2] : graphListing)
                {
                    distMat.back().push_back(val1.calculateDistance(val2));
                }
            }
        }
        else
        {
            std::cout << "Unable to open file";
        }
    };
    const Node& getNearestNode(long nodeId);
    float getDistanceBetweenNPoints(Node&p1, ...);

    const std::map<long, Node>& getGraphListing();
    const std::vector<std::vector<float>>& getDistMat();

    const Node& operator[](long nodeId);
    ~Graph(){};
};


