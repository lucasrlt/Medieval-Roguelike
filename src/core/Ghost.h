/**
 * @file Ghost.h
 * @author Alexandre PUILLET
 * @brief Module gérant les ghosts de type distance
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
 * @brief Classe créant les ghosts distance.
 */
class Ghost : public Entity{
    public:
    vector<Projectile> projectiles;
    bool isBoss;
    
    Ghost();
    /**
     * @brief Constructeur du ghost.
     * 
     * @param pos position du ghost
     * @param force force du ghost
     * @param health vie du ghost
     * @param strenght puissance du ghost
     */
    Ghost(Vector2D pos, Vector2D force, int health, int strenght, bool isDead, std::string spriteNameIdle, 
            std::string spriteNameLeft, std::string spriteNameRight);

    ~Ghost();

    /**
     * @brief Récupère les dégâts du ghost.
     * 
     * @return int 
     */
    int getStrenght() const;

    /**
     * @brief Check si le joueur est dans la zone de contact du ghost (son sprite)
     * 
     * @param player joueur
     * @return true si le joueur est dans la zone de contact
     * @return false sinon
     */
    bool checkHit(Player *player);

    /**
     * @brief Déplacement du ghost vers le joueur
     * 
     * @param player joueur
     */
    void flyToPlayer(Player *player);

    /**
     * @brief Tire les projectile du ghost
     * 
     * @param player joueur
     */
    void fireProjectile(Player *player);

    private:
    int strenght;   
};

#endif //MEDIEVALROGUELIKE_GHOST_H