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

    idleSprite = " ";
    leftSprite = " ";
    rightSprite = " ";
}

Ghost::Ghost(Vector2D posInit, Vector2D forceInit, int healthInit, int strenghtInit, /*vector<Projectile> tabProjectile*/
            std::string spriteNameIdle, std::string spriteNameLeft, std::string spriteNameRight) 
            {
    position = posInit;
    velocity = {0, 0};
    health = healthInit;
    strenght = strenghtInit;
    // projectile = tabProjectile;
    
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

void Ghost::checkHit(Player *player){
    if((position.x <= player->position.x + 0.75f && position.x >= player->position.x - 0.75f) && 
    (position.y <= player->position.y + 0.75f && position.y >= player->position.y - 0.75f)) 
        player->receiveDamage(1);
}

void Ghost::flyToPlayer(Player *player){
    float m = position.module();
    if(position.x == 0 && position.y == 0) position = {1, 1};

    position = position + ((player->position - position) * GHOST_SPEED);
    /*player->position - position;*/
}