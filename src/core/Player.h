#ifndef MEDIEVAL_ROGUELIKE_PLAYER_H
#define MEDIEVAL_ROGUELIKE_PLAYER_H

#include <string>
#include "Entity.h"
#include "Weapon.h"
//#include "Item.h"

/**
 * @brief Module gérant les caractéristiques d'un personnage
 * @file Player.h.h
 * @date 05/03/2019
 * @author Alexandre PUILLET
 */

/**
 * @brief Classe représentant les caractéristiques d'un personnage.
 */

const float MAX_JUMP_HEIGHT = 40;

class Player : public Entity
{
  private:
    int energy;
    int shield;
    float currentJumpHeight;

  public:
    Weapon weapon;
    std::string spriteName;

    Player();

    /**
     * @brief Constructeur de Player avec des valeurs.
     * @param positionInit position du personnage.
     * @param forceInit force du personnage.
     * @param healthInit vie du personnage.
     * @param energyInit énergie du personnage.
     * @param shieldInit bouclier du personnage.
     * @param weaponInit arme du personnage.
     * @param name nom du personnage.
     */
    Player(Vector2D positionInit, Vector2D forceInit, int healthInit, int energyInit, int shieldInit, Weapon weaponInit, std::string name);

    ~Player();

    int getEnergy() const;
    int getShield() const;

    /**
     * @brief Enlève des points de bouclier.
     * @param amount valeur à retirer aux points de bouclier.
     */
    void receiveShieldDamage(int amount);

    /**
     * @brief Enlève de l'énergie.
     * @param amount valeur à retirer aux points d'énergie.
     */
    void loseEnergy(int amount);

    /**
     * @brief Attaque l'entité.
     * @param e entité.
     */
    void attack(Entity &e);

    /**
     * @brief Récupère le player.
     */
    Player getPlayer();

    /**
     * @brief Affiche les caractéristiques du personnage.
     */
    void show();

    /**
     * @brief Tests du module.
     */
    void regressionTest();

    // bool jump(const TileMap &t);
};

#endif //MEDIEVAL_ROGUELIKE_PLAYER_H
