#include "Graph.hpp"
#include <cmath>
#include <cassert>
#include <cstdarg>

using namespace std;

const Node& Graph::operator[](long nodeId) const
{
    if(nodeId>=0 && nodeId<graphListing.size())
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

    vector<float> indexList;
    for(int i=0; i<graphListing.size();i++)
    {
        indexList.push_back(i);
    }

    vector<float> listDist;
    for(int i=0; i<distMat.size(); ++i){
        listDist.push_back(distMat.at(i).at(nodeId));
    }

    listDist.erase(listDist.begin()+nodeId);
    indexList.erase(indexList.begin()+nodeId);

    while (listDist.size()!=0){
        int minElementIndex = std::min_element(listDist.begin(),listDist.end()) - listDist.begin();
        //int minElement = *std::min_element(listDist.begin(), listDist.end());

        if(!graphListing[indexList.at(minElementIndex)].getAlreadyTaken()){
            //cout << minElement << " " << nodeId << " " << graphListing.at(nodeId).getLogicalNumber() << 
            //" " << minElementIndex << " " << graphListing.at(minElementIndex).getLogicalNumber() << endl;
            return indexList.at(minElementIndex);
        }
        else{
            listDist.erase(listDist.begin()+minElementIndex);
            indexList.erase(indexList.begin()+minElementIndex);
        }
    }

    assert(false);
}

float Graph::getDistanceBetweenNPoints(int nbNodes, long p1, long p2, ...)
{
    float distance = graphListing.at(p1).calculateDistance(graphListing.at(p2),weightType=="GEO");
    va_list args;
    va_start(args, p2);

    for(int i=0; i<nbNodes-2; ++i){
        long p = va_arg(args, long);
        distance += graphListing.at(p2).calculateDistance(graphListing.at(p),weightType=="GEO");
        p2 = p;
    }

    va_end(args);

    return distance;
}

float Graph::getPathWeight(const vector<long>& nodeList)
{
    float sum = 0;
    for(int i = 0; i< nodeList.size()-1;i++)
    {
        sum += distMat.at(nodeList[i]).at(nodeList[i+1]);
    }
    return sum;
}

void Graph::setTaken(long nodeId)
{
    if(nodeId>=0 && nodeId<graphListing.size())
        graphListing.at(nodeId).setAlreadyTaken(true);
}

void Graph::reinitTaken()
{
    for(int i = 0 ; i< graphListing.size() ; i++)
    {
        graphListing.at(i).setAlreadyTaken(false);
    }
}

const std::vector<Node>& Graph::getGraphListing() const
{
    return graphListing;
}

const vector<vector<float>>& Graph::getDistMat() const
{
    return distMat;
}

long Graph::getGraphDim() const
{
    return dimension;
}