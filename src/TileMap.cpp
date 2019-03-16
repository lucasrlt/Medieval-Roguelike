//
// Created by hadrien on 05/03/19.
//

#include "TileMap.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void TileMap::fetchRoomFromFile(const string &filename, int tabTile[GRID_SIZE][GRID_SIZE])
{
    ifstream readFile(filename.c_str()); //Ouverture d'un flux pour lire le fichier voulu

    if (!readFile.is_open())
    { //En cas d'erreur de l'ouverture du fichier, envoie un message d'erreur et stop le programme
        cerr << "TILEMAP: Erreur dans l'ouverture en lecture du fichier." << endl;
        return;
    }

    if (readFile)
    {
        char content;
        string beforeContent;
        char separator;

        for (int k = 0; k < LINES_BEFORE_GRID; k++) //Récupère les premières lignes inutiles
        {
            getline(readFile, beforeContent);
        }

        for (int i = 0; i < GRID_SIZE; i++) //Récupère les ids des tiles et les stocke dans un tableau 2D
        {
            for (int j = 0; j < GRID_SIZE; j++)
            {
                readFile >> content;
                readFile >> separator;
                tabTile[i][j] = content - '0';
            }
            cout << endl;
        }
        readFile.close(); //Ferme le flux
    }
}

void TileMap::getSpriteNames(vector<string> &files)
{
    const string filename = "../data/TileSet.tsx";
    string linesBeforeContent;
    string testContent;
    string separator;
    string sourceContent;
    string content;
    string spriteContent;

    ifstream readFile(filename.c_str());

    if (!readFile.is_open())
    {
        cerr << "Erreur dans l'ouverture en lecture du fichier." << endl;
        return;
    }
    while (!readFile.eof())
    {
        readFile >> testContent;
        if (testContent == "<image") // Si le string correspond à <image, on récupère le nom du fichier et on le rentre dans le vector
        {
            readFile >> separator;
            readFile >> separator;
            readFile >> sourceContent;

            size_t sourcePos = sourceContent.find("source="); //Cherche le mot source dans la chaine sourceContent
            content = sourceContent.substr(sourcePos + 8);    //Copie les caractères depuis le s de source jusqu'au " et le met dans le string content
            size_t contentPos = content.find('"');
            spriteContent = content.substr(0, contentPos);
            files.push_back(spriteContent);
        }
        else
        {
            getline(readFile, linesBeforeContent);
        }
    }
    readFile.close();
}