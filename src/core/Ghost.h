/**
 * @file Ghost.h
 * @author Alexandre PUILLET
 * @brief Module gérant les ennemis de type distance
 */

#include <iostream>
#include <vector>
#include "Game.h"
#include "Entity.h"
// #include "Projectile.h"

#ifndef MEDIEVALROGUELIKE_GHOST_H
#define MEDIEVALROGUELIKE_GHOST_H

class Game;
class Player;
/**
 * @brief Classe créant les ennemis distance.
 */
class Ghost : public Entity{
    public:
    Ghost();
    /**
     * @brief Constructeur d'un ennemi distance.
     * 
     * @param pos position de l'ennemi
     * @param force force de l'ennemi
     * @param health vie de l'ennemi
     * @param strenght puissance de l'ennemi
     */
    Ghost(Vector2D pos, Vector2D force, int health, int strenght, /*vector<Projectile> projectile*/
            std::string spriteNameIdle, std::string spriteNameLeft, std::string spriteNameRight);

    ~Ghost();

    /**
     * @brief Récupère les dégâts de l'ennemi.
     * 
     * @return int 
     */
    int getStrenght() const;

    bool checkHit(Player *player);

    /**
     * @brief Vole vers l'ennemi.
     * 
     * @param game 
     */
    void flyToPlayer(Player *player);

    /**
     * @brief Tire les projectiles.
     * @param game 
     */
    void fireProjectile();

    private:
    int strenght;
    /**
     * @brief initialisation du tableau de projectiles.
     */
    // vector<Projectile> projectile;
};

#endif //MEDIEVALROGUELIKE_GHOST_H