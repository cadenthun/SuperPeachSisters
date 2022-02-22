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
  ~StudentWorld();
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  void releaseGoodie(double x, double y, int goodieType);
  bool overlap(double x, double y, bool bonk = NOBONK, bool prevent = PREVENT, bool bonkedByPeach = false);
  bool canFall(double x, double y, int fallDistance);
  bool overlapWithPeach(double x, double y, bool bonk);
  void setPeachAlive(bool alive);
  void setPeachHP(int setVal);
  void setPeachShootPower(bool shootPowerStatus);
  void setPeachJumpPower(bool jumpPowerStatus);
  void setPeachStarPower(bool starPowerStatus);
  bool getPeachStarPower();
  void setLevelStatus(bool status);
  void setGameStatus(bool status);
  
//  void releaseGoodie(double x, double y);

private:
    Peach* m_peachPtr;
    std::vector<Actor*> m_container;
    //container for storing actors
    int m_numLives;
    int m_levelNum;
    
    bool m_levelComplete;
    bool m_gameWon;
};

#endif // STUDENTWORLD_H_
