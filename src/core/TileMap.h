//
// Created by hadrien on 05/03/19.
//

#ifndef MEDIEVAL_ROGUELIKE_TILEMAP_H
#define MEDIEVAL_ROGUELIKE_TILEMAP_H
#include <string>
#include <vector>
#include "Vector2D.h"

using namespace std;

const int TILE_SIZE = 16;

const int GRID_SIZE = 16; // largeur et hauteur d'une salle en nombre de tiles
const int NUM_TILES = TILE_SIZE * GRID_SIZE;
const int LINES_BEFORE_GRID = 5;

enum TileType  // Tous les blocks existants dans la création d'une tilemap
{
     platform,
     collision,
     spike,
     background,
     spawn,
     spawnMonster,
     spawnMonsterSavage,
     regenItem
};

/**
 * @brief structure contenant les paramètres d'une tile
 */
struct Tile
{
     /// @brief id de la tile dans le tileset
     int id;
     /// @brief Position de la tile dans l'affichage
     int posX, posY;
     /// @brief type de tile, utile pour les collisions
     TileType type;
     

     Tile(int _id, int _posX, int _posY, TileType _type) : id(_id), posX(_posX), posY(_posY), type(_type) {}
};

/**
 @brief Classe gérant la TileMap. Une tilemap est un tableau de tiles qui provient d'un fichier .tmx 
 * créé avec le logiciel Tiled.  Les tiles sont des images carrées que l'on assemble pour créer des niveaux.
 * Ce module gére la récupération et le traitement de TileMaps depuis un fichier .tmx pour gérer les niveaux dans le jeu.
 */
class TileMap
{
   private:
     string tilesetFile;
     Tile *roomMap[GRID_SIZE][GRID_SIZE];
     TileType tileTypes[NUM_TILES];
     
     /**
      * @brief Récupère les types de tous les blocs du tileset.
     */
     void fetchTileTypes();
     
     /**
     * @brief Supprime un donjon de la mémoire.
     * 
     */

     void deleteRoomMap();

   public:
     Point playerSpawn; /// @brief  Position du spawn du joueur.

     ~TileMap();
     vector<Point> enemySpawns; /// @brief Vector de positions de spawns de ghosts.
     vector<Point> savageSpawns; /// @brief Vector de positions de spawns de savages.
     vector<Point> itemSpawns; /// @brief Vector de positions de spawns d'items.

     /**
         * @brief Récupère les types de tous les blocs du tileset passé en paramètre par la fonction fetchTileTypes().
         * @param tilesetFile : nom du fichier tileset contenant nos blocs.
     */
     void init(const string &tilesetFile);

     /**
     * @brief Récupère le tile de positions X et Y d'un tile.
     *
     * @param x,y coordonnées d'un tile.
     * @return *roomMap[x][y].
     */
     const Tile &getXY(unsigned int x, unsigned int y) const;

     /**
     * @brief Vérifie si la position de coordonnées x,y est une position dans l'écran, hors d'un bloc de collision.
     *
     * @param x,y coordonnées que l'on va vérifier.
     * @param goingUp booléen pour la gestion des plateformes.
     * 
     * @return true si les coordonnées sont bien dans la fenêtre et hors d'un bloc de collision.
     */

     bool isValidPosition(const int x, const int y, bool goingUp = false) const;

     /**
         * @brief Récupère la grille d'id a partir du fichier en paramètre.
         * @brief Ajoute des joueurs/ennemis dans les vector.
         * @param filename : nom du fichier du tile
         */
     void fetchRoomFromFile(const string &filename);

     /// @brief Test de regression de la classe TileMap.
     void regressionTest();
};

#endif //MEDIEVAL_ROGUELIKE_TILEMAP_H
