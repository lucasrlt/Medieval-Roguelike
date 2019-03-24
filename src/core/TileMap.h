//
// Created by hadrien on 05/03/19.
//

#ifndef MEDIEVAL_ROGUELIKE_TILEMAP_H
#define MEDIEVAL_ROGUELIKE_TILEMAP_H
#include <string>
#include <vector>

using namespace std;

const int TILE_SIZE = 16;

const int GRID_SIZE = 16; // largeur et hauteur d'une salle en nombre de tiles
const int NUM_TILES = TILE_SIZE * GRID_SIZE;
const int LINES_BEFORE_GRID = 5;

enum TileType
{
     collision,
     spike,
     background,
};
//
struct Tile
{
     int id;
     int posX, posY;
     TileType type;

     Tile(int _id, int _posX, int _posY, TileType _type) : id(_id), posX(_posX), posY(_posY), type(_type) {}
};

/**
     @brief Classe qui récupère la couleur d'un sprite et la forme d'un tile
     */
class TileMap
{
   private:
     string tilesetFile;
     Tile *roomMap[GRID_SIZE][GRID_SIZE];
     TileType tileTypes[NUM_TILES];

     void fetchTileTypes();

   public:
     void init(const string &tilesetFile);
     const Tile &getXY(unsigned int x, unsigned int y) const;

     bool isValidPosition(const int x, const int y) const;

     /**
         * @brief Récupère la salle depuis le fichier
         * @param filename : nom du fichier du tile
         * @param gridSize  : Taille d'une salle de tiles
         * @param linesBeforeGrid : Lignes de textes du fichier filename avant les tiles
         */
     void fetchRoomFromFile(const string &filename); //Room* out_room;
};

#endif //MEDIEVAL_ROGUELIKE_TILEMAP_H
