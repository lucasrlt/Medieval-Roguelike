//
// Created by hadrien on 05/03/19.
//

#include "TileMap.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void TileMap::fetchRoomFromFile(const string& filename,int gridSize, int linesBeforeGrid)
{
    ifstream readFile(filename.c_str());    //Ouverture d'un flux pour lire le fichier voulu

    if (!readFile.is_open()) {              //En cas d'erreur de l'ouverture du fichier, envoie un message d'erreur et stop le programme
        cerr << "Erreur dans l'ouverture en lecture du fichier." << endl;
        return;
    }

    if (readFile) {
        char content;       //Variable contenant les numéros des sprites
        string beforeContent;   //Variable contenant les lignes de textes avant les ids des sprites
        char separator;     //Variable stockant les virgules entre les id des sprites
        int tabTile[gridSize][gridSize];    //Tableau 2D contenant tous les ids des sprites

        for(int k = 0; k < linesBeforeGrid; k++)    //Récupère les premières lignes inutiles
        {
            getline(readFile, beforeContent);
        }

        for(int i = 0; i < gridSize; i++)   //Récupère les ids des tiles et les stocke dans un tableau 2D
        {
            for(int j = 0; j < gridSize; j++)
            {
                readFile >> content;    //Lis le fichier et mets le contenu dans la variable content
                readFile >> separator;  //Lis le fichier et mets le contenu dans la variable separator
                tabTile[i][j] = content - '0';  //Mets le contenu de la variable content dans le tableau puis converti le caractère en entier
                //cout << tabTile[i][j];
            }
            cout << endl;
        }
        readFile.close();   //Ferme le flux
    }
}

void getSpriteNames(vector<string> &files)
{
    const string filename = "../data/tilemaps/TileSet.tsx";
    string linesBeforeContent;
    string testContent;
    string separator;
    string content;

    ifstream readFile(filename.c_str());

    if (!readFile.is_open()) {
        cerr << "Erreur dans l'ouverture en lecture du fichier." << endl;
        return;
    }
while (!readFile.eof())
    readFile >> testContent;
    if(testContent == "<image")
    {
        readFile >> separator;
        readFile >> separator;
        readFile >> content;
        content.substr(0,6); // Soustrait d'un caractère avec une certaine portée et le mets dans content
    } else
        getline(readFile,linesBeforeContent);
}