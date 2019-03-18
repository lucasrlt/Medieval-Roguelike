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

using namespace std;

/**
 * @brief Classe s'occupant de créer le jeu.
 */

class Game{
  public:
    ~Game();

    Room dungeon[MAZE_SIZE][MAZE_SIZE];
    DungeonGenerator dungeonGenerator;

    /**
     * @brief Initialisation du niveau, avec le personnage.
     */
    void initDungeon();

    /**
     * @brief Récupère une salle.
     * @return Room.
     */
    Room getConstRoom(int x, int y);

    /**
     * @brief Récupère un Player.
     * 
     * @return Player 
     */
    Player getConstPlayer();

  private:
    Room currentRoom;
    Player* player;
};

#endif //MEDIVALROGUELIKE_GAME_H