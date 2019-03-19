//
// Created by Lucas on 2019-03-14.
//

#include "TXTGame.h"
#include <unistd.h>

#include "WinTXT.h"
#include "../core/TileMap.h"

void drawRoom(const Game &g, WinTXT &win)
{
    const TileMap &tilemap = g.getConstTilemap();

    for (int y = 0; y < GRID_SIZE; y++)
    {
        for (int x = 0; x < GRID_SIZE; x++)
        {
            const Tile &tile = tilemap.getXY(x, y);
            if (tile.id == 0 || tile.type == background)
            {
                win.print(x, y, '.');
            }
            else
            {
                win.print(x, y, 'X');
            }
        }
    }
}

void TXTLoop(Game &g)
{
    WinTXT win(MAZE_SIZE * GRID_SIZE, MAZE_SIZE * GRID_SIZE);
    bool ok = true;
    do
    {
        win.clear();
        drawRoom(g, win);
        win.draw();
        usleep(10000);

        char c = win.getCh();
        switch (c)
        {
        case 't':
            ok = false;
        }
    } while (ok);
}