#include "Node.hpp"
#include<algorithm>
#include<sstream>
#include <cmath>

#include<iostream>
using namespace std;

float Node::calculateDistance(Node& point)
{
    return sqrt(pow(point.x - x, 2) + pow(point.y - y, 2));
}

void Node::setAlreadyTaken(bool value)
{
    alreadyTaken = value;
}

long Node::getId()
{
    return id;
}

pair<float, float> Node::getPos()
{
    return make_pair(x,y);
}

bool Node::getAlreadyTaken()
{
    return alreadyTaken;
}

bool Node::getIsStart()
{
    return isStart;
}