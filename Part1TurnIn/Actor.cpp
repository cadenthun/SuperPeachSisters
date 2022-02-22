#include "Actor.h"
#include "StudentWorld.h"
#include "GameWorld.h"

//********************
//Actor class below



Actor::Actor(int imageID, double startX, double startY, StudentWorld* currStudentWorld, int depth)
: GraphObject(imageID, startX, startY)
{
    m_alive = true;
    m_prevent = false;
    m_damageable = false;
    m_currStudentWorld = currStudentWorld;
}

void Actor::bonk() {}

StudentWorld* Actor::getWorld()
{
    return m_currStudentWorld;
}


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

Block::Block(double startX, double startY, StudentWorld* currStudentWorld)
: Actor(IID_BLOCK, startX, startY, currStudentWorld, 2)
{
    Actor::setPrevent(true);
    m_goodieReleased = false;
}

void Block::doSomething()
{return;}

void Block::bonk()
{
    getWorld()->playSound(SOUND_PLAYER_BONK);
}

//Block class above
//********************
//********************
//Peach class below

Peach::Peach(double startX, double startY, StudentWorld* currStudentWorld)
: Actor(IID_PEACH, startX, startY, currStudentWorld)
{
    m_hitPoints = 1;
}

void Peach::bonk()
{}

void Peach::doSomething()
{
    int ch;
    if (getWorld()->getKey(ch))
     {
     // user hit a key during this tick!
         switch (ch)
         {
         case KEY_PRESS_LEFT:
                 setDirection(left);
                 if(getWorld()->overlap(getX() - 4, getY(), true))
                 {
                     break;
                 }
                 moveTo(getX() - 4, getY());
         break;
         case KEY_PRESS_RIGHT:
                 setDirection(right);
                 if(getWorld()->overlap(getX() + 4, getY(), true))
                 {
                     break;
                 }
                 moveTo(getX() + 4, getY());
         break;
         default: break;
        // case KEY_PRESS_SPACE:
        // ... add fireball in front of Peach...;
       //  break;
         // etc…
         }
     }
}

//Peach class above
//********************
//********************
