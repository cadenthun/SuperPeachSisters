#include "StudentWorld.h"
#include "Level.h"
#include "Actor.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "GameConstants.h"
#include <string>
#include <vector>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_levelComplete = LEVELNOTCOMPLETE;
    m_gameWon = GAMENOTWON;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    m_levelComplete = false;
    Level lev(assetPath());
    ostringstream oss;
    oss.fill('0');
    oss << "level" << setw(2) << getLevel() << ".txt";
    string level_file = oss.str();
    Level::LoadResult result = lev.loadLevel(level_file);

     if (result == Level::load_fail_file_not_found)
         cerr << "Could not find level01.txt data file" << endl;
     else if (result == Level::load_fail_bad_format)
         cerr << "level01.txt is improperly formatted" << endl;
     else if (result == Level::load_success)
     {
         cerr << "Successfully loaded level" << endl;
         for(int i = 0; i < 32; i++)
            {
                for(int j = 0; j < 32; j++)
                {
                    Level::GridEntry ge;
                    ge = lev.getContentsOf(i, j); // x=5, y=10
                    switch(ge)
                    {
                     case Level::empty:
                        break;
                     case Level::peach:
                        m_peachPtr = new Peach(i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this);
                        break;
                    case Level::pipe:
                        m_container.push_back(new Pipe(i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
                        break;
                     case Level::block:
                        m_container.push_back(new Block(i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
                        break;
                     case Level::star_goodie_block:
                        m_container.push_back(new SpecialBlock(i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this, star));
                        break;
                     case Level::mushroom_goodie_block:
                        m_container.push_back(new SpecialBlock(i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this, mushroom));
                        break;
                     case Level::flower_goodie_block:
                        m_container.push_back(new SpecialBlock(i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this, flower));
                        break;
                    case Level::flag:
                        m_container.push_back(new Flag(i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
                        break;
                    case Level::mario:
                        m_container.push_back(new Mario(i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
                        break;
                    case Level::goomba:
                        m_container.push_back(new Goomba(i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
                        break;
                    case Level::koopa:
                        m_container.push_back(new Koopa(i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
                        break;
                    case Level::piranha:
                        m_container.push_back(new Piranha(i * SPRITE_WIDTH, j * SPRITE_HEIGHT, this));
                        break;
                     default: break;
                     }
                }
            }
        }
    
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    
    m_peachPtr->doSomething();
    
    for(vector<Actor*>::iterator it2 = m_container.begin(); it2 != m_container.end(); it2++)
    {
        (*it2)->doSomething();
    }
    
    if (m_peachPtr->getAlive() == DEAD)
    {
        playSound(SOUND_PLAYER_DIE);
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    
    for(vector<Actor*>::iterator it = m_container.begin(); it != m_container.end();)
    {
        if((*it)->getAlive() == DEAD)
        {
            delete (*it);
            m_container.erase(it);
            continue;
        }
        it++;
    }
    
    string starPowerText = "";
    if(m_peachPtr->getStarPower() == POWERACTIVATED)
        starPowerText = " StarPower!";
    
    string shootPowerText = "";
    if(m_peachPtr->getShootPower() == POWERACTIVATED)
        shootPowerText = " ShootPower!";
    
    string jumpPowerText = "";
    if(m_peachPtr->getJumpPower() == POWERACTIVATED)
        jumpPowerText = " JumpPower!";
    
    ostringstream screenText;
    screenText << "Lives: " << getLives() << "  Level: " << getLevel() << "  Points: " << getScore() << starPowerText << shootPowerText << jumpPowerText;
    setGameStatText(screenText.str());
    
    if (m_levelComplete == LEVELCOMPLETE)
    {
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    if (m_gameWon == GAMEWON)
    {
        playSound(SOUND_GAME_OVER);
        return GWSTATUS_PLAYER_WON;
    }
    return GWSTATUS_CONTINUE_GAME;
}


void StudentWorld::releaseGoodie(double x, double y, int goodieType)
{
    switch(goodieType)
    {
        case flower:
            m_container.push_back(new FlowerGoodie(x, y + 8, this));
            break;
        case mushroom:
            m_container.push_back(new MushroomGoodie(x, y + 8, this));
            break;
        case star:
            m_container.push_back(new StarGoodie(x, y + 8, this));
            break;
    }
}

void StudentWorld::releaseProjectile(double x, double y, int projectileType, int direction)
{
    switch(projectileType)
    {
        case piranhaFireball:
            m_container.push_back(new PiranhaFireball(x, y, this, direction));
            break;
        case peachFireball:
            m_container.push_back(new PeachFireball(x, y, this, direction));
            break;
        case shell:
            m_container.push_back(new Shell(x, y, this, direction));
            break;
    }
}

bool StudentWorld::overlap(double x, double y, bool bonk, bool blockable, bool damage, bool overlapperProPeachProj)
{
    
    vector<Actor*>::iterator it;
    for(it = m_container.begin(); it != m_container.end(); it++)
    {
        if((((*it)->getX() - x >= 0 && (*it)->getX() - x < SPRITE_WIDTH) || (x - (*it)->getX() < SPRITE_WIDTH && x - (*it)->getX() >= 0)) && (((*it)->getY() - y >= 0 && (*it)->getY() - y < SPRITE_HEIGHT) || (y - (*it)->getY() < SPRITE_HEIGHT && y - (*it)->getY() >= 0)))
        {
            if (bonk && (*it)->getAlive())
                (*it)->bonk();
            if (damage == DAMAGE && (*it)->getAlive())
                (*it)->inflictDamage();
            if (blockable == BLOCKABLE && (*it)->getPrevent() == PREVENT && (*it)->getAlive())
                return true;
            if (overlapperProPeachProj && (*it)->getDamageable() == DAMAGEABLE && (*it)->getX() != x)
                return true;
        }
    }
    return false;
}

bool StudentWorld::overlapWithPeach(double x, double y, bool bonk)
{
    if(((m_peachPtr->getX() - x >= 0 && m_peachPtr->getX() - x < SPRITE_WIDTH) || (x - m_peachPtr->getX() < SPRITE_WIDTH && x - m_peachPtr->getX() >= 0)) && ((m_peachPtr->getY() - y >= 0 && m_peachPtr->getY() - y < SPRITE_HEIGHT) || (y - m_peachPtr->getY() < SPRITE_HEIGHT && y - m_peachPtr->getY() >= 0)))
    {
        if (bonk)
            m_peachPtr->bonk();
        return true;
    }
    return false;
}


bool StudentWorld::canFall(double x, double y, int fallDistance)
{
    for (int i = 0; i < fallDistance; i++)
    {
        if (overlap(x, y - (i + 1), NOBONK, BLOCKABLE))
            return false;
    } 
    return true;
}

bool StudentWorld::onSameLevelAsPeach(double y)
{
    if ((m_peachPtr->getY() - y >= 0 && m_peachPtr->getY() - y <= 1.5 * SPRITE_HEIGHT) || (y - m_peachPtr->getY() >= 0 && y - m_peachPtr->getY() <= 1.5 * SPRITE_HEIGHT))
        return true;
    return false;
}

bool StudentWorld::peachToRight(double x)
{
    if (m_peachPtr->getX() > x)
        return true;
    return false;
}

bool StudentWorld::peachToLeft(double x)
{
    if (m_peachPtr->getX() < x)
        return true;
    return false;
}

int StudentWorld::xDistanceFromPeach(double x)
{
    int absVal = m_peachPtr->getX() - x;
    if (absVal < 0)
        absVal *= -1;
    return absVal;
}

void StudentWorld::setPeachAlive(bool lifeStatus)
{
    m_peachPtr->setAlive(lifeStatus);
}

void StudentWorld::setPeachHP(int setVal)
{
    m_peachPtr->setHP(setVal);
}

void StudentWorld::setPeachShootPower(bool shootPowerStatus)
{
    m_peachPtr->setShootPower(shootPowerStatus);
}

void StudentWorld::setPeachJumpPower(bool jumpPowerStatus)
{
    m_peachPtr->setJumpPower(jumpPowerStatus);
}

void StudentWorld::setPeachStarPower(bool starPowerStatus)
{
    m_peachPtr->setStarPower(starPowerStatus);
}

bool StudentWorld::getPeachStarPower()
{
    return m_peachPtr->getStarPower();
}

void StudentWorld::setLevelStatus(bool status)
{
    m_levelComplete = status;
}

void StudentWorld::setGameStatus(bool status)
{
    m_gameWon = status;
}

void StudentWorld::cleanUp()
{
    delete m_peachPtr;
    vector<Actor*>::iterator it;
    for(it = m_container.begin(); it != m_container.end(); it++)
    {
        delete (*it);
    }
    vector<Actor*>::iterator it2;
    for(it2 = m_container.begin(); it2 != m_container.end();)
    {
       m_container.erase(it2);
    }
}
