#ifndef MEDIEVALROGUELIKE_SAVAGE_H
#define MEDIEVALROGUELIKE_SAVAGE_H


#include <iostream>
#include <vector>
#include "Game.h"
#include "Entity.h"

/**
 * @file Savage.h
 * @author Alexandre PUILLET
 * @brief Module gérant les ennemis de type mêlée
 */

float const SAVAGE_SPEED = 2.0f;

class Game;
class Player;

/**
 * @brief Classe gérant un sauvage.
 * Un sauvage est un ennemi plus puissant qu'un fantôme (plus de vie et plus de dégâts), 
 * mais il ne peut pas voler. Il reste donc au sol et est très vulnéravble aux obstacles..
 */
class Savage : public Entity {
public:
    Savage();
    /**
     * @brief Constructeur du savage.
     * 
     * @param posInit position du savage
     * @param velocityInit force du savage
     * @param healthInit vie du savage
     * @param strengthInit puissance du savage
     * @param isDeadCheck si le savage est mort
     */
    Savage(Vector2D posInit, Vector2D velocityInit, int healthInit, int strengthInit, bool isDeadCheck);
    ~Savage();

    /**
     * @brief Fait avancer le savage vers le player
     * 
     * @param player joueur
     * @param t tilemap en cours
     * @param dt intervalle de temps entre 2 updates
     */
    void runToPlayer(Player *player,const TileMap &t,float dt);

    /**
     * @brief Check si le player est dans la zone de contact du savage (son sprite)
     * 
     * @param player joueur
     * @return true si le joueur prend des dégâts
     * @return false sinon
     */
    bool checkHit(Player *player);

private:
    int strength;
};


#endif //MEDIEVALROGUELIKE_SAVAGE_H