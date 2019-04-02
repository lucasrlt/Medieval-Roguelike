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

/**
 @brief Classe représentant les caractéristiques communes des entités du jeu.
 */
class Entity
{
  public:
    Vector2D position;

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
    void move(Vector2D dep, const TileMap &t);
    void moveLeft(const TileMap &t);
    void moveRight(const TileMap &t);
    void moveUp(const TileMap &t);
    void moveDown(const TileMap &t, char currDirection = ' ');

    /**
     * @brief Ajoute une force à la force du personnage.
     * @param _force vecteur de force.
     */
    void addForce(Vector2D _force);

    string getIdleSprite() const;

    string getLeftSprite() const;

    string getRightSprite() const;
    /**
     * @brief Affiche l'entité.
     */
    void show();

    /**
     * @brief Tests du module.
     */
    void regressionTest();

  protected:
    Vector2D force;
    int health;
    std::string idleSprite;
    std::string leftSprite;
    std::string rightSprite;
};

#endif //MEDIEVAL_ROGUELIKE_AGENT_H