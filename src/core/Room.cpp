#include "Room.h"

bool RoomSchema::operator==(const RoomSchema &schema) const
{
    return openBottom == schema.openBottom && openTop == schema.openTop &&
           openRight == schema.openRight && openLeft == schema.openLeft;
}

Room::Room()
{
    tilemapName = "";
}

Room::~Room()
{
}
