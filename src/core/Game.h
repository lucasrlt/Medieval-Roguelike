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
const int SPIKES_DAMAGES = 1;

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

    Game();
    ~Game();

    Room **dungeon;

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

    /**
     * @brief Attaque du personnage avec l'épée
     */
    void attackSword();

    /**
     * @brief Si le personnage est sur un item, le ramasse
     * 
     */
    void takeItem();


    /**
     * @brief Fais une action sur le player en fonction des touches appuyées désignées dans la SDL
     * @param action action désignée par la SDL
     */
    void keyboardActions(char action);

    /**
     * @brief Gère les actions automatiques du jeu, à savoir
     * les tirs de projectile, le déplacement du ghost et du savage,
     * si le joueur est mort, si l'item de régénération est pris,
     * ou quand le joueur change de salle.
     * 
     * @param dt intervalle de temps entre 2 updates
     */
    void automaticActions(float dt);

    /**
     * @brief Vérifie si le joueur est sur un bord de map, et appelle changeRoom en fonction de direction
     * 
     * @param direction direction du joueur
     */
    void checkRoomChange(char direction);

    /**
     * @brief change la salle en fonction de la position du joueur dans la map (s'il est à gauche, à droite, en haut ou en bas)
     * 
     * @param direction direction du joueur
     */
    void changeRoom(char direction);

    /**
     * @brief Détecte si le joueur est sur des pics, et renvoie vrai si c'est le cas
     */
    bool checkSpikes();

    /**
     * @brief Tire les projectiles du joueur
     * 
     * @param right si vrai, tire à droite, sinon, tire à gauche
     */
    void playerShoot(bool right);

    /**
     * @brief Fait avancer le projectile
     */
    void updateProjectile();

    /**
     * @brief Gère les collisions des projectiles sur les ennemis
     */
    void projectileHitEnnemy();

  private:
    bool isJumping;
    bool wasInitialized;
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
