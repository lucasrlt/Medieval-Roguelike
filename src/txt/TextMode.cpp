//
// Created by Lucas on 2019-03-14.
//

#include "TextMode.h"
#include <unistd.h>

#include "WinTXT.h"
#include "../TileMap.h"

void drawMap(Game &game, WinTXT &win)
{
    for (int y = 0; y < 40; y++)
    {
        for (int x = 0; x < 40; x++)
        {
            win.print(x, y, ' ');
        }
    }

    Room r;
    TileMap tm;
    for (int y = 0; y < MAZE_SIZE; y++)
    {
        for (int x = 0; x < MAZE_SIZE; x++)
        {
            r = game.getConstRoom(x, y);
            // cout << r.tilemapName << "     ";

            if (r.tilemapName != "")
            {
                int tiles[GRID_SIZE][GRID_SIZE];

                tm.fetchRoomFromFile("../data/tilemaps/" + r.tilemapName, tiles);
                // cout << "Oui - ";
                for (int j = 0; j < GRID_SIZE; j++)
                {
                    for (int i = 0; i < GRID_SIZE; i++)
                    {
                        win.print(y * GRID_SIZE + i, x * GRID_SIZE + j, tiles[i][j] > 0 ? 'X' : '.');
                    }
                }
            }
        }
        // cout << endl;
    }
}

void txtLoop(Game &game)
{
    WinTXT win(MAZE_SIZE * GRID_SIZE, MAZE_SIZE * GRID_SIZE);
    drawMap(game, win);
    bool ok = true;
    do
    {
        win.clear();
        drawMap(game, win);
        win.draw();
        usleep(1000000);

        // char c = win.getCh();
        // switch (c)i
        // {
        // case 't':
        //     ok = false;
        // }
    } while (ok);
}