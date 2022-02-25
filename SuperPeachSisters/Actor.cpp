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
void Actor::inflictDamage() {}

StudentWorld* Actor::getWorld()
{
    return m_currStudentWorld;
}


void Actor::setPrevent(bool prevent)
{
    m_prevent = prevent;
}
void Actor::setDamageable(bool damageable)
{
    m_damageable = damageable;
}

bool Actor::getPrevent()
{
    return m_prevent;
}
bool Actor::getDamageable()
{
    return m_damageable;
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
    if (getWorld()->overlapWithPeach(getX(), getY(), NOBONK))
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
    if (getWorld()->overlapWithPeach(getX(), getY(), NOBONK))
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
    if (getWorld()->overlapWithPeach(getX(), getY(), NOBONK))
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
    if (getWorld()->overlapWithPeach(getX(), getY(), NOBONK))
    {
        getWorld()->setGameStatus(GAMEWON);
    }
}

//Mario class above
//********************
//********************
//Projectile class below

Projectile::Projectile(int imageID, double startX, double startY, StudentWorld* currStudentWorld, int direction)
: Actor(imageID, startX, startY, currStudentWorld, 1, direction)
{
    setPrevent(NOPREVENT);
    setDamageable(NOTDAMAGEABLE);
}

void Projectile::doSomething() //Right now this is only for piranha fireball
{
    if (doDifferentiatedStuff() == DEAD)
        return;
    if (getWorld()->canFall(getX(), getY(), 2))
        moveTo(getX(), getY() - 2);
    if (getDirection() == right)
    {
        if (getWorld()->overlap(getX() + 2, getY(), NOBONK, BLOCKABLE))
        {
            setAlive(DEAD);
            return;
        }
    }
    else
        if (getDirection() == left)
        {
            if (getWorld()->overlap(getX() - 2, getY(), NOBONK, BLOCKABLE))
            {
                setAlive(DEAD);
                return;
            }
        }
    if (getDirection() == right)
        moveTo(getX() + 2, getY());
    else
        if (getDirection() == left)
            moveTo(getX() - 2, getY());
}

//Projectile class above
//********************
//********************
//ProPeachProjectile class below

ProPeachProjectile::ProPeachProjectile(int imageID, double startX, double startY, StudentWorld* currStudentWorld, int direction)
: Projectile(imageID, startX, startY, currStudentWorld, direction)
{
}

bool ProPeachProjectile::doDifferentiatedStuff()
{
    if (getWorld()->overlap(getX(), getY(), NOBONK, BLOCKABLE, DAMAGE, PROPEACHOVERLAPPING))
    {
        setAlive(DEAD);
        return DEAD;
    }
    return ALIVE;
}

//ProPeachProjectile class above
//********************
//********************
//PiranhaFireball class below

PiranhaFireball::PiranhaFireball(double startX, double startY, StudentWorld* currStudentWorld, int direction)
: Projectile(IID_PIRANHA_FIRE, startX, startY, currStudentWorld, direction)
{
    
}


bool PiranhaFireball::doDifferentiatedStuff()
{
    if (getWorld()->overlapWithPeach(getX(), getY(), DAMAGE))
    {
        setAlive(DEAD);
        return DEAD;
    }
    return ALIVE;
}

//PiranhaFireball class above
//********************
//********************
//PeachFireball class below

PeachFireball::PeachFireball(double startX, double startY, StudentWorld* currStudentWorld, int direction)
: ProPeachProjectile(IID_PEACH_FIRE, startX, startY, currStudentWorld, direction)
{
}

//PeachFireball class above
//********************
//********************
//Shell class below

Shell::Shell(double startX, double startY, StudentWorld* currStudentWorld, int direction)
: ProPeachProjectile(IID_SHELL, startX, startY, currStudentWorld, direction)
{
}

//Shell class above
//********************
//********************
//Enemy class below

Enemy::Enemy(int imageID, double startX, double startY, StudentWorld* currStudentWorld)
: Actor(imageID, startX, startY, currStudentWorld, 0, (randInt(0, 1) * 180))
{
    setPrevent(NOPREVENT);
    setDamageable(DAMAGEABLE);
}

void Enemy::doSomething()
{
    if (getAlive() == DEAD)
        return;
    
    if (getWorld()->overlapWithPeach(getX(), getY(), BONK))
        return;
    
    doDifferentiatedStuff();
}

void Enemy::inflictDamage()
{
    getWorld()->increaseScore(100);
    setAlive(DEAD);
}

void Enemy::bonk() //ASSUMING PEACH IS THE ONLY ACTOR WHO CAN CAUSE THIS FUNCTION TO BE CALLED
{
  
    if (getWorld()->getPeachStarPower() == POWERACTIVATED)
    {
        getWorld()->playSound(SOUND_PLAYER_KICK);
        inflictDamage();
    }

}

//Enemy class above
//********************
//********************
//MobileEnemy class below

MobileEnemy::MobileEnemy(int imageID, double startX, double startY, StudentWorld* currStudentWorld)
: Enemy(imageID, startX, startY, currStudentWorld)
{}

