#ifndef MEDIEVAL_ROGUELIKE_ENTITY_H
#define MEDIEVAL_ROGUELIKE_ENTITY_H

#include "Vector2D.h"
#include "TileMap.h"

/**
 * @brief Module gérant les entités du jeu.

 * @file Entity.h
 * @date 05/03/2019
 * @author Alexandre PUILLET
 */

const float MAX_GRAVITY = 8.0f;
const float JUMP_SPEED = 10.0f;
const float GRAVITY_SPEED = 20.0f;
const float PLAYER_SPEED = 4.0f;
const int MAX_HEALTH = 10;

/**
 @brief Classe représentant les caractéristiques communes des entités du jeu.
 */
class Entity
{
  public:
    bool movingRight, movingLeft, movingUp, movingBottom;
    bool isDead;
    
    Vector2D position;

    std::string idleSprite;
    std::string leftSprite;
    std::string rightSprite;

    Entity();

    /**
     * @brief Initialisation de l'entité avec une vie, une position, et une force.
     * @param position position de l'entité.
     * @param force force de l'entité.
     * @param health vie de l'entité.
     * @param spriteName.. sprites de l'entité.
     */
    Entity(Vector2D position, Vector2D force, int health, std::string spriteNameIdle, std::string spriteNameLeft, std::string spriteNameRight);

    ~Entity();

    /**
     * @brief récupère la vie de l'entité.
     * @return health (entier).
     */
    int getHealth() const;

    /**
     * @brief Récupère la vie de l'entité
     * @return Vector2D 
     */
    Vector2D getForce() const;

    /**
     * @brief Dégâts reçus par l'entité.
     * @param amount entier correspondant aux dégâts.
     */
    void receiveDamage(int amount);

    /**
     * @brief Ajoute le déplacement de l'entité.
     * @param dep vecteur de déplacement.
     */

    void updatePosition(const TileMap &t, float dt);
    /**
     * @brief Fait sauter l'entité.
     */
    void jump();
    void move(Vector2D dep, const TileMap &t, float time);

    /**
     * @brief Déplace le joueur à gauche
     */
    void moveLeft(const TileMap &t);
    void moveRight(const TileMap &t);

    /**
     * @brief Ajoute une force à la force de l'entité.
     * @param _force vecteur de force.
     */
    void addForce(Vector2D _force);
    /**
     * @brief Affiche l'entité.
     */
    void show();
    
    bool isGoingRight();

    /**
     * @brief Tests du module.
     */
    void regressionTest();


  protected:
    Vector2D velocity;
    int health;
    bool grounded;
};

#endif //MEDIEVAL_ROGUELIKE_ENTITY_H