#include <iostream>
#include <vector>
#include "Ghost.h"

using namespace std;

Ghost::Ghost()
{
    position = {0, 0};
    velocity = {0, 0};
    health = 0;
    strenght = 0;
    isDead = false;
    isBoss = false;

    idleSprite = " ";
    leftSprite = " ";
    rightSprite = " ";
}

Ghost::Ghost(Vector2D posInit, Vector2D forceInit, int healthInit, int strenghtInit, bool isDeadCheck,
            std::string spriteNameIdle, std::string spriteNameLeft, std::string spriteNameRight) 
            {
    position = posInit;
    velocity = {0, 0};
    health = healthInit;
    strenght = strenghtInit;
    isDead = isDeadCheck;
    isBoss = false;
    
    idleSprite = spriteNameIdle;
    leftSprite = spriteNameLeft;
    rightSprite = spriteNameRight;
}

Ghost::~Ghost()
{
}

int Ghost::getStrenght() const
{
    return strenght;
}

bool Ghost::checkHit(Player *player){
    int width = isBoss ? 3.f : .75f;
    if(isDead == false){
        if((position.x <= player->position.x + width && position.x >= player->position.x - width) && 
            (position.y <= player->position.y + width && position.y >= player->position.y - width))  
        {
            player->receiveDamage(strenght);
            return true;
        } 
    }
    return false;
}


void Ghost::flyToPlayer(Player *player){
    if(!isDead){
        Vector2D newPos;
        newPos.x = player->position.x - position.x;
        newPos.y = player->position.y - position.y;
        float m = newPos.module();
        if(position.x == 0 && position.y == 0) position = {1, 1};

        position.x = position.x + ((newPos.x / m) * GHOST_SPEED);
        position.y = position.y + ((newPos.y / m) * GHOST_SPEED);
    }
}