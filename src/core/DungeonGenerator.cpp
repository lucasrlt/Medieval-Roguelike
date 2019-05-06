#include <algorithm>
#include <tuple>
#include <dirent.h>
#include <random>
#include <string>
#include <time.h>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <chrono>
#include "DungeonGenerator.h"

using namespace std;

DungeonGenerator::DungeonGenerator()
{
    allRooms = nullptr;
    fetchRooms("data/tilemaps/");
}

DungeonGenerator::~DungeonGenerator()
{
    if (allRooms != nullptr)
        delete[] allRooms;
}

void DungeonGenerator::fetchRooms(const char *dir)
{
    // stockera les noms de toutes les tilemaps représentant des salles
    vector<string> files;

    // partie se chargeant de récupérer les noms des fichiers dans dir (site LIFAP4)
    DIR *dirp;
    struct dirent *dp;

    dirp = opendir(dir);
    assert(dirp);

    while ((dp = readdir(dirp)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            if (dp->d_name[0] != '.') // on enlève les fichiers commençant par . (.DS_STORE)
                files.push_back(dp->d_name);
        }
    }

    closedir(dirp);

    // crée le tableau sur le tas contenant toutes les salles
    roomCount = files.size();
    allRooms = new Room[roomCount];

    // pour chacune des tilemaps, on crée un objet Room et son RoomSchema associé, puis on l'ajoute
    // à allRooms.
    for (int j = 0; j < roomCount; j++)
    {
        string filename = files[j];
        Room newRoom;
        newRoom.tilemapName = "data/tilemaps/" + filename;
        newRoom.exterior = false;
        newRoom.isBossRoom = false;

        unsigned int i = 0;
        // Récup ère les différentes ouvertures de la salle et crée le RoomSchema
        while (filename[i] != '_') // les noms de fichier sont de la forme "LT_maSalle.tmx", avec L pour left et T pour top par exemple
        {
            if (filename[i] == 'B')
                newRoom.schema.openBottom = true;
            else if (filename[i] == 'T')
                newRoom.schema.openTop = true;
            else if (filename[i] == 'R')
                newRoom.schema.openRight = true;
            else if (filename[i] == 'L')
                newRoom.schema.openLeft = true;
            else if (filename[i] == 'E')
                newRoom.exterior = true;
            else if (filename[i] == 'O') {
                newRoom.exterior = true;
                newRoom.isBossRoom = true;
            }

            i++;
        }

        allRooms[j] = newRoom;
    }
}

/**
 * MAZE PATH GENERATION
 **/

void DungeonGenerator::displayMaze() const
{
    for (unsigned int y = 0; y < MAZE_SIZE; ++y)
    {
        for (unsigned int x = 0; x < MAZE_SIZE; ++x)
        {
            cout << maze[x][y] << ' ';
        }

        cout << endl;
    }
}

int DungeonGenerator::countAdjacentRooms(unsigned int x, unsigned int y) const
{
    unsigned int count = 0;

    vector<Point> neighbours;
    findNeighbours(x, y, neighbours);

    // pour chacun des points voisins, s'il est > 0 incrémente count.
    for (unsigned int i = 0; i < neighbours.size(); i++)
    {
        if (maze[neighbours[i].x][neighbours[i].y] > 0)
            count++;
    }

    return count;
}

void DungeonGenerator::fillMazeWithZeros()
{
    for (unsigned int y = 0; y < MAZE_SIZE; ++y)
    {
        for (unsigned int x = 0; x < MAZE_SIZE; ++x)
        {
            maze[x][y] = 0;
        }
    }
}

void DungeonGenerator::findNeighbours(unsigned int x, unsigned int y, vector<Point> &neighbours) const
{
    // prépare toutes les positions voisines au point (x,y). On utilise des tuples
    // pour simplifier le code.
    if (x > 0)
        neighbours.push_back({(int) x - 1, (int) y});
    if (x < MAZE_SIZE - 1)
        neighbours.push_back({(int) x + 1, (int) y});
    if (y > 0)
        neighbours.push_back({(int) x, (int) y - 1});
    if (y < MAZE_SIZE - 1)
        neighbours.push_back({(int) x, (int) y + 1});
}

// L'algorithme utilisé ici est un algorithme de recherche en profondeur (récursif).
// Cet algorithme permet de générer un chemin cohérent, tous les points étant reliés entre eux.
// Un exemple de chemin serait:
// [1 1 0 0 0]      les 0 sont des endroits vides.
// [1 0 1 1 1]      les 1 sont des emplacements qui devront être remplacés
// [1 1 1 0 1]      par des salles adaptées dans generateLevel().
void DungeonGenerator::generateMaze(unsigned int x, unsigned int y)
{
    maze[x][y] = 1;

    // trouve toutes les positions voisines au point (x, y)
    vector<Point> neighbours;
    findNeighbours(x, y, neighbours);

    // mélange le tableau de positions voisines, ce qui permet de rendre la génération aléatoire.
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(neighbours.begin(), neighbours.end(), default_random_engine(seed));

    // pour chacun des points voisins, si la case n'est pas déjà occupée et si
    // créer une nouvelle salle ne crée pas un cul-de-sac, on crée une nouvelle salle,
    // qui sera un nouveau point de départ pour generateMaze.
    for (unsigned int i = 0; i < neighbours.size(); ++i)
    {
        unsigned int nx = neighbours[i].x; // posX du voisin
        unsigned int ny = neighbours[i].y; // posY du voisin

        if (maze[nx][ny] == 0 && countAdjacentRooms(nx, nx) <= 1)
        {
            generateMaze(nx, ny);
        }
    }
}

