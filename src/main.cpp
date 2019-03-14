#include <iostream>
#include <string.h>
#include "Game.h"

using namespace std;

int main() {
    Game g;
    g.initDungeon();

    cout<<g.getConstRoom(5, 3).tilemapName<<endl;

    return 0;
}