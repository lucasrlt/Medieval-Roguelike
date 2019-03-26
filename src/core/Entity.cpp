#include "Entity.h"
#include "math.h"
#include <iostream>
#include <assert.h>

using namespace std;

Entity::Entity()
{
    position = {0, 0};

    force = {0, -9.81};

    health = 0;
}

Entity::Entity(Vector2D positionInit, Vector2D forceInit, int healthInit)
{
    position = positionInit;
    force = forceInit;
    health = healthInit;
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
    return force;
}

void Entity::receiveDamage(int amount)
{
    health -= amount;
    if (health < 0)
    {
        health = 0;
    }
}

void Entity::move(Vector2D dep, const TileMap &t)
{
    if (t.isValidPosition(position.x + dep.x + (dep.x == 0 ? 0 : dep.x > 0 ? 1 : 0), position.y + dep.y + (dep.y == 0 ? 0 : dep.y > 0 ? 1 : 0)))
    {
        position.x += dep.x;
        position.y += dep.y;
    }
}

void Entity::moveLeft(const TileMap &t)
{
    if (t.isValidPosition(position.x - 1 < 0 ? -1 : position.x - 1, position.y))
        position.x -= 1;
}

void Entity::moveRight(const TileMap &t)
{
    if (t.isValidPosition(position.x + 1, position.y))
        position.x += 1;
}

void Entity::moveUp(const TileMap &t)
{
    if (t.isValidPosition(position.x, position.y - 1, true))
        position.y -= 0.5;
}

void Entity::moveDown(const TileMap &t, char currDirection)
{
    if (t.isValidPosition(ceil(position.x), position.y + 1))
    {
        position.y += 0.01;
    }
}

void Entity::addForce(Vector2D _force)
{
    force.x += _force.x;
    force.y += _force.y;
}

void Entity::show()
{
    cout << "Position: " << position.x << ", " << position.y << endl;
    cout << "Force: " << force.x << ", " << force.y << endl;
    cout << "Vie: " << health << endl
         << endl;
}

void Entity::regressionTest()
{
    Vector2D pos(10, 10);
    Vector2D force(20, 20);
    int health = 50;
    Entity a(pos, force, health);
    assert(a.position.x == 10 && a.position.y == 10 && a.force.x == 20 && a.force.y == 20 && a.health == 50);
    cout << "Valeurs ok" << endl;
    a.show();

    Vector2D posUp(5, 5);
    // a.move(posUp);
    assert(a.position.x == 15 && a.position.y == 15);
    cout << "move ok" << endl;
    a.show();

    Vector2D forceUp(5, 5);
    a.addForce(forceUp);
    assert(a.force.x == 25 && a.force.y == 25);
    cout << "addForce ok" << endl;
    a.show();

    int damage = 12;
    a.receiveDamage(damage);
    assert(a.health == 38);
    cout << "receiveDamage ok" << endl;
    a.show();
}