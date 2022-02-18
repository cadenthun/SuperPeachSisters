#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <iostream>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  StudentWorld* getWorld();
  virtual int init();
  
  virtual int move();
  virtual void cleanUp();

private:
    
    Peach* m_peachPtr;
    std::vector<Actor*> m_container;
    //container for storing actors
};

#endif // STUDENTWORLD_H_
