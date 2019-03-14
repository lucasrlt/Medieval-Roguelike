//
// Created by hadrien on 05/03/19.
//

#ifndef MEDIEVAL_ROGUELIKE_TILEMAP_H
#define MEDIEVAL_ROGUELIKE_TILEMAP_H
#include <string>
#include <vector>

using namespace std;

const int TILES_WIDTH = 32;
const int TILES_HEIGHT = 32;

const int GRID_SIZE = 8;         // largeur et hauteur d'une salle en nombre de tiles
const int LINES_BEFORE_GRID = 6; //

/**
     @brief Classe qui récupère la couleur d'un sprite et la forme d'un tile
     */
class TileMap
{
  public:
    //Sprite[*] tiles;

    /**
         * @brief Récupère la salle depuis le fichier
         * @param filename : nom du fichier du tile
         * @param gridSize  : Taille d'une salle de tiles
         * @param linesBeforeGrid : Lignes de textes du fichier filename avant les tiles
         */
    void fetchRoomFromFile(const string &filename, int tabTiles[GRID_SIZE][GRID_SIZE]); //Room* out_room;
    //void drawTilesForRoom(Room& room, SDLMode& sdl);
    /**
         * @brief Récupère les sprites des ids
         * @param files : tableau de vecteur string des sprites
         */
    void getSpriteNames(vector<string> &files);
};

#endif //MEDIEVAL_ROGUELIKE_TILEMAP_H
