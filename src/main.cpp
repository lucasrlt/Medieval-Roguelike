#include <iostream>
#include <string>
#include "TileMap.h"
//#include "LevelGenerator.h"
int main() {

    //LevelGenerator lg;
    //lg.fetchRooms("../data/tilemaps");

    TileMap tabRead;
    tabRead.fetchRoomFromFile("../data/tilemaps/B.tmx");
    return 0;
}