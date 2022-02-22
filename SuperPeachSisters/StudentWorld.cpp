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
                            m_container.push_back(new Block(i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
                            break;
                     case Level::star_goodie_block:
                            m_container.push_back(new Block(i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
                            m_container.push_back(new StarGoodie(i * SPRITE_WIDTH, (j + 1) * SPRITE_HEIGHT, this));

                            break;
                     case Level::mushroom_goodie_block:
                            m_container.push_back(new Block(i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
                            m_container.push_back(new MushroomGoodie(i * SPRITE_WIDTH, (j + 1) * SPRITE_HEIGHT, this));
                            break;
                     case Level::flower_goodie_block:
                        m_container.push_back(new Block(i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
                        m_container.push_back(new FlowerGoodie(i * SPRITE_WIDTH, (j + 1) * SPRITE_HEIGHT, this));
                        break;
                        case Level::pipe:
                            m_container.push_back(new Pipe(i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
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

bool StudentWorld::overlap(double x, double y, bool bonk, bool blockable)
{
    
    vector<Actor*>::iterator it;
    for(it = m_container.begin(); it != m_container.end(); it++)
    {
        if((((*it)->getX() - x >= 0 && (*it)->getX() - x < SPRITE_WIDTH) || (x - (*it)->getX() < SPRITE_WIDTH && x - (*it)->getX() >= 0)) && (((*it)->getY() - y >= 0 && (*it)->getY() - y < SPRITE_HEIGHT) || (y - (*it)->getY() < SPRITE_HEIGHT && y - (*it)->getY() >= 0)))
        {
            if (bonk)
                (*it)->bonk();
            if (blockable == BLOCKABLE && (*it)->getPrevent() == PREVENT)
                return true;
        }
    }
    return false;
}

bool StudentWorld::canFall(double x, double y, int fallDistance)
{
    for (int i = 0; i < fallDistance; i++)
    {
        if (overlap(x, y - (i + 1), NOBONK, BLOCKABLE))
            return false;
    }
    return true;
}

bool StudentWorld::overlapWithPeach(double x, double y)
{
    if(((m_peachPtr->getX() - x >= 0 && m_peachPtr->getX() - x < SPRITE_WIDTH) || (x - m_peachPtr->getX() < SPRITE_WIDTH && x - m_peachPtr->getX() >= 0)) && ((m_peachPtr->getY() - y >= 0 && m_peachPtr->getY() - y < SPRITE_HEIGHT) || (y - m_peachPtr->getY() < SPRITE_HEIGHT && y - m_peachPtr->getY() >= 0)))
        return true;
    return false;
}

void StudentWorld::setPeachHP(int setVal)
{
    m_peachPtr->setHP(setVal);
}


void StudentWorld::cleanUp()
{
    vector<Actor*>::iterator it;
    for(it = m_container.begin(); it != m_container.end(); it++)
    {
        delete (*it);
    }
    vector<Actor*>::iterator it2;
    for(it2 = m_container.begin(); it2 != m_container.end();)
    {
       m_container.erase(it2);
    }
}
