/**
 * @brief Module gérant la création du jeu
 *
 * @author Alexandre PUILLET
 * @file Game.h
 */

#ifndef MEDIEVALROGUELIKE_GAME_H
#define MEDIEVALROGUELIKE_GAME_H

#include <iostream>
#include <vector>
#include "Room.h"
#include "DungeonGenerator.h"
#include "Vector2D.h"
#include "Savage.h"
#include "Ghost.h"
#include "Player.h"
#include "TileMap.h"
#include "Projectile.h"
#include "Item.h"

using namespace std;

const int PROJECTILE_OFFSET_X = 1;
const int PROJECTILE_OFFSET_Y = 1;
const float PROJECTILE_SPEED = 0.1f;
const int PROJECTILE_DAMAGES = 1;

/**
 * @brief Classe s'occupant de créer le jeu.
 */
class Savage;
class Ghost;
class Game
{
  public:
    bool playerDead, hasWon;

    vector<Projectile> projectiles;

    ~Game();

    Room *dungeon[MAZE_SIZE][MAZE_SIZE];

    /**
     * @brief Initialisation du niveau, avec le personnage.
     */
    void initDungeon();

    /**
     * @brief Récupère une salle.
     * @return Room.
     */
    Room &getConstRoom(int x, int y) const;
    int getCurrentRoomX() const;
    int getCurrentRoomY() const;

    const TileMap &getConstTilemap() const;

    /**
     * @brief Récupère un Player.
     *
     * @return Player
     */
    Player *getConstPlayer() const;

    /**
     * @brief Récupère un Savage.
     * 
     * @return Savage
     */
    Savage *getConstSavage() const;

    Ghost *getConstGhost() const;

    Item *getConstItems() const;

    void spawnGhost();
    void spawnSavage();
    void spawnRegenItem();

    void attackSword();
    void takeItem();

    /**
     * @brief Bouge le player.
     * 
     * @param move caractère indiquant la direction.
     */
    void keyboardActions(char action);

    void automaticActions(float dt);

    void refreshGhost();
    void checkRoomChange(char direction);
    void changeRoom(char direction);
    bool checkSpikes();
    void playerShoot(bool right);
    void updateProjectile();
    void projectileHitEnnemy();

  private:
    bool isJumping;
    bool isBossRoom;
    Room currentRoom;
    int currRoomX, currRoomY;

    Player *player;
    Savage *savage;
    Ghost *ghost;
    Item *item;

    TileMap *tilemap;
    DungeonGenerator dungeonGenerator;
};

#endif //MEDIVALROGUELIKE_GAME_H
