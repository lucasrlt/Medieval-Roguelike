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
#include "TileMap.h"
#ifndef MEDIEVALROGUELIKE_PROJECTILE_H
#define MEDIEVALROGUELIKE_PROJECTILE_H


const int UPDATE_PROJECTILE = 5;
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
  Projectile(Vector2D position, Vector2D velocity, int damages, string spriteName);

  ~Projectile();

  /**
     * @brief Déplacement du projectile.
     * 
     * @param dep déplacement du projectile.
     * @param game appelle le jeu.
     */
  void move();
  void checkCollision(const TileMap &t);
  /**
     * @brief Touche le joueur.
     * 
     * @param e Appelle l'Entité.
     */
  void hit(Entity &e);

private:
  int damages;
  Vector2D velocity;
};

#endif //MEDIEVALROGUELIKE_PROJECTILE_H