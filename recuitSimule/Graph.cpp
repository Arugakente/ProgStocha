#include "Graph.hpp"
#include <cmath>
#include <cassert>
#include <cstdarg>

using namespace std;

const Node& Graph::operator[](long nodeId) const
{
    if(graphListing.find( nodeId ) != graphListing.end())
    {
        return graphListing.at(nodeId);
    }
    else
    {
        assert(false);
    }
}

const long Graph::getNearestNode(long nodeId)
{
    
}

float Graph::getDistanceBetweenNPoints(int nbNodes, Node& p1, Node& p2, ...)
{
    float distance = p1.calculateDistance(p2);
    va_list args;
    va_start(args, p2);

    for(int i=0; i<nbNodes-2; ++i){
        cout << "i = " << i << endl;
        Node& p = va_arg(args, Node);
        distance += p2.calculateDistance(p);
        p2 = p;
    }

    va_end(args);

    return distance;
}

void Graph::setTaken(long nodeId)
{
    if(graphListing.find(nodeId) != graphListing.end())
        graphListing.at(nodeId).setAlreadyTaken(true);
}


const map<long, Node>& Graph::getGraphListing() const
{
    return graphListing;
}

const vector<vector<float>>& Graph::getDistMat() const
{
    return distMat;
}

long Graph::getGraphDim() const
{
    return dimention;
}