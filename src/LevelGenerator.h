/**
 * @brief Module gérant la génération d'un niveau
 */

#ifndef MEDIEVALROGUELIKE_LEVELGENERATOR_H
#define MEDIEVALROGUELIKE_LEVELGENERATOR_H

#include <vector>
#include "Room.h"

/**
 * @brief La classe LevelGenerator contient la difficulté du niveau à générer (0: facile, 1: difficile),
 * ainsi que la liste de toutes les salles.
 */
class LevelGenerator {
private:
    int difficulty;
    std::vector<Room> roomsList;
public:
    LevelGenerator();
    void fetchRooms(char* dir);
    void generateLevel(Room level[]);
};


#endif //MEDIEVALROGUELIKE_LEVELGENERATOR_H
