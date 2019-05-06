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

class Savage;
class Ghost;
/**
 * @brief Classe s'occupant de créer le jeu.
 * C'est cette classe qui gère l'intéraction entre les modules. Une instance du jeu contient
 * une Tilemap avec la salle courante, ainsi que les différentes entités (ennemis et joueur). 
 * De plus, le jeu stocke tous les projectiles envoyés, et les actualise. 
 */
class Game
{
  public:
    /// @brief vrai si le joueur est mort
    bool playerDead;
    /// @brief vrai si la partie est gégnée
    bool hasWon;
    /// @brief vecteur contenant tous les projectiles présents dans le jeu.
    vector<Projectile> projectiles;
    /// @brief tableau 2D contenant toutes les salles du donjon.
    Room **dungeon;

    Game();
    ~Game();

  

    /**
     * @brief Initialisation du niveau, avec le personnage.
     */
    void initDungeon();

    Room &getConstRoom(int x, int y) const;
    int getCurrentRoomX() const;
    int getCurrentRoomY() const;
    const TileMap &getConstTilemap() const;
    Player *getConstPlayer() const;
    Savage *getConstSavage() const;
    Ghost *getConstGhost() const;
    Item *getConstItems() const;

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
     * @brief Détecte si le joueur est sur des pics, et renvoie vrai si c'est le cas
     */
    bool checkSpikes();


  private:
    /* === VARIABLES === */
    bool wasInitialized; // si vraie, alors une partie à déjà été lancée.
    Room currentRoom;
    int currRoomX, currRoomY;

    Player *player;
    Savage *savage; // chaque salle contient un fantôme, et parfois un sauvage, pas plus. idem pour l'item.
    Ghost *ghost;
    Item *item;

    TileMap *tilemap;
    DungeonGenerator dungeonGenerator;

    /* === FONCTIONS === */

    /**
     * @brief Tire les projectiles du joueur
     * 
     * @param right si vrai, tire à droite, sinon, tire à gauche
     */
    void playerShoot();

    /**
     * @brief Fait avancer les projectiles
     */
    void updateProjectiles();

    /**
     * @brief Gère les collisions des projectiles avec les ennemis
     */
    void checkProjectileHit();

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
     * @brief Fais apparaître un ennemi fantôme dans la salle.
     */
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
    void checkItemTaken();

    void regressionTest();
};

#endif //MEDIVALROGUELIKE_GAME_H
