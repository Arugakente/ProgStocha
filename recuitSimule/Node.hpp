#pragma once
#include<algorithm>
#include<sstream>
#include<iostream>

class Node
{
private:
    long id;
    float x;
    float y;

    bool allreadyTaken;
    bool isStart;
public:
    Node(long nId,float xCoord,float yCoord):id(nId),x(xCoord),y(yCoord),allreadyTaken(false),isStart(false){};
    int getId();
    std::pair<float, float> getPos();
    bool getAlreadyTaken();
    bool getIsStart();

    ~Node();
};

Node::~Node()
{
}
