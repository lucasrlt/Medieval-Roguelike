/**
 * @file Savage.h
 * @author Alexandre PUILLET
 * @brief Module gérant les ennemis de type mêlée
 */

#include <iostream>
#include "Entity.h"
#include "Game.h"

#ifndef MEDIEVALROGUELIKE_SAVAGE_H
#define MEDIEVALROGUELIKE_SAVAGE_H

/**
 * @brief Classe créant les ennemis de mêlée.
 */

class Savage : public Entity{
    public:
    Savage();

    /**
     * @brief Constructeur d'un ennemi de mêlée.
     * 
     * @param pos position de l'ennemi
     * @param force force de l'ennemi
     * @param health vie de l'ennemi
     * @param strenght puissance de l'ennemi
     */
    Savage(Vector2D pos, Vector2D force, int health, int strenght);

    ~Savage();

    /**
     * @brief Récupère les dégâts de l'ennemi
     * 
     * @return int 
     */
    int getStrenght() const;

    /**
     * @brief Fait avanancer le Savage vers le personnage.
     * 
     * @param game 
     */
    void runToPlayer(Game &game);

    /**
     * @brief 
     * 
     * @param game 
     */
    void attackPlayer(Game &game);

    private:
    int strenght;
};


#endif //MEDIEVALROGUELIKE_SAVAGE_H