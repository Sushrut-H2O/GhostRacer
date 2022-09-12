#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;
class GhostRacer;

class BaseActor : public GraphObject
{
public:
    BaseActor(StudentWorld* sworld, int imageID, double x_pos, double y_pos, int direction = 0, double actor_size = 1.0, unsigned int graphicalDepth = 0, int playerHealth = 0) : GraphObject(imageID, x_pos, y_pos, direction, actor_size, graphicalDepth)
    {
        m_studentworld = sworld;
        status = GWSTATUS_CONTINUE_GAME;
        health = playerHealth;
    }
    virtual void doSomething() = 0;
    StudentWorld* getWorld();
    int getStatus() const {return status;}
    void setStatus(const int a) {status = a;}
    int getHealth() const {return health;}
    void setHealth(int a) {health = a;}
    int getVSpeed() {return vspeed;}
    void setVSpeed(int a) {vspeed = a;}
private:
    StudentWorld* m_studentworld;
    int status;
    int health;
    int vspeed;
};

class BorderLine : public BaseActor
{
public:
    BorderLine(StudentWorld* sw, int ID, int x, int y) : BaseActor(sw, ID, x, y, 0, 2, 2, 0)
    {
        vspeed = -4;
        hspeed = 0;
        setStatus(GWSTATUS_CONTINUE_GAME);
    }
    void doSomething();
private:
    int vspeed;
    int hspeed;
};

class GhostRacer : public BaseActor
{
public:
    GhostRacer(StudentWorld* sw) : BaseActor(sw, IID_GHOST_RACER, 128, 32, 90, 4, 0, 100)
    {
        setVSpeed(0);
        setStatus(GWSTATUS_CONTINUE_GAME);
    }
    void damageGhostRacer(int damage)
    {
        setHealth(getHealth() - damage);
    }
    void doSomething();
private:
};

#endif // ACTOR_H_
