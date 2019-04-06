#include <iostream>
#include "Savage.h"

using namespace std;

Savage::Savage()
{
    position = {0, 0};
    velocity = {0, 0};
    health = 0;
    strenght = 0;
}

Savage::Savage(Vector2D posInit, Vector2D forceInit, int healthInit, int strenghtInit)
{
    position = posInit;
    velocity = forceInit;
    health = healthInit;
    strenght = strenghtInit;
}

Savage::~Savage()
{
}

int Savage::getStrenght() const
{
    return strenght;
}

void Savage::runToPlayer(Game &game)
{
}

void Savage::attackPlayer(Game &g)
{
}