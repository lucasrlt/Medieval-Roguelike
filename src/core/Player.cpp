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
    if(isRunning){
        velocity = velocity * 1.5f;
        loseEnergy(1);
    }
}

const Weapon& Player::getWeapon() const { return weapon; }  

int Player::getEnergy() const { return energy; }

void Player::regressionTest()
{
    cout << endl << "- TESTS Player -" << endl;
    cout << "**************************" << endl;

    Player p({15, 15}, {10, 10}, 10, 5, weapon);
    p.loseEnergy(3);

    assert(p.energy == 2);
    cout << "--> Energie perdue OK" << endl;
}
