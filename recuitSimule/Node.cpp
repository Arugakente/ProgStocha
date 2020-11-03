#include "Node.hpp"
#include<algorithm>
#include<sstream>

#include<iostream>
using namespace std;

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