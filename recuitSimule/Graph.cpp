#include "Graph.hpp"
#include <cmath>
#include <cassert>
#include <cstdarg>

using namespace std;

const Node& Graph::operator[](long nodeId)
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

const Node& Graph::getNearestNode(long nodeId)
{
    //TODO implémentation
}

float Graph::getDistanceBetweenNPoints(Node& p...)
{
    va_list args;
    va_start(args, p);

    /*while (&p != nullptr) {
        //Node& i = va_arg(args, Node);
        //cout << i.getPos().first;
    }*/

    va_end(args);
}

const map<long, Node>& Graph::getGraphListing()
{
    return graphListing;
}

const vector<vector<float>>& Graph::getDistMat()
{
    return distMat;
}