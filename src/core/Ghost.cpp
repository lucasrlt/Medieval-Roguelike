#include <iostream>
#include <vector>
#include "Ghost.h"

using namespace std;

Ghost::Ghost(){
    position = {0, 0};
    force = {0, 0};
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
    force = forceInit;
    health = healthInit;
    strenght = strenghtInit;
    // projectile = tabProjectile;
    
    idleSprite = spriteNameIdle;
    leftSprite = spriteNameLeft;
    rightSprite = spriteNameRight;
}

Ghost::~Ghost(){
    
}

int Ghost::getStrenght() const{
    return strenght;
}

void Ghost::flyToPlayer(){
    
}