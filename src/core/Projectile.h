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
  bool isHit;

  Projectile();

  /**
     * @brief Construit un Projectile.
     * 
     * @param position position du projectile.
     * @param force force appliquée au projectile.
     * @param damages dégâts du projectile.
     * @param spriteName nom du sprite du projectile.
     */
  Projectile(Vector2D position, Vector2D force, int damages, string spriteName);

  ~Projectile();

  /**
     * @brief Déplacement du projectile.
     * 
     * @param dep déplacement du projectile.
     * @param game appelle le jeu.
     */
  void move(Vector2D dep, Game &game);

  /**
     * @brief Touche le joueur.
     * 
     * @param e Appelle l'Entité.
     */
  void hit(Entity &e);

private:
  int damages;
  Vector2D force;
};

#endif //MEDIEVALROGUELIKE_PROJECTILE_H