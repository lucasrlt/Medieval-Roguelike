//
// Created by Lucas on 2019-03-14.
//

#include "TXTGame.h"
#include <chrono>
#include <ctime>
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
            else
            {
                win.print(x, y, 'X');
            }
        }
    }

    const Ghost *gh = g.getConstGhost();
    if (!gh->isDead)
        win.print((int)gh->getPosition().x, (int)gh->getPosition().y, 'G');

    const Savage *s = g.getConstSavage();
    if (s != nullptr && !s->isDead)
        win.print((int)s->getPosition().x, (int)s->getPosition().y, 'S');


    const Player *p = g.getConstPlayer();
    win.print((int)p->getPosition().x, (int)p->getPosition().y, 'P');


    string health = "Vie: " + to_string(p->getHealth());
    string energy = "Energie: " + to_string(p->getEnergy());
    
    string ghost_health = "Vie ghost: " + to_string(g.getConstGhost()->getHealth());

    if (g.getConstSavage() != nullptr) {
        string savage_health = "Vie sauvage: " + to_string(g.getConstGhost()->getHealth());
        win.print(0, 20, savage_health.c_str());
    }

    win.print(0, 17, health.c_str());
    win.print(0, 18, energy.c_str());
    win.print(0, 19, ghost_health.c_str());
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

    bool r = false, l = false;

    Player *p = g.getConstPlayer();

    auto now = std::chrono::system_clock::now();
    // Some computation here
    auto lastHit = std::chrono::system_clock::now();

    do
    {
        now = std::chrono::system_clock::now();

        char c = win.getCh();
        switch (c)
        {
        case 't': // stop
            ok = false;
            break;
        case 'i': // jump
            g.keyboardActions('j');
            break;
        case 'l': // droite
            if (l) { g.keyboardActions('r'); }
            if (!r) {
                g.keyboardActions('r');
                r = true;
                l = false;
            }
            break;
        case 'j': // gauche
            if (r) { g.keyboardActions('l'); }
            if (!l) {
                g.keyboardActions('l');
                r = false;
                l = true;
            }
            break;
        case 'm': // map
            showMap = !showMap;
            break;
        case 'h':
            g.keyboardActions('h');
            break;
        case 'f':
            g.keyboardActions('e');
            break;
        }

        g.automaticActions(0.002f); 

        std::chrono::duration<double> elapsed_seconds = now - lastHit;
        // cout << elapsed_seconds.count();
        // if (now - lastH)
        
        if (elapsed_seconds.count() >= 0.5) {
            if (g.checkSpikes() || g.getConstGhost()->checkHit(p) || (g.getConstSavage() != nullptr && g.getConstSavage()->checkHit(p))) {
                lastHit = std::chrono::system_clock::now();
            }
        }

        win.clear();
        if (showMap)
            drawMap(g, win);
        else
            drawRoom(g, win);

        win.draw();

        usleep(1000);
    } while (ok && !g.playerDead);

    cout << "Vous êtes mort." << endl;
}