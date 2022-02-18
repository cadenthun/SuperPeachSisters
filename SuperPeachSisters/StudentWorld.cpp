#include "StudentWorld.h"
#include "Level.h"
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

int StudentWorld::init()
{
    
    Level lev(assetPath());
    ostringstream oss;
    oss.fill('0');
    oss << "level" << setw(2) << getLevel() << ".txt.";
    string level_file = oss.str();
    Level::LoadResult result = lev.loadLevel(level_file);

     if (result == Level::load_fail_file_not_found)
         cerr << "Could not find level01.txt data file" << endl;
     else if (result == Level::load_fail_bad_format)
         cerr << "level01.txt is improperly formatted" << endl;
     else if (result == Level::load_success)
     {
         cerr << "Successfully loaded level" << endl;
         for(int i = 0; i < 31; i++)
            {
                for(int j = 0; j < 31; j++)
                {
                    Level::GridEntry ge;
                    ge = lev.getContentsOf(i, j); // x=5, y=10
                    switch(ge)
                    {
                     case Level::empty:
                        break;
                     case Level::peach:
                        m_peachPtr = new Peach(i, j);
                        break;
                     case Level::block:
                        m_container.push_back(new Block(i, j));
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
    decLives();
    return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
}
