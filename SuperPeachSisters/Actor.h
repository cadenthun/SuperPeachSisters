#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

//********************
//Actor class below

class Actor : public GraphObject
{
    
public:
    Actor();
    virtual void doSomething();
    
private:
    
};

Actor::Actor()
:GraphObject(<#int imageID#>, <#int startX#>, <#int startY#>)
{
    
}

void Actor::doSomething()
{}

//Actor class above
//********************
//********************
//Block class below

class Block : public Actor
{
public:
    Block();
private:
    
};

Block::Block()
{
    
}



//Block class above
//********************
//********************
//Peach class below

class Peach : public Actor
{
public:
    virtual void doSomething();
private:
};

void Peach::doSomething()
{
    
}

//Peach class above
//********************
//********************

#endif // ACTOR_H_
