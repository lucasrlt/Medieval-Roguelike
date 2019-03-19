/**
 * @file Projectile.h
 * @author Alexandre PUILLET
 * @brief Module gérant les projectiles
 */

#include <iostream>
#include <vector>
#include <string>
#include "Entity.h"
#include "Vector2D.h"
#include "Game.h"
#ifndef MEDIEVALROGUELIKE_PROJECTILE_H
#define MEDIEVALROGUELIKE_PROJECTILE_H

/**
 * @brief Classe créant les projectiles.
 */

class Projectile
{
public:
  Vector2D position;
  string spriteName;

  Projectile();

  Projectile(Vector2D position, Vector2D force, int damages, string spriteName);

  ~Projectile();

  void move(Vector2D dep, Game &game);

  void hit(Entity &e);

private:
  int damages;
  Vector2D force;
};

#endif //MEDIEVALROGUELIKE_PROJECTILE_H