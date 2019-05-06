#include "Button.h"
#include <string>
#include <cassert>
#include <iostream>
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

void Button::regressionTest()
{
    cout << endl << endl << "- TESTS Button -" << endl;
    cout << "**************************" << endl;

    Button button("name", {15, 15}, {30, 30});
    assert(button.size.x == 30 && button.size.y == 30 && button.pos.x == 15 && button.pos.y == 15 && button.name == "name");

    cout << "--> Initialisation du bouton OK" << endl;

    bool touch = clickZone({25, 17});
    assert(touch == true);

    cout << "--> Zone de click OK" << endl;
}