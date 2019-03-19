#include <iostream>
#include <string.h>
#include "DungeonGenerator.h"
#include "../sdl2/SDLGame.h"
#include "Game.h"
#include "../txt/TXTGame.h"
#include <cstdlib>

int main(int argc, char **arg)
{
    SDLGame sg;
    sg.SDLLoop();

    return 0;
}