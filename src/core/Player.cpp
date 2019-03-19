#include "Player.h"
#include <string>
#include <iostream>

using namespace std;

Player::Player(){
    energy = 0;
    shield = 0;
    spriteName = " ";
}

Player::Player(Vector2D positionInit, Vector2D forceInit, int healthInit, int energyInit, int shieldInit, Weapon weaponInit, std::string name)
    : Entity(positionInit, forceInit, healthInit)
{
    weapon = weaponInit;
    energy = energyInit;
    shield = shieldInit;
    spriteName = name;
}

Player::~Player(){

}

void Player::receiveShieldDamage(int amount){
    shield -= amount;
    if(shield < 0)
        shield = 0;
}

void Player::loseEnergy(int amount){
    energy -= amount;
    if(energy < 0)
        energy = 0;
}

void Player::attack(Entity &e) {
    e.receiveDamage(weapon.damages);
}

void Player::show(){
    cout << "Energie: " << energy << endl;
    cout << "Bouclier: " << shield << endl;
    cout << "Nom: " << spriteName << endl << endl;
}

void Player::regressionTest(){

    /*
    Player p(5, 3, "JeSuisUnJoueur");
    assert(p.energy == 5 && p.shield == 3 && p.spriteName == "JeSuisUnJoueur");
    cout << "Paramètres ok" << endl;
    p.show();

    p.receiveShieldDamage(2);
    assert(p.shield == 1);
    cout << "receiveDamage ok" << endl;
    p.show();

    p.loseEnergy(3);
    assert(p.energy == 2);
    cout << "loseEnergy ok" << endl;
    p.show();

    p.loseEnergy(-3);
    p.receiveShieldDamage(-2);
    assert(p.energy == 5 && p.shield == 3);
    cout << "Ok" << endl;
    p.show();
    */

    Vector2D v(3, 5);
    Entity e(v, v, 12);

    Weapon w(5, 2, 3, 0, 3.4, "Lance");
    Player pa(v, v, 100, 5, 3, w, "joueur.png");
    //w.regressionTest();

    w.show();

    cout << endl << "Vie entité1: " << e.getHealth() << endl;
    pa.attack(e);
    cout << "Vie entité: " << e.getHealth() << endl;
    e.show();
}