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

    // for (int y = 0; y < GRID_SIZE; y++)
    // {
    //     for (int x = 0; x < GRID_SIZE; x++)
    //     {
    //         cout << tm[x][y]->id << "   ";
    //     }
    //     cout << endl;
    // }

    // for (int y = 0; y < GRID_SIZE; y++)
    // {
    //     for (int x = 0; x < GRID_SIZE; x++)
    //     {
    //         delete tm[x][y];
    //     }
    // }
    cout << "ouiii" << endl;
    TXTLoop(g);
}
