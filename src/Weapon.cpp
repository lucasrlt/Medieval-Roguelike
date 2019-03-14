#include "Weapon.h"
#include <string>
#include <iostream>

using namespace std;

Weapon::Weapon() {
    damages = 0;
    energyCost = 0;
    attackSpeed = 0;

    type = 0;

    attackRange = 0.0f;

    spriteName = " ";
}

Weapon::Weapon(unsigned int damagesInit, unsigned int energyCostInit, unsigned int attackSpeedInit,
                int typeInit, float attackRangeInit, string name) {
    damages = damagesInit;
    energyCost = energyCostInit;
    attackSpeed = attackSpeedInit;

    type = typeInit;
    attackRange = attackRangeInit;
    spriteName = name;
}

Weapon::~Weapon() {

}

unsigned int Weapon::getDamages() {
    return damages;
}

void Weapon::show(){
    cout << "Dégâts: " << damages << endl;
    cout << "Coût en énergie: " << energyCost << endl;
    cout << "Vitesse d'attaque: " << attackSpeed << endl;
    cout << "Type de l'arme: " << type << endl;
    cout << "Distance d'attaque: " << attackRange << endl;
    cout << "Nom de l'arme: " << spriteName << endl;
}

void Weapon::regressionTest() {
    Weapon w(5, 2, 3, 0, 3.4, "Lance");
    w.show();
}