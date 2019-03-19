//
// Created by hadrien on 05/03/19.
//

#ifndef MEDIEVAL_ROGUELIKE_TILEMAP_H
#define MEDIEVAL_ROGUELIKE_TILEMAP_H
#include <string>
#include <vector>

using namespace std;

const int TILE_SIZE = 16;

const int GRID_SIZE = 16;        // largeur et hauteur d'une salle en nombre de tiles
const int LINES_BEFORE_GRID = 6; //

enum TileType
{
     collision,
     background,
     spike,
};

struct Tile
{
     unsigned int id;
     unsigned int posX, posY;
     TileType type;
};

/**
     @brief Classe qui récupère la couleur d'un sprite et la forme d'un tile
     */
class TileMap
{
   private:
     TileType getTypeForTile(unsigned int tileId);

   public:
     //Sprite[*] tiles;

     /**
         * @brief Récupère la salle depuis le fichier
         * @param filename : nom du fichier du tile
         * @param gridSize  : Taille d'une salle de tiles
         * @param linesBeforeGrid : Lignes de textes du fichier filename avant les tiles
         */
     void fetchRoomFromFile(const string &filename, Tile * [GRID_SIZE][GRID_SIZE]); //Room* out_room;
     //void drawTilesForRoom(Room& room, SDLMode& sdl);
     /** m
         * @brief Récupère les sprites des ids
         * @param files : tableau de vecteur string des sprites
         */
     void getSpriteNames(vector<string> &files);
};

#endif //MEDIEVAL_ROGUELIKE_TILEMAP_H
