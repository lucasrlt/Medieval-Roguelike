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

    idleSprite = " ";
    leftSprite = " ";
    rightSprite = " ";
}

Entity::Entity(Vector2D positionInit, Vector2D forceInit, int healthInit, std::string idle, std::string left, std::string right)
{
    position = positionInit;
    force = forceInit;
    health = healthInit;
    idleSprite = idle;
    leftSprite = left;
    rightSprite = right;
}

Entity::~Entity()
{
}

int Entity::getHealth() const
{
    return health;
}

string Entity::getIdleSprite()const
{
    return idleSprite;
}

string Entity::getLeftSprite()const
{
    return leftSprite;
}

string Entity::getRightSprite()const
{
    return rightSprite;
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
        position.y += 0.04;
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
    std::string nameI = "data/blanc.png";
    std::string nameL = "data/blanc.png";
    std::string nameR = "data/blanc.png";
    Entity e(pos, force, health, nameI, nameL, nameR);
    assert(e.position.x == 10 && e.position.y == 10 && e.force.x == 20 && e.force.y == 20 && e.health == 50);
    cout << "Valeurs ok" << endl;
    e.show();

    Vector2D posUp(5, 5);
    // a.move(posUp);
    assert(e.position.x == 15 && e.position.y == 15);
    cout << "move ok" << endl;
    e.show();

    Vector2D forceUp(5, 5);
    e.addForce(forceUp);
    assert(e.force.x == 25 && e.force.y == 25);
    cout << "addForce ok" << endl;
    e.show();

    int damage = 12;
    e.receiveDamage(damage);
    assert(e.health == 38);
    cout << "receiveDamage ok" << endl;
    e.show();
}