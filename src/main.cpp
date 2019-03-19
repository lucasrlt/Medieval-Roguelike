#include <iostream>
#include <string.h>
#include "DungeonGenerator.h"
#include "SDLGame.h"
#include "Game.h"

int main(int argc, char **arg)
{
    SDLGame sg;
    sg.SDLLoop();

    Game g;
    g.initDungeon();

    return 0;
}