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

    bool alreadyTaken;
    bool isStart;
public:
    Node(long nId,float xCoord,float yCoord):id(nId),x(xCoord),y(yCoord),alreadyTaken(false),isStart(false){};

    float calculateDistance(Node& point);

    void setAlreadyTaken(bool value);

    long getId() const;
    std::pair<float, float> getPos() const;
    bool getAlreadyTaken() const;
    bool getIsStart() const;

    ~Node(){};
};
