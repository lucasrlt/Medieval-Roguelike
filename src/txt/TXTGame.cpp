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
            else if (tile.type == spike)
            {
                win.print(x, y, '^');
            }
            else if (tile.type == spawnMonster)
            {
                win.print(x, y, 'E');
            }
            else
            {
                win.print(x, y, 'X');
            }
        }
    }

    const Player *p = g.getConstPlayer();
    win.print((int)p->position.x, (int)p->position.y, 'P');

    string health = "Vie: " + to_string(p->getHealth());
    string energy = "Energie: " + to_string(p->getEnergy());
    string shield = "Bouclier: " + to_string(p->getShield());

    win.print(0, 17, health.c_str());
    win.print(0, 18, energy.c_str());
    win.print(0, 19, shield.c_str());
}

void drawMap(const Game &g, WinTXT &win)
{
    int roomSize = 3;
    for (int y = 0; y < MAZE_SIZE; y++)
    {
        for (int x = 0; x < MAZE_SIZE; x++)
        {
            Room r = g.dungeon[x][y];

            if (r.tilemapName != "")
            {
                for (int j = 0; j < roomSize; j++)
                {
                    for (int i = 0; i < roomSize; i++)
                    {

                        if (j != 1 || i != 1)
                        {
                            char c = x == g.getCurrentRoomX() && y == g.getCurrentRoomY() ? '*' : 'X';
                            win.print(x * roomSize + i, y * roomSize + j, c);
                        }
                        else
                        {
                            char c = x == g.getCurrentRoomX() && y == g.getCurrentRoomY() ? 'P' : '.';
                            win.print(x * roomSize + i, y * roomSize + j, c);
                        }
                    }
                }

                if (r.schema.openBottom)
                    win.print(x * roomSize + 1, y * roomSize + 2, '.');
                if (r.schema.openTop)
                    win.print(x * roomSize + 1, y * roomSize, '.');
                if (r.schema.openLeft)
                    win.print(x * roomSize, y * roomSize + 1, '.');
                if (r.schema.openRight)
                    win.print(x * roomSize + 2, y * roomSize + 1, '.');
            }
        }
    }
}

void TXTLoop(Game &g)
{
    WinTXT win(20, 20);
    system("clear");
    bool ok = true;
    bool showMap = false;

    do
    {
        win.clear();
        if (showMap)
            drawMap(g, win);
        else
            drawRoom(g, win);

        win.draw();
        // sleep(1);
        usleep(1000);

        char c = win.getCh();
        switch (c)
        {
        case 't':
            ok = false;
            break;
        case 'j':
        cout << "hey." << endl;
            g.keyboardActions('l');
            break;
        case 'l':
            g.keyboardActions('r');
            break;
        case 'i':
            g.keyboardActions('t');
            break;
        case 'm':
            showMap = !showMap;
        }
        g.automaticActions(1);
        g.getConstPlayer()->updatePosition(g.getConstTilemap(), 1);
        // cout << endl;

    } while (ok);
}