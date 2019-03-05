#include <iostream>
#include "TileMap.h"
#include "LevelGenerator.h"
int main() {
    std::cout << "Hello, World!" << std::endl;

    LevelGenerator lg;
    lg.fetchRooms("../data/tilemaps");

    TileMap tabRead;
    tabRead.fetchRoomFromFile("/data/tilemaps/B.tmx");
    return 0;
}