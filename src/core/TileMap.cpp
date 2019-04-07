//
// Created by hadrien on 05/03/19.
//

#include "TileMap.h"
#include "Room.h"
#include "Vector2D.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <assert.h>

using namespace std;

TileMap::~TileMap()
{
    deleteRoomMap();
}

void TileMap::deleteRoomMap()
{
    if (tilesetFile != "")
    {
        for (int i = 0; i < GRID_SIZE; i++)
        {
            for (int j = 0; j < GRID_SIZE; j++)
            {
                if (roomMap[i][j] != NULL)
                    delete roomMap[i][j];
            }
        }
    }
}

void TileMap::init(const string &tileset_file)
{
    tilesetFile = tileset_file;
    fetchTileTypes();
}

void TileMap::fetchTileTypes()
{
    ifstream readFile(tilesetFile.c_str());

    if (!readFile.is_open())
    {
        cerr << "FETCH_TILE_TYPES: erreur ouverture " << tilesetFile << endl;
        return;
    }

    string content;

    for (int k = 0; k < 3; k++)
        getline(readFile, content);

    for (int i = 0; i < NUM_TILES; i++)
        tileTypes[i] = background;

    while (!readFile.eof())
    {
        getline(readFile, content);
        if (content[1] != '/') // élimine </tileset>
        {
            // On fetch une ligne du type <tile id="2" type="block" />
            size_t idPos = content.find("id=\"") + 4;
            size_t typePos = content.find("type=\"");
            int tileId = stoi(content.substr(idPos, typePos - idPos - 2));

            size_t endPos = content.find("/") - 1;
            string tileType = content.substr(typePos + 6, endPos - typePos - 6);

            if (tileType == "block")
                tileTypes[tileId] = collision;
            else if (tileType == "background")
                tileTypes[tileId] = background;
            else if (tileType == "spike")
                tileTypes[tileId] = spike;
            else if (tileType == "spawn")
                tileTypes[tileId] = spawn;
            else if (tileType == "platform")
                tileTypes[tileId] = platform;
            else if (tileType == "spawn-monster")
                tileTypes[tileId] = spawnMonster;
        }
    }
}

void TileMap::fetchRoomFromFile(const string &filename)
{
    ifstream readFile(filename.c_str()); //Ouverture d'un flux pour lire le fichier voulu

    if (!readFile.is_open())
    { //En cas d'erreur de l'ouverture du fichier, envoie un message d'erreur et stop le programme
        cerr << "TILEMAP: Erreur dans l'ouverture en lecture du fichier." << endl;
        return;
    }

    if (readFile)
    {
        deleteRoomMap();
        string content;
        string beforeContent;

        for (int k = 0; k < LINES_BEFORE_GRID; k++) //Récupère les premières lignes inutiles
        {
            getline(readFile, beforeContent);
        }

        for (int y = 0; y < GRID_SIZE; y++) //Récupère les ids des tiles et les stocke dans un tableau 2D
        {
            for (int x = 0; x < GRID_SIZE; x++)
            {
                getline(readFile, content, ',');
                int tileId = stoi(content);

                TileType tileType = tileId == 0 ? background : tileTypes[tileId - 1];
                if (tileType == spawnMonster)
                {
                    enemySpawns.push_back({x, y});
                }
                int posX = ((tileId - 1) % TILE_SIZE) * TILE_SIZE;
                int posY = ((int)((tileId - 1) / TILE_SIZE)) * TILE_SIZE;
                Tile *tile = new Tile(tileId, posX, posY, tileType);

                if (tileType == spawn)
                {
                    playerSpawn.x = x;
                    playerSpawn.y = y;
                }

                roomMap[x][y] = tile;
            }
        }
        readFile.close(); //Ferme le flux
    }
}

bool TileMap::isValidPosition(const int x, const int y, bool goingUp) const
{
    // cout << x << " : " << y << endl;
    return (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && !(roomMap[x][y]->type == collision || (goingUp ? false : roomMap[x][y]->type == platform)));
}

const Tile &TileMap::getXY(unsigned int x, unsigned int y) const
{
    return *roomMap[x][y];
}

void TileMap::regressionTest()
{

    TileMap tm;

    tm.init("data/tileset.tsx");

    tm.fetchRoomFromFile("data/test_tilemap.tmx");

    assert(tm.roomMap[0][0]->id == 8 && tm.roomMap[0][0]->type == collision);
    cout << "Case [0][0] bonne" << endl;

    assert(tm.roomMap[1][0]->id == 116 && tm.roomMap[1][0]->type == background);
    cout << "Case [1][0] bonne" << endl;

    assert(tm.roomMap[2][0]->id == 195 && tm.roomMap[2][0]->type == spike);
    cout << "Case [2][0] bonne" << endl;

    assert(tm.roomMap[15][15]->id == 104 && tm.roomMap[15][15]->type == collision);
    cout << "Case [15][15] bonne" << endl;
}