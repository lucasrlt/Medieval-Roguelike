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

    movingLeft = movingBottom = movingRight = movingUp = false;

}

Entity::Entity(Vector2D positionInit, Vector2D forceInit, int healthInit)
{
    position = positionInit;
    velocity = forceInit;
    health = healthInit;

    movingLeft = movingBottom = movingRight = movingUp = false;

    grounded = false;
}

Entity::~Entity()
{
}

int Entity::getHealth() const
{
    return health;
}

Vector2D Entity::getForce() const
{
    return velocity;
}

void Entity::receiveDamage(int amount)
{
    health -= amount;
    if (health < 0)
    {
        health = 0;
    }
}

const float moveA = 0.15f;

void Entity::move(Vector2D dep, const TileMap &t, float time)
{
    // if (t.isValidPosition(position.x + dep.x + (dep.x == 0 ? 0 : dep.x > 0 ? 1 : 0), position.y + dep.y + (dep.y == 0 ? 0 : dep.y > 0 ? 1 : 0)))
    // {

    // cout << dep.x << endl;
    // position.x += dep.x;
    // position.y += dep.y;
    // }

    if (t.isValidPosition(position.x + velocity.x * time, (position.y + velocity.y * time) + 1))
    {
        position.x += velocity.x * time;
        position.y += velocity.y * time;

        velocity.y += 10 * time;
        // force.x -= 10 * time;
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

void Entity::show()
{
    cout << "Position: " << position.x << ", " << position.y << endl;
    cout << "Force: " << velocity.x << ", " << velocity.y << endl;
    cout << "Vie: " << health << endl
         << endl;
}

void Entity::regressionTest()
{
    Vector2D pos(10, 10);
    Vector2D force(20, 20);
    int health = 50;
    Entity a(pos, velocity, health);
    assert(a.position.x == 10 && a.position.y == 10 && a.velocity.x == 20 && a.velocity.y == 20 && a.health == 50);
    cout << "Valeurs ok" << endl;
    a.show();

    Vector2D posUp(5, 5);
    // a.move(posUp);
    assert(a.position.x == 15 && a.position.y == 15);
    cout << "move ok" << endl;
    a.show();

    Vector2D forceUp(5, 5);
    a.addForce(forceUp);
    assert(a.velocity.x == 25 && a.velocity.y == 25);
    cout << "addForce ok" << endl;
    a.show();

    int damage = 12;
    a.receiveDamage(damage);
    assert(a.health == 38);
    cout << "receiveDamage ok" << endl;
    a.show();
}