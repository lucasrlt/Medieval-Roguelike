#include <iostream>
#include "Projectile.h"

using namespace std;

Projectile::Projectile(){
    position = {0, 0};
    force = {0, 0};
    damages = 0;
    spriteName = " ";
}

Projectile::Projectile(Vector2D posInit, Vector2D forceInit, int damagesInit, string name){
    position = posInit;
    force = forceInit;
    damages = damagesInit;
    spriteName = name;
}

Projectile::~Projectile(){
    
}

void Projectile::move(Vector2D dep, Game &g){
    position.x += dep.x;
    position.y += dep.y;
}

void Projectile::hit(Entity &e){
    e.receiveDamage(damages);
}