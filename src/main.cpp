#include <iostream>
#include <string>
#include <vector>
#include "TileMap.h"
//#include "LevelGenerator.h"
int main() {

    //LevelGenerator lg;
    //lg.fetchRooms("../data/tilemaps");

    TileMap tabRead;
    vector<string> fetchSprite;
    tabRead.fetchRoomFromFile("../data/tilemaps/B.tmx");
    tabRead.getSpriteNames(fetchSprite);
    for(auto it = fetchSprite.begin(); it != fetchSprite.end(); ++it)
    {
        cout << *it << endl;
    }

    return 0;
}