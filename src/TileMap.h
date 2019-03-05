//
// Created by hadrien on 05/03/19.
//

#ifndef MEDIEVAL_ROGUELIKE_TILEMAP_H
#define MEDIEVAL_ROGUELIKE_TILEMAP_H
#include <string>
/**
     @brief Création de la classe TileMap qui permet de créer une pièce du labyrinthe sur la map
     */

class TileMap {
    /**
     @brief Création d'une pièce, avec TILES_WIDTH = largeur du tile et TILES_HEIGHT = hauteur du tile
     */
    public :
        const int TILES_WIDTH = 32;
        const int TILES_HEIGHT = 32;
        //Sprite[*] tiles;

        //TileMap();
        void fetchRoomFromFile(string filename); //Room* out_room);
        //drawTilesForRoom(Room& room, SDLMode& sdl);
};


#endif //MEDIEVAL_ROGUELIKE_TILEMAP_H
