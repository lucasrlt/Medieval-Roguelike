#include "Room.h"
#include <iostream>
using namespace std;

bool RoomSchema::operator==(const RoomSchema &schema) const
{
    return openBottom == schema.openBottom && openTop == schema.openTop &&
           openRight == schema.openRight && openLeft == schema.openLeft;
}

Room::Room()
{
    tilemapName = "";
}

Room::Room(const Room& r) {
    schema = r.schema;
    tiles = r.tiles;
    tilemapName = r.tilemapName;
    exterior = r.exterior;
    isBossRoom = r.isBossRoom;
}

Room::~Room()
{
}
