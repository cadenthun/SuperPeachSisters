#include "Actor.h"
#include "StudentWorld.h"
#include "GameWorld.h"

//********************
//Actor class below



Actor::Actor(int imageID, double startX, double startY, StudentWorld* currStudentWorld, int depth, int direction)
: GraphObject(imageID, startX, startY, direction, depth)
{
    m_alive = true;
    m_prevent = NOPREVENT;
    m_damageable = NOTDAMAGEABLE;
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

void Actor::setAlive(bool alive)
{
    m_alive = alive;
}

//Actor class above
//********************
//********************
//Ground class below

Ground::Ground(int imageID, double startX, double startY, StudentWorld* currStudentWorld)
: Actor(imageID, startX, startY, currStudentWorld, 2)
{
    setPrevent(PREVENT);
    setDamageable(NOTDAMAGEABLE);
}

void Ground::doSomething()
{}

void Ground::bonk()
{}

//Ground class above
//********************
//********************
//Block class below

Block::Block(double startX, double startY, StudentWorld* currStudentWorld)
: Ground(IID_BLOCK, startX, startY, currStudentWorld)
{
}

void Block::bonk()
{
    getWorld()->playSound(SOUND_PLAYER_BONK);
}

//Block class above
//********************
//********************
//SpecialBlock class below

SpecialBlock::SpecialBlock(double startX, double startY, StudentWorld* currStudentWorld, int goodieHeld)
: Block(startX, startY, currStudentWorld)
{
    m_goodieHeld = goodieHeld;
    m_beenBonked = false;
}

void SpecialBlock::bonk()
{
    if (m_beenBonked)
    {
        Block::bonk();
        return;
    }
    getWorld()->playSound(SOUND_POWERUP_APPEARS);
    getWorld()->releaseGoodie(getX(), getY(), m_goodieHeld);
    m_beenBonked = true;
}

//SpecialBlock class above
//********************
//********************
//Pipe class below

Pipe::Pipe(double startX, double startY, StudentWorld* currStudentWorld)
: Ground(IID_PIPE, startX, startY, currStudentWorld)
{}

//Pipe class above
//********************
//********************
//Goodie class below

Goodie::Goodie(int imageID, double startX, double startY, StudentWorld* currStudentWorld)
: Actor(imageID, startX, startY, currStudentWorld, 1)
{
    setPrevent(NOPREVENT); 
    setDamageable(NOTDAMAGEABLE);
}

void Goodie::doSomething()
{
    if (getWorld()->overlapWithPeach(getX(), getY()))
    {
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        doDifferentiatedOverlapStuff(); //REMEMBER TO FILL THIS IN
        setAlive(DEAD);
        return;
    }
    
    if(getWorld()->canFall(getX(), getY(), 2))
    {
        moveTo(getX(), getY() - 2);
    }
    
    if (getDirection() == right)
    {
        if (getWorld()->overlap(getX() + 1, getY(), NOBONK, BLOCKABLE) || getWorld()->overlap(getX() + 2, getY(), NOBONK, BLOCKABLE))
        {
            setDirection(left);
            return;
        }
        moveTo(getX() + 2, getY());
    }
    if (getDirection() == left)
    {
        if (getWorld()->overlap(getX() - 1, getY(), NOBONK, BLOCKABLE) || getWorld()->overlap(getX() - 2, getY(), NOBONK, BLOCKABLE)) //ygugg
        {
            setDirection(right);
            return;
        }
        moveTo(getX() - 2, getY());
    }
}

//Goodie class above
//********************
//********************
//StemmedGoodie class below

StemmedGoodie::StemmedGoodie(int imageID, double startX, double startY, StudentWorld* currStudentWorld)
: Goodie(imageID, startX, startY, currStudentWorld)
{
    
}

void StemmedGoodie::doDifferentiatedOverlapStuff()
{
    getWorld()->setPeachHP(2);
}

//StemmedGoodie class above
//********************
//********************
//FlowerGoodie class below

FlowerGoodie::FlowerGoodie(double startX, double startY, StudentWorld* currStudentWorld)
: StemmedGoodie(IID_FLOWER, startX, startY, currStudentWorld)
{
    
}

void FlowerGoodie::doDifferentiatedOverlapStuff()
{
    StemmedGoodie::doDifferentiatedOverlapStuff();
    getWorld()->increaseScore(50);
    getWorld()->setPeachShootPower(POWERACTIVATED);
    
}

//FlowerGoodie class above
//********************
//********************
//MushroomGoodie class below

MushroomGoodie::MushroomGoodie(double startX, double startY, StudentWorld* currStudentWorld)
: StemmedGoodie(IID_MUSHROOM, startX, startY, currStudentWorld)
{
    
}

void MushroomGoodie::doDifferentiatedOverlapStuff()
{
    StemmedGoodie::doDifferentiatedOverlapStuff();
    getWorld()->increaseScore(75);
    getWorld()->setPeachJumpPower(POWERACTIVATED);
}

//MushroomGoodie class above
//********************
//********************
//StarGoodie class below

StarGoodie::StarGoodie(double startX, double startY, StudentWorld* currStudentWorld)
: Goodie(IID_STAR ,startX, startY, currStudentWorld)
{
    
}

void StarGoodie::doDifferentiatedOverlapStuff()
{
    getWorld()->increaseScore(100);
    getWorld()->setPeachStarPower(POWERACTIVATED);
}

//StarGoodie class above
//********************
//********************
//Goal class below

Goal::Goal(int imageID, double startX, double startY, StudentWorld* currStudentWorld)
: Actor(imageID, startX, startY, currStudentWorld, 1)
{
    setPrevent(NOPREVENT);
    setDamageable(NOTDAMAGEABLE);
}

void Goal::doSomething()
{
    if (!getAlive())
        return;
    if (getWorld()->overlapWithPeach(getX(), getY()))
    {
        getWorld()->increaseScore(1000);
        setAlive(DEAD);
        doSpecificStuff();
    }
}

//Goal class above
//********************
//********************
//Flag class below

Flag::Flag(double startX, double startY, StudentWorld* currStudentWorld)
: Goal(IID_FLAG, startX, startY, currStudentWorld)
{}

void Flag::doSpecificStuff()
{
    if (getWorld()->overlapWithPeach(getX(), getY()))
    {
        getWorld()->setLevelStatus(LEVELCOMPLETE);
    }
}

//Flag class above
//********************
//********************
//Mario class below

Mario::Mario(double startX, double startY, StudentWorld* currStudentWorld)
: Goal(IID_MARIO, startX, startY, currStudentWorld)
{}

void Mario::doSpecificStuff()
{
    if (getWorld()->overlapWithPeach(getX(), getY()))
    {
        getWorld()->setGameStatus(GAMEWON);
    }
}

//Mario class above
//********************
//********************
//Peach class below


Peach::Peach(double startX, double startY, StudentWorld* currStudentWorld)
: Actor(IID_PEACH, startX, startY, currStudentWorld)
{
    setPrevent(NOPREVENT);
    setDamageable(DAMAGEABLE);
    m_hitPoints = 1;
    m_remainingJumpDistance = 0;
}

void Peach::bonk()
{}

void Peach::doSomething()
{
    if (!getAlive())
        return;
    
    (getWorld()->overlap(getX(), getY(), BONK));
    
    if (m_remainingJumpDistance == 0)
    {
        if (getWorld()->canFall(getX(), getY(), 3))
            moveTo(getX(), getY() - 4);
    }
    
    if (m_remainingJumpDistance > 0)
    {
        bool abort = false;
        if (getWorld()->overlap(getX(), getY() + 4, BONK))
        {
            m_remainingJumpDistance = 0;
            abort = true;
        }
        if (!abort)
        {
            moveTo(getX(), getY() + 4);
            m_remainingJumpDistance--;
        }
    }
    
    int ch;
    if (getWorld()->getKey(ch))
     {
     // user hit a key during this tick!
         switch (ch)
         {
         case KEY_PRESS_LEFT:
                 setDirection(left);
                 if(getWorld()->overlap(getX() - 4, getY(), BONK, BLOCKABLE))
                 {
                     break;
                 }
                 moveTo(getX() - 4, getY());
         break;
         case KEY_PRESS_RIGHT:
                 setDirection(right);
                 if(getWorld()->overlap(getX() + 4, getY(), BONK, BLOCKABLE))
                 {
                     break;
                 }
                 moveTo(getX() + 4, getY());
         break;
         case KEY_PRESS_UP:
                 if (getWorld()->overlap(getX(), getY() - 1, NOBONK, BLOCKABLE))
                 {
                     if(m_jumpPower == POWERACTIVATED)
                         m_remainingJumpDistance = 12;
                     else
                         m_remainingJumpDistance = 8;
                     getWorld()->playSound(SOUND_PLAYER_JUMP);
                 }
         case KEY_PRESS_DOWN:
                 
         default: break;
        // case KEY_PRESS_SPACE:
        // ... add fireball in front of Peach...;
       //  break;
         // etc…
         }
     }
}

void Peach::setShootPower(bool shootPowerStatus)
{
    m_shootPower = shootPowerStatus;
}

void Peach::setJumpPower(bool jumpPowerStatus)
{
    m_jumpPower = jumpPowerStatus;
}

void Peach::setStarPower(bool starPowerStatus)
{
    m_starPower = starPowerStatus;
}

bool Peach::getShootPower()
{
    return m_shootPower;
}

bool Peach::getJumpPower()
{
    return m_jumpPower;
}

bool Peach::getStarPower()
{
    return m_starPower;
}

void Peach::setHP(int setVal)
{
    m_hitPoints = setVal;
}

//Peach class above
//********************
//********************
