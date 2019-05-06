#ifndef MEDIEVAL_ROGUELIKE_PLAYER_H
#define MEDIEVAL_ROGUELIKE_PLAYER_H

#include <string>
#include "Entity.h"
#include "Weapon.h"

/**
 * @brief Module gérant les caractéristiques d'un personnage
 * @file Player.h
 * @date 05/03/2019
 * @author Alexandre PUILLET
 */

const float MAX_JUMP_HEIGHT = 40;

class Game;
/**
 * @brief Classe représentant les caractéristiques d'un personnage.
 */
class Player : public Entity
{
  private:
    Weapon weapon;
    
    bool isRunning;
    int energy;
    int shield;
    float currentJumpHeight;

  public:

    Player();

    /**
     * @brief Constructeur de Player
     * @param positionInit position du personnage.
     * @param forceInit force du personnage.
     * @param healthInit vie du personnage.
     * @param energyInit énergie du personnage.
     * @param weaponInit arme du personnage.
     */
    Player(Vector2D positionInit, Vector2D forceInit, int healthInit, int energyInit, Weapon weaponInit);

    ~Player();

    int getEnergy() const;
    const Weapon& getWeapon() const;

    /**
     * @brief Enlève de l'énergie.
     * @param amount valeur à retirer aux points d'énergie.
     */
    void loseEnergy(int amount);

    /**
     * @brief Augmente la vitesse du joueur pour le sprint
     * 
     */
    void sprint();

    /**
     * @brief Tests du module.
     */
    void regressionTest();
};

#endif //MEDIEVAL_ROGUELIKE_PLAYER_H
