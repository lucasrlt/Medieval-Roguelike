#include "Button.h"
#include <string>

using namespace std;

Button::Button()
{
    name = "basicButton";
    pos = {0,0};
    size = {200,50};
}

Button::Button(const Button &_button)
{
    name = _button.name;
    pos = _button.pos;
    size = _button.size;
}

Button::Button(const string &_name, const Point &_pos, const Vector2D &_size)
{
    name = _name;
    pos = _pos;
    size = _size;
}

Button::~Button()
{
    name = "";
    pos = {0,0};
    size = {0,0};
}

string Button::getName()
{
    return name;
}

Point Button::getPos()
{
    return pos;
}

Vector2D Button::getSize()
{
    return size;
}

void Button::setName(const string &_name)
{
    name = _name;
}

void Button::setPos(const Point &_pos)
{
    pos = _pos;
}

void Button::setSize(const Vector2D &_size)
{
    size = _size;
}

bool Button::clickZone(const Point &_pos) // Définit la zone de click du bouton
{
    if(_pos.x >= pos.x && _pos.y >= pos.y && _pos.x <= (pos.x + size.x) && _pos.y <= (pos.y + size.y))
        return true;
    return false;
}