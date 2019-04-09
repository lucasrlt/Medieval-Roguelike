#include <iostream>
#include "Projectile.h"

using namespace std;

Projectile::Projectile()
{
    position = {0, 0};
    velocity = {0, 0};
    damages = 0;
    spriteName = " ";
}

Projectile::Projectile(Vector2D posInit, Vector2D velocityInit, int damagesInit, string name)
{
    position = posInit;
    velocity = velocityInit;
    damages = damagesInit;
    spriteName = name;
}
Projectile::~Projectile()
{

}
void Projectile::move()
{
    position = position + velocity;
}
    
void Projectile::hit(Entity &e)
{
    e.receiveDamage(damages);
}