#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include "Level.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

//********************
//Actor class below

class Actor : public GraphObject
{
    
public:
    Actor(int imageID, double startX, double startY, StudentWorld* currStudentWorld, int depth = 0);
    virtual void doSomething() = 0;
    virtual void bonk();
    StudentWorld* getWorld();
    virtual bool getPrevent();
    virtual void setPrevent(bool prevent);
    virtual void setDamageable(bool damageable);
    virtual bool getDamageable();
    bool getAlive();
    
private:
    bool m_alive;
    bool m_prevent;
    bool m_damageable;
    StudentWorld* m_currStudentWorld;
};

//Actor class above
//********************
//********************
//Block class below

class Block : public Actor
{
public:
    Block(double startX, double startY, StudentWorld* currStudentWorld);
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
    Peach(double startX, double startY, StudentWorld* currStudentWorld);
    virtual void doSomething();
    virtual void bonk();
private:
    int m_hitPoints;
};

//Peach class above
//********************
//********************

#endif // ACTOR_H_
