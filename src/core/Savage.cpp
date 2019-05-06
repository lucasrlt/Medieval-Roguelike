#include <iostream>
#include "Savage.h"

using namespace std;
//
Savage::Savage()
{
    position = {0, 0};
    velocity = {0, 0};
    health = 0;
    strength = 0;
}

Savage::Savage(Vector2D posInit, Vector2D forceInit, int healthInit, int strenghtInit, bool isDeadCheck) 
{
    position = posInit;
    velocity = {0, 0};
    health = healthInit;
    strength = strenghtInit;
    isDead = isDeadCheck;
}

Savage::~Savage()
{
}

bool Savage::checkHit(Player *player){
    if(!isDead){
        if((position.x <= player->getPosition().x + 0.75f && position.x >= player->getPosition().x - 0.75f) && 
            (position.y <= player->getPosition().y + 0.75f && position.y >= player->getPosition().y - 0.75f))  
        {
            player->receiveDamage(strength);
            return true;
        } 
    }
    return false;
}

void Savage::runToPlayer(Player *player, const TileMap &t,float dt)
{
    Vector2D newPos;
    
    newPos.x = player->getPosition().x - position.x;
    float m = newPos.module();
    if(newPos.y == 0)
    {
        newPos = {newPos.x,1};
    }
    velocity.x = (newPos.x / m) * SAVAGE_SPEED;

    updatePosition(t,dt);
}
