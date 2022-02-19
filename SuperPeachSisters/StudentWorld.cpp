#include "StudentWorld.h"
#include "Level.h"
#include "Actor.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "GameConstants.h"
#include <string>
#include <vector>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    
    Level lev(assetPath());
    ostringstream oss;
    oss.fill('0');
    oss << "level" << setw(2) << getLevel() << ".txt";
    string level_file = oss.str();
    Level::LoadResult result = lev.loadLevel(level_file);

     if (result == Level::load_fail_file_not_found)
         cerr << "Could not find level01.txt data file" << endl;
     else if (result == Level::load_fail_bad_format)
         cerr << "level01.txt is improperly formatted" << endl;
     else if (result == Level::load_success)
     {
         cerr << "Successfully loaded level" << endl;
         for(int i = 0; i < 32; i++)
            {
                for(int j = 0; j < 32; j++)
                {
                    Level::GridEntry ge;
                    ge = lev.getContentsOf(i, j); // x=5, y=10
                    switch(ge)
                    {
                     case Level::empty:
                        break;
                     case Level::peach:
                        m_peachPtr = new Peach(i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this);
                        break;
                     case Level::block:
                     case Level::star_goodie_block:
                     case Level::mushroom_goodie_block:
                     case Level::flower_goodie_block:
                        m_container.push_back(new Block(i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
                        break;
                     default: break;
                     }
                }
            }
        }
    
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //
    decLives();
    
    m_peachPtr->doSomething();
    
    for(vector<Actor*>::iterator it = m_container.begin(); it != m_container.end(); it++)
    {
        (*it)->doSomething();
    }
    return GWSTATUS_CONTINUE_GAME;
}

bool StudentWorld::overlap(double x, double y, bool bonk)
{
    vector<Actor*>::iterator it;
    for(it = m_container.begin(); it != m_container.end(); it++)
    {
        if ((*it)->getY() == y)
        {
            if(((*it)->getX() - x >= 0 && (*it)->getX() - x < SPRITE_WIDTH) || (x - (*it)->getX() < SPRITE_WIDTH && x - (*it)->getX() >= 0))
            {
                if (bonk)
                    (*it)->bonk();
                return true;
            }
        }
    }
    return false;
}



void StudentWorld::cleanUp()
{
    vector<Actor*>::iterator it;
    for(it = m_container.begin(); it != m_container.end(); it++)
    {
        delete (*it);
    }
}
