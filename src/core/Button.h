#ifndef MEDIEVALROGUELIKE_BUTTON_H
#define MEDIEVALROGUELIKE_BUTTON_H

#include "Vector2D.h"
#include <string>

/**
 * @brief Module gérant les boutons du jeu.

 * @file Button.h
 * @date 30/04/2019
 * @author Hadrien GUY
 */

using namespace std;

class Button
{
    private:
        Point pos;
        string name;
        Vector2D size;

    public:
        Button();
        Button(const Button &_button);
        Button(const string &_name, const Point &_pos, const Vector2D &_size);
        ~Button();    
        string getName();
        Point getPos();
        Vector2D getSize();
        void setName(const string &_name);
        void setPos(const Point &_pos);
        void setSize(const Vector2D &_size);
        bool clickZone(const Point &pos);
};

#endif //MEDIEVALROGUELIKE_BUTTON_H
