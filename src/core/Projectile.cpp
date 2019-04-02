#include <iostream>
#include "Projectile.h"
#include "Entity.h"

using namespace std;

Projectile::Projectile()
{
    position = {0, 0};
    force = {0, 0};
    damages = 0;
    spriteName = " ";
}

Projectile::Projectile(Vector2D posInit, Vector2D forceInit, int damagesInit, string name)
{
    position = posInit;
    force = forceInit;
    damages = damagesInit;
    spriteName = name;
}

Projectile::~Projectile()
{
}

/* Projectile::move(Vector2D dep, Game &game)
{
    Entity e;
    isHit=false;
    while(position.x != dep.x)
    {
        position.x += force.x;
        if (position.x == e.position.x && position.y == e.position.y)
        {
            game.jesaispasebcore
            hit(e);
            isHit = true;
        }
    }
    
}*/

void Projectile::hit(Entity &e)
{
    e.receiveDamage(damages);
}