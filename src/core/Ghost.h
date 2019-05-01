/**
 * @file Ghost.h
 * @author Alexandre PUILLET
 * @brief Module gérant les ennemis de type distance
 */

#include <iostream>
#include <vector>
#include "Game.h"
#include "Entity.h"
#include "Projectile.h"

#ifndef MEDIEVALROGUELIKE_GHOST_H
#define MEDIEVALROGUELIKE_GHOST_H

float const GHOST_SPEED = 0.03f;

class Game;
class Player;
/**
 * @brief Classe créant les ennemis distance.
 */
class Ghost : public Entity{
    public:
    vector<Projectile> projectiles;
    bool isBoss;
    
    Ghost();
    /**
     * @brief Constructeur d'un ennemi distance.
     * 
     * @param pos position de l'ennemi
     * @param force force de l'ennemi
     * @param health vie de l'ennemi
     * @param strenght puissance de l'ennemi
     */
    Ghost(Vector2D pos, Vector2D force, int health, int strenght, bool isDead, std::string spriteNameIdle, 
            std::string spriteNameLeft, std::string spriteNameRight);

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
    void fireProjectile(Player *player);

    private:
    int strenght;   
};

#endif //MEDIEVALROGUELIKE_GHOST_H