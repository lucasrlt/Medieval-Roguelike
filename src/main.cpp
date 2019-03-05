#include <iostream>
#include "LevelGenerator.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    LevelGenerator lg;
    lg.fetchRooms("../data/tilemaps");

    return 0;
}