void MobileEnemy::doDifferentiatedStuff()
{
    
    if (getDirection() == right)
    {
        if (getWorld()->overlap(getX() + 1, getY(), NOBONK, BLOCKABLE))
            setDirection(left);
        else
            if (!getWorld()->overlap(getX() + SPRITE_WIDTH, getY() - 1, NOBONK, BLOCKABLE))
                setDirection(left);
    }
    
    if (getDirection() == left)
    {
        if (getWorld()->overlap(getX() - 1, getY(), NOBONK, BLOCKABLE))
            setDirection(right);
        else
            if (!getWorld()->overlap(getX() - SPRITE_WIDTH, getY() - 1, NOBONK, BLOCKABLE))
                setDirection(right);
    }
    
    if (getDirection() == right && !getWorld()->overlap(getX() + 1, getY(), NOBONK, BLOCKABLE))
        moveTo(getX() + 1, getY());
    if (getDirection() == left && !getWorld()->overlap(getX() - 1, getY(), NOBONK, BLOCKABLE))
        moveTo(getX() - 1, getY());
}

void MobileEnemy::inflictDamage()
{
    Enemy::inflictDamage();
}

//MobileEnemy class above
//********************
//********************
//Goomba class below

Goomba::Goomba(int startX, int startY, StudentWorld* currStudentWorld)
: MobileEnemy(IID_GOOMBA, startX, startY, currStudentWorld)
{
}

//Goomba class above
//********************
//********************
//Koopa class below

Koopa::Koopa(int startX, int startY, StudentWorld* currStudentWorld)
: MobileEnemy(IID_KOOPA, startX, startY, currStudentWorld)
{}

void Koopa::inflictDamage()
{
    MobileEnemy::inflictDamage();
    getWorld()->releaseProjectile(getX(), getY(), shell, getDirection());
}

//Koopa class above
//********************
//********************
//Piranha class below

Piranha::Piranha(int startX, int startY, StudentWorld* currStudentWorld)
: Enemy(IID_PIRANHA, startX, startY, currStudentWorld)
{
    m_firingDelay = 0;
}

void Piranha::doDifferentiatedStuff()
{
    increaseAnimationNumber();
    if (!getWorld()->onSameLevelAsPeach(getY()))
        return;
    if (getWorld()->peachToRight(getX()))
        setDirection(right);
    if (getWorld()->peachToLeft(getX()))
        setDirection(left);
    if (m_firingDelay == 0)
    {
        if (getWorld()->xDistanceFromPeach(getX()) < 8 * SPRITE_WIDTH)
        {
            getWorld()->releaseProjectile(getX(), getY(), piranhaFireball, getDirection());
            getWorld()->playSound(SOUND_PIRANHA_FIRE);
            m_firingDelay = 40;
        }
    }
    if (m_firingDelay > 0)
    {
        m_firingDelay--;
        return;
    }
}

//Piranha class above
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
    m_shootPower = POWERDEACTIVATED;
    m_jumpPower = POWERDEACTIVATED;
    m_starPower = POWERDEACTIVATED;
}

void Peach::bonk()
{
    if (m_starPower == POWERACTIVATED || m_tempInvincibility)
        return;
    m_hitPoints--;
    m_tempInvincibility = true;
    m_remainingTempInvincibility = 10;
    m_shootPower = POWERDEACTIVATED;
    m_jumpPower = POWERDEACTIVATED;
    if (m_hitPoints > 0)
        getWorld()->playSound(SOUND_PLAYER_HURT);
    if (m_hitPoints <= 0)
        setAlive(DEAD);
}

void Peach::doSomething()
{
    if (!getAlive())
        return;
    
    if (m_remainingInvincibility == 0)
        m_starPower = POWERDEACTIVATED;
    
    if (m_remainingInvincibility > 0)
        m_remainingInvincibility --;
    
    if (m_remainingTempInvincibility == 0)
        m_tempInvincibility = false;
    
    if (m_remainingTempInvincibility > 0)
        m_remainingTempInvincibility --;
    
    if (m_remainingRechargeTime > 0)
        m_remainingRechargeTime --;
    
    (getWorld()->overlap(getX(), getY(), BONK, BLOCKABLE));
    
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
         break;
         case KEY_PRESS_SPACE:
                 if (!m_shootPower)
                     break;
                 if (m_remainingRechargeTime > 0)
                     break;
                 getWorld()->playSound(SOUND_PLAYER_FIRE);
                 m_remainingRechargeTime = 8;
                 if (getDirection() == right)
                     getWorld()->releaseProjectile(getX() + 4, getY(), peachFireball, right);
                 if (getDirection() == left)
                     getWorld()->releaseProjectile(getX() - 4, getY(), peachFireball, left);
                 break;

         default: break;
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
    if (m_starPower == POWERACTIVATED)
        m_remainingInvincibility = 150;
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

int Peach::getRemainingInvincibility()
{
    return m_remainingInvincibility;
}

void Peach::setHP(int setVal)
{
    m_hitPoints = setVal;
}

//Peach class above
//********************
//********************
