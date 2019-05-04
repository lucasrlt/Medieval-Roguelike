#ifndef MEDIEVAL_ROGUELIKE_PLAYER_H
#define MEDIEVAL_ROGUELIKE_PLAYER_H

#include <string>
#include "Entity.h"
#include "Weapon.h"

/**
 * @brief Module gérant les caractéristiques d'un personnage
 * @file Player.h.h
 * @date 05/03/2019
 * @author Alexandre PUILLET
 */

const float MAX_JUMP_HEIGHT = 40;

/**
 * @brief Classe représentant les caractéristiques d'un personnage.
 */
class Game;
class Player : public Entity
{
  private:
    int energy;
    int shield;
    float currentJumpHeight;

  public:
    Weapon weapon;

    Player();

    /**
     * @brief Constructeur de Player
     * @param positionInit position du personnage.
     * @param forceInit force du personnage.
     * @param healthInit vie du personnage.
     * @param energyInit énergie du personnage.
     * @param shieldInit bouclier du personnage.
     * @param weaponInit arme du personnage.
     * @param spriteNameIdle sprite de face
     * @param spriteNameLeft sprite gauche
     * @param spriteNameRight sprite droit
     */
    Player(Vector2D positionInit, Vector2D forceInit, int healthInit, int energyInit, int shieldInit, 
            Weapon weaponInit, std::string spriteNameIdle, std::string spriteNameLeft, std::string spriteNameRight);

    ~Player();

    /**
     * @brief Récupère l'énerigie du player
     * 
     * @return int 
     */
    int getEnergy() const;

    /**
     * @brief Récupère le shield du player
     * 
     * @return int 
     */
    int getShield() const;

    /**
     * @brief Enlève des points de bouclier.
     * @param amount valeur à retirer aux points de bouclier.
     */
    // void receiveShieldDamage(int amount);

    /**
     * @brief Enlève de l'énergie.
     * @param amount valeur à retirer aux points d'énergie.
     */
    void loseEnergy(int amount);

    /**
     * @brief Récupère le player.
     */
    Player getPlayer();

    /**
     * @brief Augmente la vitesse du joueur pour le sprint
     * 
     */
    void sprint();

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
