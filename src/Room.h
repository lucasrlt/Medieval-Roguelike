/**
 * @brief Module gérant une salle
 */

#ifndef MEDIEVALROGUELIKE_ROOM_H
#define MEDIEVALROGUELIKE_ROOM_H

struct RoomSchema {
    bool openLeft;
    bool openRight;
    bool openBottom;
    bool openTop;
};

class Room {
private:
    RoomSchema schema;
public:
    Room();
    Room(RoomSchema _schema);
};


#endif //MEDIEVALROGUELIKE_ROOM_H
