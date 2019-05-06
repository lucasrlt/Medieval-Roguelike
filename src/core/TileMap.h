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
     

     void fetchTileTypes();
     void deleteRoomMap();

   public:
     Point playerSpawn;

     ~TileMap();
     vector<Point> enemySpawns;
     vector<Point> savageSpawns;
     vector<Point> itemSpawns;
     void init(const string &tilesetFile);

     const Tile &getXY(unsigned int x, unsigned int y) const;

     bool isValidPosition(const int x, const int y, bool goingUp = false) const;

     /**
         * @brief Récupère la salle depuis le fichier
         * @param filename : nom du fichier du tile
         */
     void fetchRoomFromFile(const string &filename); //Room* out_room;

     void regressionTest();
};

#endif //MEDIEVAL_ROGUELIKE_TILEMAP_H
