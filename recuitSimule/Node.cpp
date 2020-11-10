#include "Node.hpp"
#include<algorithm>
#include<sstream>
#include <cmath>

#include<iostream>
using namespace std;

float Node::calculateDistance(const Node& point,bool geoMode) const
{
    float distance;
    if(geoMode)
    {
        float RRR = 6378.388;

        float q1 = cos( point.y - y );
        float q2 = cos( point.x - x );
        float q3 = cos( point.x + x );
        distance = RRR * acos( 0.5*((1.0+q1)*q2 - (1.0-q1)*q3) ) + 1.0;
    }
    else
        distance = sqrt(pow(point.x - x, 2) + pow(point.y - y, 2));
    return distance;
}

void Node::setAlreadyTaken(bool value)
{
    alreadyTaken = value;
}

long Node::getLogicalNumber() const
{
    return logicalNumber;
}

pair<float, float> Node::getPos() const
{
    return make_pair(x,y);
}

bool Node::getAlreadyTaken() const
{
    return alreadyTaken;
}

bool Node::getIsStart() const
{
    return isStart;
}