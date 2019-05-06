#include "Weapon.h"
#include <string>
#include <iostream>

using namespace std;

Weapon::Weapon() {
    damages = 0;
    attackSpeed = 0;
    attackRange = 0.0f;
}

Weapon::Weapon(unsigned int damagesInit, unsigned int attackSpeedInit, float attackRangeInit) {
    damages = damagesInit;
    attackSpeed = attackSpeedInit;
    attackRange = attackRangeInit;
}

Weapon::~Weapon() {

}

void Weapon::regressionTest() {
}