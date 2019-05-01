/**
 * @brief Module gérant une salle du donjon.
 * 
 * @author Lucas ROLLET
 * @file Room.h
 */

#ifndef MEDIEVALROGUELIKE_ROOM_H
#define MEDIEVALROGUELIKE_ROOM_H

#include <string>
#include <vector>
using namespace std;

/**
 * @brief Structure contenant le schéma des portes d'une salle. 
 * Contient quatre paramètres booléens, représentant chacune des portes.
 */
struct RoomSchema
{
    bool openLeft = false;
    bool openRight = false;
    bool openBottom = false;
    bool openTop = false;

    bool operator==(const RoomSchema &schema) const;
};

/**
 * @brief Classe représentant une salle dans le donjon.
 * Contient un schéma d'ouvertures et le chemin vers le fichier de tilemap associé.
 */
class Room
{
  public:
    RoomSchema schema;
    int *tiles;
    string tilemapName;
    bool exterior, isBossRoom;

    Room();
    ~Room();
};

#endif //MEDIEVALROGUELIKE_ROOM_H
