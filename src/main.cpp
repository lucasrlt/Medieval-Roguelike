#include <iostream>
#include "TileMap.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    TileMap * tabRead = NULL;
    fetchRoomFromFile("/data/tilemaps/B.tmx");
    delete[] tabRead;
    return 0;
}