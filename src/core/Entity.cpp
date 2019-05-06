#include "Entity.h"
#include "math.h"
#include <iostream>
#include <assert.h>

using namespace std;

Entity::Entity()
{
    position = {0, 0};
    velocity = {0, 0};
    health = 0;
    
    grounded = false;
    isDead = false;
    lastDirectionRight = true;
}

Entity::Entity(Vector2D positionInit, Vector2D forceInit, int healthInit)
{
    position = positionInit;
    velocity = forceInit;
    health = healthInit;

    grounded = false;
    isDead = false;
    lastDirectionRight = true;
}

Entity::~Entity()
{

}

int Entity::getHealth() const
{
    return health;
}

Vector2D Entity::getVelocity() const
{
    return velocity;
}

Vector2D Entity::getPosition() const 
{
    return position;
}

void Entity::setPosition(Vector2D pos) {
    position = pos;
}

bool Entity::isMovingRight() const {
    return velocity.x >= 0;
}

void Entity::receiveDamage(int amount)
{
    health -= amount;       
    if (health < 0)
    {
        health = 0;
    }
    if (health > MAX_HEALTH)
    {
        health = MAX_HEALTH;
    }
}



void Entity::updatePosition(const TileMap &t, float dt)
{
    // Applique la gravité
    velocity.y += GRAVITY_SPEED * dt;
    if (velocity.y > MAX_GRAVITY)
        velocity.y = MAX_GRAVITY;

    Vector2D newPos = {position.x + velocity.x * dt, position.y + velocity.y * dt};

    // Collision gauche
    if (velocity.x < 0 && t.isValidPosition(newPos.x, newPos.y) && t.isValidPosition(newPos.x, round(newPos.y))) {
        position.x += velocity.x * dt;
    }  
    // Collision droite
    if (velocity.x > 0 && t.isValidPosition(newPos.x + 1, newPos.y)) {
        position.x += velocity.x * dt;
    }
    
    // Si le joueur est à l'intérieur d'un bloc, on le remet au-dessus du bloc
    if (velocity.x > 0 && velocity.y > 0 && (t.getXY(position.x, floor(position.y + 1)).type == collision || t.getXY(position.x, floor(position.y + 1)).type == platform)) {
        position.y = floor(position.y);
    }

    // Collision haut
    if (velocity.y < 0 && t.isValidPosition(position.x, newPos.y, true)) 
    {
        position.y += velocity.y * dt;
    }
    // Collision bas  
    if (velocity.y > 0 && 
        ((position.x - floor(position.x) >= 0.8f ? 
            t.isValidPosition(ceil(position.x), newPos.y + 1) : 
            t.isValidPosition(round(position.x), newPos.y + 1) && t.isValidPosition(position.x, newPos.y + 1))))
    {
        position.y += velocity.y * dt;
    }

    // Vérifie si le joueur est au sol
    if (velocity.y >= 0 && (!t.isValidPosition(round(newPos.x), newPos.y + 1) || !t.isValidPosition(newPos.x, newPos.y + 1))) {
        grounded = true;
    }
}

void Entity::jump()
{
    if (grounded) 
        velocity.y = -JUMP_SPEED;
    grounded = false;
}

void Entity::moveLeft(const TileMap &t)
{
    velocity.x += -PLAYER_SPEED;
}

void Entity::moveRight(const TileMap &t)
{
    velocity.x += PLAYER_SPEED;
}

void Entity::addForce(Vector2D _force)
{
    velocity.x += _force.x;
    velocity.y += _force.y;
}

void Entity::regressionTest()
{
    Entity e({15, 15}, {10, 10}, 10);
    cout << endl << "- TESTS Entity -" << endl;
    cout << "**************************" << endl;
    e.receiveDamage(12);
    assert(e.health == 0);
    cout << "--> Dégâts reçus OK" << endl;

    Entity en({15, 15}, {10, 10}, 10);
    en.receiveDamage(-4);
    assert(en.health == 10);
    cout << "--> Vie max 10 OK" << endl;
}