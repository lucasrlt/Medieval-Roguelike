#include <iostream>
#include "Vector2D.h"
#include <string.h>

using namespace std;

#ifndef MEDIEVALROGUELIKE_ITEM_H
#define MEDIEVALROGUELIKE_ITEM_H

/**
 * @brief Classe gérant les items du jeu.
 * A l'heure actuelle, seuls des items de régénération existent.
 */
class Item {
private: 
    Vector2D position;

public:
    bool isTaken;

    Item();
    Item(Vector2D posInit, bool isTakenCheck);
    ~Item();

    Vector2D getPosition() const;
};

#endif //MEDIEVALROGUELIKE_ITEMs_H