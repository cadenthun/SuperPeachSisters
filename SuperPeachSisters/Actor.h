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
enum projectileType {piranhaFireball, peachFireball, shell};
const bool ALIVE = true;
const bool DEAD = false;
const bool BONK = true;
const bool DAMAGE = true;
const bool NOBONK = false;
const bool PREVENT = true;
const bool ANYACTOR = true;
const bool ONLYPREVENT = false;
const bool NOPREVENT = false;
const bool DAMAGEABLE = true;
const bool NOTDAMAGEABLE = false;
const bool NODAMAGE = false;
const bool BLOCKABLE = true;
const bool NOTBLOCKABLE = false;
const bool LEVELCOMPLETE = true;
const bool LEVELNOTCOMPLETE = false;
const bool GAMEWON = true;
const bool GAMENOTWON = false;
const bool POWERACTIVATED = true;
const bool POWERDEACTIVATED = false;
const bool BONKEDBYPEACH = true;
const bool PROPEACHOVERLAPPING = true;

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
    virtual void inflictDamage();
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
//Projectile class below

class Projectile : public Actor
{
public:
    Projectile(int imageID, double startX, double startY, StudentWorld* currStudentWorld, int direction);
    virtual void doSomething();
    virtual bool doDifferentiatedStuff() = 0;
private:
};

//Projectile class above
//********************
//********************
//ProPeachProjectile class below

class ProPeachProjectile : public Projectile
{
public:
    ProPeachProjectile(int imageID, double startX, double startY, StudentWorld* currStudentWorld, int direction);
    virtual bool doDifferentiatedStuff();
private:
    
};

//ProPeachProjectile class above
//********************
//********************
//PiranhaFireball class below

class PiranhaFireball : public Projectile
{
public:
    PiranhaFireball(double startX, double startY, StudentWorld* currStudentWorld, int direction);
    virtual bool doDifferentiatedStuff();
private:
};

//PiranhaFireball class above
//********************
//********************
//PeachFireball class below

class PeachFireball : public ProPeachProjectile
{
public:
    PeachFireball(double startX, double startY, StudentWorld* currStudentWorld, int direction);
private:
};

//PeachFireball class above
//********************
//********************
//Shell class below

class Shell : public ProPeachProjectile
{
public:
    Shell(double startX, double startY, StudentWorld* currStudentWorld, int direction);
private:
};

//Shell class above
//********************
//********************
//Enemy class below

class Enemy : public Actor
{
public:
    Enemy(int imageID, double startX, double startY, StudentWorld* currStudentWorld);
    virtual void doSomething();
    virtual void doDifferentiatedStuff() = 0;
    virtual void bonk();
    virtual void inflictDamage();

    
private:
    
};

//Enemy class above
//********************
//********************
//MobileEnemy class below

class MobileEnemy : public Enemy
{
public:
    MobileEnemy(int imageID, double startX, double startY, StudentWorld* currStudentWorld);
    virtual void doDifferentiatedStuff();
    virtual void inflictDamage();
private:
    
};

//MobileEnemy class above
//********************
//********************
//Goomba class below

class Goomba : public MobileEnemy
{
public:
    Goomba(int startX, int startY, StudentWorld* currStudentWorld);
private:
};

//Goomba class above
//********************
//********************
//Koopa class below

class Koopa : public MobileEnemy
{
public:
    Koopa(int startX, int startY, StudentWorld* currStudentWorld);
    virtual void inflictDamage();
private:
    
};

//Koopa class above
//********************
//********************
//Piranha class below

class Piranha : public Enemy
{
public:
    Piranha(int startX, int startY, StudentWorld* currStudentWorld);
    virtual void doDifferentiatedStuff();
private:
    int m_firingDelay;
};

//Piranha class above
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
    void setShootPower(bool shootPowerStatus);
    void setJumpPower(bool jumpPowerStatus);
    void setStarPower(bool starPowerStatus);
    bool getShootPower();
    bool getJumpPower();
    bool getStarPower();
private:
    int m_hitPoints;
    bool m_shootPower;
    bool m_jumpPower;
    bool m_starPower;
    int m_remainingJumpDistance;
    bool m_invincibility;
    bool m_tempInvincibility;
    int m_remainingInvincibility;
    int m_remainingTempInvincibility;
    bool m_inRechargeMode;
    int m_remainingRechargeTime;
};

//Peach class above
//********************
//********************

#endif // ACTOR_H_
