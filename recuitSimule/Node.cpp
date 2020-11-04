#include "Node.hpp"
#include<algorithm>
#include<sstream>
#include <cmath>

#include<iostream>
using namespace std;

float Node::calculateDistance(const Node& point) const
{
    return sqrt(pow(point.x - x, 2) + pow(point.y - y, 2));
}

void Node::setAlreadyTaken(bool value)
{
    alreadyTaken = value;
}

long Node::getId() const
{
    return id;
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