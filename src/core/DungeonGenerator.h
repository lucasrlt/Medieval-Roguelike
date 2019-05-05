/**
 * @brief Module gérant la génération d'un donjon
 *
 * @author Lucas ROLLET
 * @file DungeonGenerator.h
 */

#ifndef MEDIEVALROGUELIKE_DUNGEONGENERATOR_H
#define MEDIEVALROGUELIKE_DUNGEONGENERATOR_H

#include <vector>
#include "Vector2D.h"
#include "Room.h"

const int MAZE_SIZE = 5;

/**
 * @brief Classe s'occupant de la génération d'un donjon de manière procédurale.
 * Contient la liste de toutes les salles du jeu, le chemin du labyrinthe, et le nom des salles du labyrinthe.
 */
class DungeonGenerator
{
  private:
    int roomCount;  /// @brief Nombre de salles dans data/tilemaps
    Room *allRooms; /// @brief Liste de toutes le salles qu'il est possible d'utiliser dans le donjon.

    /// @brief Tableau d'entiers représentant le chemin du labyrinthe. 0 = pas de salle, 1 = mettre une salle.
    int maze[MAZE_SIZE][MAZE_SIZE];

    /**
     * @brief Utilise un algorithme de recherche en profondeur (depth-first search) afin de
     * générer une chemin depuis un point de départ donné.
     * Tous les points du chemin doivent être connectés à un autre point relié à ce chemin.
     * Chaque point du chemin sera remplacé plus tard par une salle. Remplit le tableau maze
     * de DungeonGenerator avec des 0 pour les cases vides et des 1 pour les cases occupées par des salles.
     *
     * @param x,y coordonnées de départ du chemin
     */
    void generateMaze(unsigned int x, unsigned int y);

    /// @brief Remplit le tableau maze de zéros.
    void fillMazeWithZeros();

   
    /**
     * @brief Compte le nombre de salles adjacentes (maze[x][y] > 0) à la position donnée en paramètre.
     *
     * @param x,y coordonnées du point (dans le tableau maze) dont on cherche le nombre de voisins.
     * @return int nombre de voisins (> 0) du point (x, y)
     */
    int countAdjacentRooms(unsigned int x, unsigned int y) const;

    /**
     * @brief Retourne les positions adjacentes au point (x,y) en faisant attention aux
     * extrémités du tableau.
     *
     * @param x,y coordonnées du point (x,y)
     * @param neighbours retour des coordonnées voisines au point (x,y) sous la forme
     * d'un vecteur de tuples
     */
    void findNeighbours(unsigned int x, unsigned int y, vector<tuple<unsigned int, unsigned int>> &neighbours) const;

    /**
     * @brief Retourne une salle adaptée au point (x,y), c'est-à-dire qu'elle doit avoir des
     * ouvertures correspondant aux salles qui l'entourent.
     * En cas de plusieurs possibilité, la salle est choisie aléatoirement.
     *
     * @note Cette fonction est appelée lors du deuxième passage sur maze, pour
     * générer le plan des salles à partir du chemin du donjon.
     *
     * @param x,y coordonnées du point (x,y)
     * @return Room salle adaptée au point (x,y)
     */
    Room getRandomRoomForPos(unsigned int x, unsigned int y);

    void findBossRoom(Room** dungeon);

  public:
    DungeonGenerator();
    ~DungeonGenerator();

    /// @brief Affiche le tableau maze.
    void displayMaze() const;

    /**
     * @brief Génère un donjon de taille MAZE_SIZE x MAZE_SIZE procéduralement à partir
     * des différentes salles créées dans les tilemaps.
     *
     * @param dungeon tableau dans lequel les salles du donjon sont stockées.
     */
    void generateDungeon(Room** &dungeon);

    /**
     * @brief Crée des salles à partir de toutes les tilemaps stockées dans le dossier dir et
     * les ajoute dans le vecteur allRooms.
     *
     * @param dir dossier dans lequel se trouve les tilemaps représentant les salles.
     */
    void fetchRooms(const char *dir);

    void deleteDungeon(Room** &dungeon);

    void regressionTest();
};

#endif //MEDIEVALROGUELIKE_DUNGEONGENERATOR_H
