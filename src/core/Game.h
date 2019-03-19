/**
 * @brief Module gérant la création du jeu
 *
 * @author Alexandre PUILLET
 * @file Game.h
 */

#ifndef MEDIEVALROGUELIKE_GAME_H
#define MEDIEVALROGUELIKE_GAME_H

#include <iostream>
#include "Room.h"
#include "DungeonGenerator.h"
#include "Vector2D.h"
#include "Player.h"
#include "TileMap.h"

using namespace std;

/**
 * @brief Classe s'occupant de créer le jeu.
 */

class Game
{
  public:
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
    Room &getConstRoom(int x, int y);

    const TileMap &getConstTilemap() const;

    /**
     * @brief Récupère un Player.
     *
     * @return Player
     */
    Player *getConstPlayer();

    /**
     * @brief Bouge le player.
     * 
     * @param move caractère indiquant la direction.
     */
    void movePlayer(char move);

    void jump();

  private:
    Room currentRoom;
    Player *player;
    TileMap tilemap;
    DungeonGenerator dungeonGenerator;
};

#endif //MEDIVALROGUELIKE_GAME_H
