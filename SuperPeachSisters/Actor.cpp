#include "Actor.h"
#include "StudentWorld.h"

//********************
//Actor class below



Actor::Actor(int imageID, int startX, int startY, int depth = 0)
: GraphObject(imageID, startX, startY)
{
    m_alive = true;
    m_prevent = false;
    m_damageable = false;
}

void Actor::doSomething() {}
void Actor::bonk() {}

bool Actor::getPrevent()
{
    return m_prevent;
}
bool Actor::getDamageable()
{
    return m_damageable;
}

void Actor::setPrevent(bool prevent)
{
    m_prevent = prevent;
}
void Actor::setDamageable(bool damageable)
{
    m_damageable = damageable;
}

bool Actor::getAlive()
{
    return m_alive;
}

//Actor class above
//********************
//********************
//Block class below

Block::Block(int startX, int startY)
: Actor(IID_BLOCK, startX, startY, 2)
{
    Actor::setPrevent(true);
    m_goodieReleased = false;
}

void Block::doSomething()
{}

void Block::bonk()
{}

//Block class above
//********************
//********************
//Peach class below

Peach::Peach(int startX, int startY)
: Actor(IID_PEACH, startX, startY)
{
    
}

void Peach::doSomething()
{
    
}

//Peach class above
//********************
//********************
