#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include "Level.h"

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

//********************
//Constants below

enum goodieType {flower, mushroom, star};
const bool ALIVE = true;
const bool DEAD = false;
const bool BONK = true;
const bool NOBONK = false;
const bool PREVENT = true;
const bool NOPREVENT = false;
const bool DAMAGEABLE = true;
const bool NOTDAMAGEABLE = false;
const bool BLOCKABLE = true;
const bool NOTBLOCKABLE = false;
const bool LEVELCOMPLETE = true;
const bool LEVELNOTCOMPLETE = false;
const bool GAMEWON = true;
const bool GAMENOTWON = false;

//for Special Blocks

//Constants above
//********************


//********************
//Actor class below

class Actor : public GraphObject
{
    
public:
    Actor(int imageID, double startX, double startY, StudentWorld* currStudentWorld, int depth = 0, int direction = 0);
    virtual void doSomething() = 0;
    virtual void bonk();
    StudentWorld* getWorld();
    bool getPrevent();
    void setPrevent(bool prevent);
    void setDamageable(bool damageable);
    bool getDamageable();
    bool getAlive();
    void setAlive(bool alive);
    
private:
    bool m_alive;
    bool m_prevent; //true if actor will prevent other actors from moving to the spot it currently occupies
    bool m_damageable;
    StudentWorld* m_currStudentWorld;
};

//Actor class above
//********************
//********************
//Ground class below

class Ground: public Actor
{
public:
    Ground(int imageID, double startX, double startY, StudentWorld* currStudentWorld);
    virtual void doSomething();
    virtual void bonk();
private:
};

//Ground class above
//********************
//********************
//Block class below

class Block : public Ground
{
public:
    Block(double startX, double startY, StudentWorld* currStudentWorld);
    virtual void bonk();
private:
};

//Block class above
//********************
//********************
//SpecialBlock class below

class SpecialBlock : public Block
{
public:
    SpecialBlock(double startX, double startY, StudentWorld* currStudentWorld, int goodieHeld);
    virtual void bonk();
private:
    bool m_beenBonked;
    int m_goodieHeld;
};

//SpecialBlock class above
//********************
//********************
//Pipe class below

class Pipe : public Ground
{
public:
    Pipe(double startX, double startY, StudentWorld* currStudentWorld);
};

//Pipe class above
//********************
//********************
//Goodie class below

class Goodie : public Actor
{
public:
    Goodie(int imageID, double startX, double startY, StudentWorld* currStudentWorld);
    void doSomething();
    virtual void doDifferentiatedOverlapStuff() = 0;
    
private:
    
};

//Goodie class above
//********************
//********************
//StemmedGoodie class below

class StemmedGoodie : public Goodie
{
public:
    StemmedGoodie(int imageID, double startX, double startY, StudentWorld* currStudentWorld);
    virtual void doDifferentiatedOverlapStuff();
private:
};

//StemmedGoodie class above
//********************
//********************
//FlowerGoodie class below

class FlowerGoodie : public StemmedGoodie
{
public:
    FlowerGoodie(double startX, double startY, StudentWorld* currStudentWorld);
    virtual void doDifferentiatedOverlapStuff();
private:
};

//FlowerGoodie class above
//********************
//********************
//MushroomGoodie class below

class MushroomGoodie : public StemmedGoodie
{
public:
    MushroomGoodie(double startX, double startY, StudentWorld* currStudentWorld);
    virtual void doDifferentiatedOverlapStuff();
private:
};

//MushroomGoodie class above
//********************
//********************
//StarGoodie class below

class StarGoodie : public Goodie
{
public:
    StarGoodie(double startX, double startY, StudentWorld* currStudentWorld);
    virtual void doDifferentiatedOverlapStuff();
private:
};

//StarGoodie class above
//********************
//********************
//Goal class below

class Goal : public Actor
{
public:
    Goal(int imageID, double startX, double startY, StudentWorld* currStudentWorld);
    virtual void doSomething();
    virtual void doSpecificStuff() = 0;
private:
};

//Goal class above
//********************
//********************
//Flag class below

class Flag : public Goal
{
public:
    Flag(double startX, double startY, StudentWorld* currStudentWorld);
    virtual void doSpecificStuff();
private:
};

//Flag class above
//********************
//********************
//Mario class below

class Mario : public Goal
{
public:
    Mario(double startX, double startY, StudentWorld* currStudentWorld);
    virtual void doSpecificStuff();
private:
};

//Mario class above
//********************
//********************
//Peach class below

class Peach : public Actor
{
public:
    Peach(double startX, double startY, StudentWorld* currStudentWorld);
    virtual void doSomething();
    virtual void bonk();
    void setHP(int setVal);
private:
    int m_hitPoints;
    bool m_shootPower;
    bool m_jumpPower;
    bool m_starPower;
    int m_remainingJumpDistance;
};

//Peach class above
//********************
//********************

#endif // ACTOR_H_