/** DUNGEON GENERATION **/
Room DungeonGenerator::getRandomRoomForPos(unsigned int x, unsigned int y)
{
    srand(time(NULL));

    // Détermine les ouvertures que doit avoir la salle en fonction des voisins de (x,y).
    // Par exemple, si on a [1, *1*, 0] la salle pour le point *1* doit avoir une ouverture
    // à gauche mais pas à droite.
    RoomSchema schemaToUse;
    if (x > 0 && maze[x - 1][y] > 0)
        schemaToUse.openLeft = true;
    if (x < MAZE_SIZE - 1 && maze[x + 1][y] > 0)
        schemaToUse.openRight = true;
    if (y > 0 && maze[x][y - 1] > 0)
        schemaToUse.openTop = true;
    if (y < MAZE_SIZE - 1 && maze[x][y + 1] > 0)
        schemaToUse.openBottom = true;

    // Trouve toutes les salles correspondant au schéma trouvé au-desuss, et les ajoute à possibleRooms.
    vector<Room> possibleRooms;
    for (int i = 0; i < roomCount; ++i)
    {
        if (allRooms[i].schema == schemaToUse)
        {
            possibleRooms.push_back(allRooms[i]);
        }
    }

    // Retourne une salle aléatoire parmi toutes les salles possibles.
    // Room *newRoom = new Room(possibleRooms[rand() % possibleRooms.size()]);
    return possibleRooms[rand() % possibleRooms.size()];
}

bool DungeonGenerator::findBossRoom(Room **dungeon) {
    vector<Point> possiblePositions;

    // cherche une salle qui n'a qu'un voisin (extrêmité d'un chemin)
    for (int y = 0; y < MAZE_SIZE; ++y) {
        for (int x = 0; x < MAZE_SIZE; ++x) {
            if (maze[x][y] > 0 && countAdjacentRooms(x, y) == 1) {
                possiblePositions.push_back({x, y});
            }
        }
    }

    // le donjon ne contient pas d'extrêmité
    if (possiblePositions.size() == 0)
        return false;
    
    Point bossRoom = possiblePositions[rand() % possiblePositions.size()];

    for (int i = 0; i < roomCount; i++) {
        if (allRooms[i].isBossRoom) {
            dungeon[bossRoom.x][bossRoom.y] = allRooms[i];
            break;
        }
    }

    return true;
}

void DungeonGenerator::generateDungeon(Room** &dungeon)
{
    dungeon = new Room*[MAZE_SIZE];
    for (unsigned int i = 0; i < MAZE_SIZE; ++i)
    {
        dungeon[i] = new Room[MAZE_SIZE];
    }

    Room emptyRoom;
    do {
        fillMazeWithZeros();
        generateMaze((int)MAZE_SIZE / 2, (int)MAZE_SIZE / 2);

        for (unsigned int y = 0; y < MAZE_SIZE; ++y)
        {
            for (unsigned int x = 0; x < MAZE_SIZE; ++x)
            {
                dungeon[x][y] = maze[x][y] > 0 ? getRandomRoomForPos(x, y) : emptyRoom;
            }
        }
    } while(!findBossRoom(dungeon));
}

void DungeonGenerator::regressionTest()
{
    cout << endl << "- TESTS DungeonGenerator -" << endl;
    cout << "**************************" << endl;

    Room** dungeon;
    generateDungeon(dungeon);
    
    displayMaze();

    vector<Point> dungeon_test;
    for (int i = 0; i < MAZE_SIZE; i++)
    {
        for (int j = 0; j < MAZE_SIZE; j++)
        {
            findNeighbours(MAZE_SIZE, MAZE_SIZE, dungeon_test);
            assert(dungeon_test.size() > 0);
        }
    }
    cout << "--> Toutes les salles ont une salle voisine OK" << endl;

    for (int k = 0; k < 100; k++) {
        deleteDungeon(dungeon);
        generateDungeon(dungeon);
        
        bool hasBoss = false;
        for (int i = 0; i < MAZE_SIZE; i++)
        {
            for (int j = 0; j < MAZE_SIZE; j++)
            {
                if (countAdjacentRooms(j, i) == 1) {
                    hasBoss = true;
                    break;
                }
            }
        }
        assert(hasBoss);
    }

    cout << "--> Tous les donjons ont une salle de boss (100 essais) OK";

}

void DungeonGenerator::deleteDungeon(Room** &dungeon) {
    for (int i = 0; i < MAZE_SIZE; i++)
    { 
        delete [] dungeon[i];
        dungeon[i] = nullptr;
    }
    delete [] dungeon;
}