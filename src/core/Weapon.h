#ifndef MEDIEVAL_ROGUELIKE_WEAPON_H
#define MEDIEVAL_ROGUELIKE_WEAPON_H

#include <string>
#include <vector>
// #include "Projectile.h"

/**
 @brief Module gérant les armes.

 @file Weapon.h
 @date 09/03/2019
 @author Alexandre PUILLET
 */

/**
 * @brief Classe représentant une arme.
 */

class Weapon
{
public:
  unsigned int damages;
  unsigned int attackSpeed;
  float attackRange;

  Weapon();

  /**
     * @brief Arme avec des valeurs.
     * @param damages dégâts de l'arme.
     * @param attackSpeed vitesse d'attaque de l'arme.
     * @param attackRange distance d'attaque de l'arme.
     */
  Weapon(unsigned int damages, unsigned int attackSpeed, float attackRange);

  ~Weapon();

  /**
     * @brief Tests du module.
     */
  void regressionTest();
};

#endif //MEDIEVAL_ROGUELIKE_WEAPON_H