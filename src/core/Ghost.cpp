#include <iostream>
#include <vector>
#include <cassert>
#include "Ghost.h"

using namespace std;

Ghost::Ghost()
{
    position = {0, 0};
    velocity = {0, 0};
    health = 0;
    strength = 0;
    isDead = false;
    isBoss = false;
}

Ghost::Ghost(Vector2D posInit, Vector2D forceInit, int healthInit, int strenghtInit, bool isDeadCheck)
{
    position = posInit;
    velocity = {0, 0};
    health = healthInit;
    strength = strenghtInit;
    isDead = isDeadCheck;
    isBoss = false;
}

Ghost::~Ghost()
{
}

bool Ghost::checkHit(Player *player){
    float width = isBoss ? 2.f : .75f;

    if(!isDead){
        if((position.x <= player->getPosition().x + width && position.x >= player->getPosition().x - width) && 
            (position.y <= player->getPosition().y + width && position.y >= player->getPosition().y - width))  
        {
            player->receiveDamage(strength);
            return true;
        } 
    }
    
    return false;
}


void Ghost::flyToPlayer(Player *player, float dt){
    if(!isDead) {
        // vecteur allant du fantôme vers le joeur
        Vector2D newPos;
        newPos.x = player->getPosition().x - position.x;
        newPos.y = player->getPosition().y - position.y;

        float m = newPos.module();
        if(position.x == 0 && position.y == 0) position = {0, 1};

        position.x = position.x + ((newPos.x / m) * GHOST_SPEED * dt);
        position.y = position.y + ((newPos.y / m) * GHOST_SPEED * dt);
    }
}

void Ghost::regressionTest(){
    Ghost ghost({15, 15}, {10, 10}, 10, 3, false);
    cout << endl << endl << "- TESTS Ghost-" << endl;
    cout << "**************************" << endl;

    assert(!ghost.isDead);
    cout << "--> Ghost initialisé OK" << endl;
}