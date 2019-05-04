/**
 * @file Savage.h
 * @author Alexandre PUILLET
 * @brief Module gérant les ennemis de type mêlée
 */

#include <iostream>
#include <vector>
#include "Game.h"
#include "Entity.h"

#ifndef MEDIEVALROGUELIKE_SAVAGE_H
#define MEDIEVALROGUELIKE_SAVAGE_H

class Game;
class Player;

float const SAVAGE_SPEED = 2;
/**
 * @brief Classe créant les savage.
 */
class Savage : public Entity{
    public:
    Savage();
    /**
     * @brief Constructeur du savage.
     * 
     * @param pos position du savage
     * @param force force du savage
     * @param health vie du savage
     * @param strenght puissance du savage
     * @param isDeadCheck si le savage est mort
     * @param spriteNameIdle sprite de face
     * @param spriteNameLeft sprite gauche
     * @param spriteNameRight sprite droit
     */
    Savage(Vector2D posInit, Vector2D forceInit, int healthInit, int strenghtInit, bool isDeadCheck,
            std::string spriteNameIdle, std::string spriteNameLeft, std::string spriteNameRight);

    ~Savage();

    /**
     * @brief Récupère les dégâts du savage
     * 
     * @return int 
     */
    int getStrenght() const;

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
    int strenght;
};


#endif //MEDIEVALROGUELIKE_SAVAGE_H