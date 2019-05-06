#include "Player.h"
#include <string>
#include <iostream>

using namespace std;

Player::Player()
{
    energy = 0;
    shield = 0;
    currentJumpHeight = 0;
}

Player::Player(Vector2D positionInit, Vector2D forceInit, int healthInit, int energyInit, Weapon weaponInit) : Entity(positionInit, forceInit, healthInit)
{
    weapon = weaponInit;
    energy = energyInit;
}

Player::~Player()
{
}

void Player::loseEnergy(int amount)
{
    energy -= amount;
    if (energy < 0)
        energy = 0;
}

void Player::sprint(){
    if(energy > 0)
        velocity = velocity * 1.5f;
}

const Weapon& Player::getWeapon() const { return weapon; }  

void Player::regressionTest()
{

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
}

int Player::getEnergy() const { return energy; }
