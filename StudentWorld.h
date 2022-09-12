#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class BaseActor;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    ~StudentWorld() {cleanUp();}
    BaseActor* getGhostRacer() {return ghostracer;}

private:
    std::vector<BaseActor*> actors;
    BaseActor* ghostracer;
    int last_y;
};

#endif // STUDENTWORLD_H_
