#ifndef MEDIEVAL_ROGUELIKE_AGENT_H
#define MEDIEVAL_ROGUELIKE_AGENT_H

#include "Vector2D.h"
#include "TileMap.h"

/**
 * @brief Module gérant les entités du jeu.

 * @file Entity.h.h
 * @date 05/03/2019
 * @author Alexandre PUILLET
 */

const float MAX_GRAVITY = 8.0f;
const float JUMP_SPEED = 10.0f;
const float GRAVITY_SPEED = 20.0f;
const float PLAYER_SPEED = 4.0f;

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
     * @brief Initialisation d'un Agent avec une vie, une position, et une force.
     * @param position position de l'Agent.
     * @param force force de l'Agent.
     * @param health vie de l'Agent.
     */
    Entity(Vector2D position, Vector2D force, int health, std::string spriteNameIdle, std::string spriteNameLeft, std::string spriteNameRight);

    ~Entity();

    /**
     * @brief récupère la vie de l'entité.
     * @return health (entier).
     */
    int getHealth() const;

    Vector2D getForce() const;

    /**
     * @brief Change la vie du personnage en fonction des dégâts subits.
     * @param amount entier correspondant aux dégâts.
     */
    void receiveDamage(int amount);

    /**
     * @brief Ajoute le déplacement au personnage.
     * @param dep vecteur de déplacement.
     */
    void updatePosition(const TileMap &t, float dt);
    void jump();
    void move(Vector2D dep, const TileMap &t, float time);
    void moveLeft(const TileMap &t);
    void moveRight(const TileMap &t);

    /**
     * @brief Ajoute une force à la force du personnage.
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

#endif //MEDIEVAL_ROGUELIKE_AGENT_H