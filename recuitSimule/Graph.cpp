#include "Graph.hpp"
#include <cmath>
#include <cassert>

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

const Node& Graph::getNearestNode(long nodeId)
{
    //TODO implémentation
}

float Graph::getDistanceBetweenNPoints(Node& p...)
{
    //TODO distMat.get(p2.id).get(p1.id)
}

const map<long, Node>& Graph::getGraphListing() const
{
    return graphListing;
}

const vector<vector<float>>& Graph::getDistMat() const
{
    return distMat;
}