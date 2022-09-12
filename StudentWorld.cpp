#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

const int LEFT_EDGE = ROAD_CENTER - (ROAD_WIDTH/2);
const int RIGHT_EDGE = ROAD_CENTER + (ROAD_WIDTH/2);
const int N = VIEW_HEIGHT/SPRITE_HEIGHT;
const int M = VIEW_HEIGHT/(4*SPRITE_HEIGHT);

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::init()
{
    ghostracer = new GhostRacer(this);
    //Add left borderline
    for (int i = 0; i < N; i++)
    {
        actors.push_back(new BorderLine(this, IID_YELLOW_BORDER_LINE, LEFT_EDGE, (i * SPRITE_HEIGHT)));
    }
    //Add right borderline
    for (int i = 0; i < N; i++)
    {
        actors.push_back(new BorderLine(this, IID_YELLOW_BORDER_LINE, RIGHT_EDGE, (i * SPRITE_HEIGHT)));
    }
    //Add borderline between left and middle lane
    for (int i = 0; i < M; i++)
    {
        actors.push_back(new BorderLine(this, IID_WHITE_BORDER_LINE, (LEFT_EDGE + ROAD_WIDTH/3), (i * (4 * SPRITE_HEIGHT))));
    }
    //Add borderline between middle and right lane
    for (int i = 0; i < M; i++)
    {
        actors.push_back(new BorderLine(this, IID_WHITE_BORDER_LINE, (RIGHT_EDGE - ROAD_WIDTH/3), (i * (4 * SPRITE_HEIGHT))));
    }
    last_y = (*(actors.end() - 1))->getY();
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    vector<BaseActor*>::iterator it;
    for (it = actors.begin(); it < actors.end(); it++)
    {
        //Non-GhostRacer actors move
        (*it)->doSomething();
        if (ghostracer->getHealth() <= 0)
        {
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
    }
    //GhostRacer moves
    ghostracer->doSomething();
    
    if (ghostracer->getStatus() == GWSTATUS_PLAYER_DIED)
    {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    cout << "last y: " << last_y << endl;
    last_y -= (ghostracer->getVSpeed() + 4);
    int new_border_y = VIEW_HEIGHT - SPRITE_HEIGHT;
    int delta_y = new_border_y - last_y;
    if (delta_y >= SPRITE_HEIGHT)
    {
        actors.push_back(new BorderLine(this, IID_YELLOW_BORDER_LINE, LEFT_EDGE, new_border_y));
        actors.push_back(new BorderLine(this, IID_YELLOW_BORDER_LINE, RIGHT_EDGE, new_border_y));
    }
    if (delta_y >= (4 * SPRITE_HEIGHT))
    {
        actors.push_back(new BorderLine(this, IID_WHITE_BORDER_LINE, (LEFT_EDGE + ROAD_WIDTH/3), new_border_y));
        actors.push_back(new BorderLine(this, IID_WHITE_BORDER_LINE, (RIGHT_EDGE - ROAD_WIDTH/3), new_border_y));
        last_y = (*(actors.end() - 1))->getY();
    }
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    return ghostracer->getStatus();
}

void StudentWorld::cleanUp()
{
    vector<BaseActor*>::iterator it;
    for (it = actors.end() - 1; it >= actors.begin(); it--)
    {
        delete *it;
    }
    std::vector<BaseActor*>().swap(actors);
    delete ghostracer;
}
