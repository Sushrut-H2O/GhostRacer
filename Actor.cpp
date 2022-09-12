#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

StudentWorld* BaseActor::getWorld()
{
    return m_studentworld;
}

void BorderLine::doSomething()
{
    int horiz_speed = hspeed;
    int vert_speed = vspeed - getWorld()->getGhostRacer()->getVSpeed();
    int new_x = getX() + horiz_speed;
    int new_y = getY() + vert_speed;
    moveTo(new_x, new_y);
    if ((new_x < 0) || (new_y < 0) || (new_x > VIEW_WIDTH) || (new_y > VIEW_HEIGHT))
    {
        setStatus(GWSTATUS_PLAYER_DIED);
        return;
    }
}

void GhostRacer::doSomething()
{
    if (getHealth() <= 0)
    {
        setStatus(GWSTATUS_PLAYER_DIED);
        return;
    }
    else if (getX() <= (ROAD_CENTER - (ROAD_WIDTH/2)))   //Left borderline
    {
        if (getDirection() > 90)
            damageGhostRacer(10);
        setDirection(82);
        getWorld()->playSound(SOUND_VEHICLE_CRASH);
    }
    else if (getX() >= (ROAD_CENTER + (ROAD_WIDTH/2)))   //Right borderline
    {
        if (getDirection() < 90)
            damageGhostRacer(10);
        setDirection(98);
        getWorld()->playSound(SOUND_VEHICLE_CRASH);
    }
    int ch;
    if (getWorld()->getKey(ch))
    {
        switch(ch)
        {
            case KEY_PRESS_LEFT:
            {
                if (getDirection() < 114)
                    setDirection(getDirection() + 8);
                break;
            }
            case KEY_PRESS_RIGHT:
            {
                if (getDirection() > 66)
                    setDirection(getDirection() - 8);
                break;
            }
            case KEY_PRESS_UP:
            {
                if (getVSpeed() < 5)
                    setVSpeed(getVSpeed()+1);
                break;
            }
            case KEY_PRESS_DOWN:
            {
                if (getVSpeed() > -1)
                    setVSpeed(getVSpeed()-1);
                break;
            }
            case KEY_PRESS_SPACE:
                //Holy water
                break;
            default:
                break;
        }
    }
    //Move algorithm
    static const double PI = 4 * atan(1.0);
    const double max_shift_per_tick = 4.0;
    double delta_x = cos((getDirection()*1.0 / 360) * 2 * PI) * max_shift_per_tick;
    //std::cout << "Delta x: " << delta_x << std::endl;
    double cur_x = getX();
    double cur_y = getY();
    //std::cout << "x, y: " << cur_x << ", " << cur_y << std::endl;
    moveTo(cur_x + delta_x, cur_y);
    if (getHealth() <= 0)
    {
        setStatus(GWSTATUS_PLAYER_DIED);
        getWorld()->playSound(SOUND_PLAYER_DIE);
        return;
    }
}
