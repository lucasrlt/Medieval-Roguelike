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
    grounded = true;
}

Entity::Entity(Vector2D positionInit, Vector2D forceInit, int healthInit)
{
    position = positionInit;
    velocity = forceInit;
    health = healthInit;

    grounded = true;
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
    if (grounded)
    {
        velocity.y = 0;
    }
    else
    {
        velocity.y += 10 * dt;
        if (velocity.y > 20)
            velocity.y = 20;
    }

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
}

void Entity::jump()
{
    velocity.y = -10.f;
    grounded = false;
}

void Entity::moveLeft(const TileMap &t)
{
    // if (t.isValidPosition(position.x - 1 < 0 ? -1 : position.x - 1, position.y))
    position.x -= moveA;
}

void Entity::moveRight(const TileMap &t)
{
    // if (t.isValidPosition(position.x + 1, position.y))
    position.x += moveA;
}

void Entity::moveUp(const TileMap &t)
{
    if (t.isValidPosition(position.x, position.y - 1, true))
        position.y -= 0.5;
}

void Entity::moveDown(const TileMap &t, char currDirection)
{
    // if (t.isValidPosition(ceil(position.x), position.y + 1))
    // {
    position.y += 0.04;
    // }
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