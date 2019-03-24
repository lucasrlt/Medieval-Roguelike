//
// Created by Lucas on 2019-03-18.
//
#include "TXTGame.h"
#include "Game.h"
#include <iostream>
#include "../core/TileMap.h"
using namespace std;
int main(int argc, char **arg)
{
    Game g;
    g.initDungeon();

    TXTLoop(g);
}
