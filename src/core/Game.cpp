#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

Game::~Game(){
    delete player;
}

Room Game::getConstRoom(int x, int y){
    return dungeon[x][y];
}

Player* Game::getConstPlayer(){
    return player;
}

void Game::initDungeon(){
    Vector2D pos(100, 100);
    Vector2D force(3, 3);
    int health = 50;
    int energy = 15;
    int shield = 5;
    string spriteName = "Jean-Claude";

    unsigned int damages = 12;
    unsigned int energyCost = 3; 
    unsigned int attackSpeed = 5;
    int type = 1;
    float attackRange = 8;
    string weaponName = "Lance";

    Weapon weapon(damages, energyCost, attackSpeed, type, attackRange, weaponName);

    player = new Player(pos, force, health, energy, shield, weapon, spriteName);

    dungeonGenerator.generateDungeon(dungeon);

    currentRoom = getConstRoom((int)MAZE_SIZE/2, (int)MAZE_SIZE/2);
}

void Game::movePlayer(char move){
    switch (move)
    {
        case 'r':
            player->move({5, 0});
            break;
        case 'l':
            player->move({-5, 0});
            break;
        default:
            break;
    }
}

void Game::jump(){
    player->getForce();
    player->move({0, -3});
}