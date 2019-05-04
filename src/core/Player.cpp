#include "Player.h"
#include <string>
#include <iostream>

using namespace std;

Player::Player()
{
    energy = 0;
    shield = 0;
    idleSprite = " ";
    leftSprite = " ";
    rightSprite = " ";
    currentJumpHeight = 0;

    movingRight = true;
}

Player::Player(Vector2D positionInit, Vector2D forceInit, int healthInit, int energyInit, int shieldInit, 
            Weapon weaponInit, std::string spriteNameIdle, std::string spriteNameLeft, std::string spriteNameRight) 
            : Entity(positionInit, forceInit, healthInit, spriteNameIdle, spriteNameLeft, spriteNameRight)
{
    weapon = weaponInit;
    energy = energyInit;
    shield = shieldInit;
    
    idleSprite = spriteNameIdle;
    leftSprite = spriteNameLeft;
    rightSprite = spriteNameRight;

    movingRight = true;
}

Player::~Player()
{
}

// void Player::receiveShieldDamage(int amount) //Dégâts dans le shield (plus tard)
// {
//     shield -= amount;
//     if (shield < 0)
//         shield = 0;
// }

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

// bool Player::jump(const TileMap &t)
// {
//     if (currentJumpHeight < MAX_JUMP_HEIGHT)
//     {
//         currentJumpHeight += 5;
//         moveUp(t);
//         return true;
//     }
//     currentJumpHeight = 0;
//     return false;
// }

void Player::show()
{
    cout << "Energie: " << energy << endl;
    cout << "Bouclier: " << shield << endl;
    cout << "Nom: " << idleSprite << endl
         << endl;
}

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

    Vector2D v(3, 5);
    Entity e(v, v, 12, "oui", "non", "peut-être");

    Weapon w(5, 2, 3, 0, 3.4, "Lance");
    Player pa(v, v, 100, 5, 3, w, "warrior_front.png", "warrior_left.png", "warrior_right.png");
    //w.regressionTest();

    w.show();

    cout << endl
         << "Vie entité1: " << e.getHealth() << endl;
    cout << "Vie entité: " << e.getHealth() << endl;
    e.show();
}

int Player::getEnergy() const { return energy; }
int Player::getShield() const { return shield; }