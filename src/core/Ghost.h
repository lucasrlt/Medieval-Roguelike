
#ifndef MEDIEVALROGUELIKE_GHOST_H
#define MEDIEVALROGUELIKE_GHOST_H

#include <iostream>
#include <vector>
#include "Game.h"
#include "Entity.h"
#include "Projectile.h"

/**
 * @brief Module gérant les ghosts de type distance
 * 
 * @file Ghost.h
 * @author Alexandre PUILLET
 */

float const GHOST_SPEED = 0.03f;

class Game;
class Player;

/**
 * @brief Classe gérant les fantômes. Les fantômes sont des ennemis qui volent et traversent
 * les murss. Ils sont par contre fragiles et font peu de dégâts.
 * 
 * @note Un fantôme peut être un boss. Son sprite, sa vie et sa taille changeront en conséquence.
 */
class Ghost : public Entity {
public:
    bool isBoss;
    
    Ghost();
    /**
     * @brief Constructeur du ghost.
     * 
     * @param pos position du ghost
     * @param force force du ghost
     * @param health vie du ghost
     * @param strenght puissance du ghost
     * @param isDead vrai si le fantôme est mort
     */
    Ghost(Vector2D pos, Vector2D force, int health, int strenght, bool isDead);
    ~Ghost();

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
    int strength;   
};

#endif //MEDIEVALROGUELIKE_GHOST_H