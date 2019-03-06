//
// Created by hadrien on 05/03/19.
//

#include "TileMap.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void TileMap::fetchRoomFromFile(const string& filename,int gridSize, int linesBeforeGrid)
{
    ifstream readFile(filename.c_str());
    if (!readFile.is_open()) {
        cerr << "Erreur dans l'ouverture en lecture du fichier." << endl;
        return;
    }
    if (readFile) {
        char content;
        string beforeContent;
        char separator;
        int tabTile[gridSize][gridSize];
        for(int k = 0; k < linesBeforeGrid; k++)
        {
            getline(readFile, beforeContent);
        }
        for(int i = 0; i < gridSize; i++)
        {
            for(int j = 0; j < gridSize; j++)
            {
                readFile >> content;
                readFile >> separator;
                tabTile[i][j] = content - '0';
                cout << tabTile[i][j];
            }
            cout << endl;
        }
        readFile.close();
    }
}

void TileMap::getTileNameForId(int id)
{
        
}