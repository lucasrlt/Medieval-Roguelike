//
// Created by Lucas on 2019-03-18.
//
#include "SDLGame.h"

int main(int argc, char **arg)
{
    Game g;
    g.initDungeon();

    SDLGame sg;
    sg.SDLLoop(g);

    return 0;
}