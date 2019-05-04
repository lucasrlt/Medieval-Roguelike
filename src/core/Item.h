#include <iostream>
#include "Vector2D.h"
#include <string.h>

using namespace std;

#ifndef MEDIEVALROGUELIKE_ITEM_H
#define MEDIEVALROGUELIKE_ITEM_H

class Item{
    public:
    Vector2D position;
    string itemName;
    bool isTaken;

    Item();

    Item(Vector2D posInit, string spriteName, bool isTakenCheck);

    ~Item();
};

#endif //MEDIEVALROGUELIKE_ITEMs_H