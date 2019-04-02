#include "Player.h"
#include "Savage.h"
#include "Game.h"
#include <iostream>
#include <string>

using namespace std;

Game::~Game()
{
    delete player;
    delete savage;
    delete tilemap;

    for (int i = 0; i < MAZE_SIZE; i++)
    {
        for (int j = 0; j < MAZE_SIZE; j++)
        {
            delete dungeon[i][j];
        }
    }
}

Room &Game::getConstRoom(int x, int y) const
{
    return *dungeon[x][y];
}

const TileMap &Game::getConstTilemap() const
{
    return *tilemap;
}

Player *Game::getConstPlayer() const
{
    return player;
}

Savage *Game::getConstSavage() const
{
    return savage;
}

int Game::getCurrentRoomX() const { return currRoomX; }
int Game::getCurrentRoomY() const { return currRoomY; }

void Game::initDungeon()
{
    Vector2D pos;
    Vector2D force(3, 3);
    int health = 10;
    int energy = 15;
    int shield = 5;
    string spriteNameFront = "data/warrior_front.png";
    string spriteNameLeft = "data/warrior_left.png";
    string spriteNameRight = "data/warrior_right.png";

    unsigned int damages = 12;
    unsigned int energyCost = 3;
    unsigned int attackSpeed = 5;
    int type = 1;
    float attackRange = 8;
    string weaponName = "Lance";

    //Caractéristiques du Savage
    Vector2D posSavage;
    int healthSavage = 15;
    int strenghtSavage = savage->getStrenght();
    string spriteNameBack = "data/warrior_back.png";

    Weapon weapon(damages, energyCost, attackSpeed, type, attackRange, weaponName);

    dungeonGenerator.generateDungeon(dungeon);

    currRoomX = (int)MAZE_SIZE / 2;
    currRoomY = (int)MAZE_SIZE / 2;
    currentRoom = getConstRoom((int)MAZE_SIZE / 2, (int)MAZE_SIZE / 2);

    /*if (currentRoom.schema.openBottom)
        pos = {7, 7};
    else if (currentRoom.schema.openLeft)
        pos = {1, 7};
    else if (currentRoom.schema.openRight)
        pos = {14, 7};
    else
        pos = {7, 7};*/

    tilemap = new TileMap();
    tilemap->init("data/tileset.tsx");
    tilemap->fetchRoomFromFile(currentRoom.tilemapName);
    pos = {(float)tilemap->playerSpawn.x, (float)tilemap->playerSpawn.y};
    player = new Player(pos, force, health, energy, shield, weapon, spriteNameFront, spriteNameLeft, spriteNameRight);
    // Point ennemyPos = tilemap->enemySpawns[rand() % tilemap->enemySpawns.size()];
    
    savage = new Savage(posSavage, force, healthSavage, strenghtSavage, spriteNameFront, spriteNameLeft, spriteNameRight); //Utilier getStrenght ?
    isJumping = false;
}

void Game::keyboardActions(char action)
{
    switch (action)
    {
    case 'r':
        player->moveRight(*tilemap);
        checkRoomChange('r');
        break;
    case 'l':
        player->moveLeft(*tilemap);
        checkRoomChange('l');
        break;
    case 't':
        isJumping = true;
        // checkRoomChange();
        break;
    default:
        break;
    }
}

void Game::automaticActions()
{
    if (isJumping)
    {
        isJumping = player->jump(*tilemap);
    }
    player->moveDown(*tilemap);

    checkRoomChange(false);
}

void Game::checkSpikes()
{
    if (tilemap->getXY((int)player->position.x, (int)player->position.y).type == spike)
        player->receiveDamage(1);
}

void Game::checkRoomChange(char direction)
{
    if (tilemap->getXY(player->position.x, player->position.y).type == background)
    {
        if (player->position.x >= 15.0f && direction == 'r' && currentRoom.schema.openRight)
            changeRoom('r');
        else if (player->position.x < 1.0f && direction == 'l' && currentRoom.schema.openLeft)
            changeRoom('l');
        else if (player->position.y >= 15.0f && currentRoom.schema.openBottom)
            changeRoom('b');
        else if (player->position.y < 1.0f && currentRoom.schema.openTop)
            changeRoom('t');
    }
}

void Game::changeRoom(char direction)
{
    switch (direction)
    {
    case 'r':
        currRoomX += 1;
        player->position = {0, 7};
        break;
    case 'l':
        currRoomX -= 1;
        player->position = {15, 7};
        break;
    case 'b':
        currRoomY += 1;
        player->position = {7, 1};
        break;
    case 't':
        currRoomY -= 1;
        player->position = {7, 13};
        break;
    }

    currentRoom = getConstRoom(currRoomX, currRoomY);
    tilemap->fetchRoomFromFile(currentRoom.tilemapName);
}