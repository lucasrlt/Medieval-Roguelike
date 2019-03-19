//
// Created by Lucas on 2019-03-18.
//
#include "TXTGame.h"
#include "Game.h"

int main(int argc, char **arg)
{
    Game g;
    g.initDungeon();

    TXTLoop(g);
}