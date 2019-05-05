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
  unsigned int energyCost;
  unsigned int attackSpeed;

  int type;

  float attackRange;

  std::string spriteName;

  Weapon();

  /**
     * @brief Arme avec des valeurs.
     * @param damages dégâts de l'arme.
     * @param energyCost coût en énergie de l'arme.
     * @param attackSpeed vitesse d'attaque de l'arme.
     * @param type type de l'arme.
     * @param attackRange distance d'attaque de l'arme.
     * @param name sprite de l'arme.
     */
  Weapon(unsigned int damages, unsigned int energyCost, unsigned int attackSpeed, int type,
         float attackRange, std::string name);

  ~Weapon();

  /**
     * @brief Récupère les dégâts de l'arme.
     * @return damages (entier > 0).
     */
  unsigned int getDamages();

  /**
     * @brief Affiche l'arme.
     */
  void show();

  /**
     * @brief Tests du module.
     */
  void regressionTest();

private:
  // vector<Projectile> projectile;
};

#endif //MEDIEVAL_ROGUELIKE_WEAPON_H