#pragma once
#include<algorithm>
#include<sstream>
#include<iostream>

class Node
{
private:
    long logicalNumber;
    float x;
    float y;

    bool alreadyTaken;
    bool isStart;
public:
    Node(long nId,float xCoord,float yCoord):logicalNumber(nId),x(xCoord),y(yCoord),alreadyTaken(false),isStart(false){};

    float calculateDistance(const Node& point,bool geoMode)const ;

    void setAlreadyTaken(bool value);

    long getLogicalNumber() const;
    std::pair<float, float> getPos() const;
    bool getAlreadyTaken() const;
    bool getIsStart() const;

    ~Node(){};
};
