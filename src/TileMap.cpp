//
// Created by hadrien on 05/03/19.
//

#include "TileMap.h"
#include <iostream>
#include <ifstream>

using namespace std;

void TileMap::fetchRoomFromFile(string filename)
{
    copyingfile(string filename);
    if (!copyingfile.is_open()) {
        cout << "Erreur dans l'ouverture en lecture du fichier." << endl;
        return;
    }
    tab = new TileMap[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            copyingfile >> tab[i][j];
    }
    copyingfile.close();
}