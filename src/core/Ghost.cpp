#include <iostream>
#include <vector>
#include "Ghost.h"

using namespace std;

Ghost::Ghost(){
    position = {0, 0};
    force = {0, 0};
    health = 0;
    strenght = 0;
}

Ghost::Ghost(Vector2D posInit, Vector2D forceInit, int healthInit, int strenghtInit, vector<Projectile> tabProjectile){
    position = posInit;
    force = forceInit;
    health = healthInit;
    strenght = strenghtInit;
    projectile = tabProjectile;
}

Ghost::~Ghost(){
    
}

int Ghost::getStrenght() const{
    return strenght;
}

void Ghost::flyToPlayer(Game &game){
    
}