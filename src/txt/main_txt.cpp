//
// Created by Lucas on 2019-03-18.
//
#include "TXTGame.h"

int main(int argc, char **arg)
{
    Game g;
    g.initDungeon();

    TXTLoop(g);
    return 0;
}