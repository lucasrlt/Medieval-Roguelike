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
 * @brief Classe gérant les projectiles. Les projectiles sont principalement des flèches tirées par le joueur.
 * Un projectile peut toucher une éntité et lui infliger des dégâts, ou s'écraser contre un mur.
 * Les projectiles passent à travers les plateformes mais pas les blocs.
 */
class Projectile
{
public:
  /// @brief position du projectile
  Vector2D position;
  /// @brief vrai si le projectile est entré en collision avec quelque chose
  bool isHit;

  Projectile();

  /**
     * @brief Construit un Projectile.
     * 
     * @param position position du projectile.
     * @param velocity vitesse appliquée au projectile.
     * @param damages dégâts du projectile.
     */
  Projectile(Vector2D position, Vector2D velocity, int damages);

  ~Projectile();

  /**
     * @brief Déplacement du projectile. 
     */
  void move();

  /**
   * @brief Check les collisions des projectiles
   * 
   * @param t tilemap en cours
   */
  void checkCollision(const TileMap &t);

  /**
     * @brief Touche le joueur.
     * 
     * @param e Appelle l'Entité.
     */
  void hit(Entity &e);

   /**
    * @brief Check si le projectile va à droite
    * 
    * @return true si il va à droite
    * @return false sinon
    */
  bool isGoingRight() const;

  void regressionTest();

private:
  int damages;
  Vector2D velocity;
};

#endif //MEDIEVALROGUELIKE_PROJECTILE_H