#include <iostream>
#include "Projectile.h"

using namespace std;

Projectile::Projectile()
{
    position = {0, 0};
    velocity = {0, 0};
    damages = 0;
}

Projectile::Projectile(Vector2D posInit, Vector2D velocityInit, int damagesInit)
{
    position = posInit;
    velocity = velocityInit;
    damages = damagesInit;
    isHit = false;
}

Projectile::~Projectile()
{

}
void Projectile::move()
{
    Vector2D newPos;
    newPos = position + velocity;
    if(newPos.x >= 0 && newPos.y >= 0 && newPos.x < 16 && newPos.y < 16)
    {
        position = newPos;
    } 
    else
    {
        isHit = true;
    }
    
}

void Projectile::checkCollision(const TileMap &t)
{
    if((t.getXY(position.x,position.y).type == collision) /*|| (t.getXY(position.x,position.y).type == platform)*/) // Pour que le projectile traverse les plateformes
    {
        isHit = true;
    }
}

void Projectile::hit(Entity &e)
{
    if(!e.isDead && !isHit){
        isHit = true; 
        e.receiveDamage(PROJECTILE_DAMAGES);
        if(e.getHealth() <= 0)
        {
            e.isDead = true;
        }
    }
}

bool Projectile::isGoingRight() const {
    return velocity.x > 0; 
}