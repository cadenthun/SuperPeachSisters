#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include "Level.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

//********************
//Actor class below

class Actor : public GraphObject
{
    
public:
    Actor(int imageID, int startX, int startY, int depth);
    virtual void doSomething() = 0;
    virtual void bonk();
    virtual bool getPrevent();
    virtual void setPrevent(bool prevent);
    virtual void setDamageable(bool damageable);
    virtual bool getDamageable();
    bool getAlive();
    
private:
    bool m_alive;
    bool m_prevent;
    bool m_damageable;
};

//Actor class above
//********************
//********************
//Block class below

class Block : public Actor
{
public:
    Block(int startX, int startY);
    virtual void doSomething();
    virtual void bonk();
private:
    bool m_goodieReleased;
};

//Block class above
//********************
//********************
//Peach class below

class Peach : public Actor
{
public:
    Peach(int startX, int startY);
    virtual void doSomething();
private:
    int hitPoints;
};

//Peach class above
//********************
//********************

#endif // ACTOR_H_
