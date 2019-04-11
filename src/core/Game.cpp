#include "Player.h"
#include "Savage.h"
#include "Game.h"
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

Game::~Game()
{
    delete player;
    delete savage;
    delete ghost;
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

Ghost *Game::getConstGhost() const
{
    return ghost;
}

int Game::getCurrentRoomX() const { return currRoomX; }
int Game::getCurrentRoomY() const { return currRoomY; }

void Game::initDungeon()
{
    Vector2D pos;
    Vector2D force(0, 0);
    int health = 10;
    int energy = 15;
    int shield = 5;
    string idleSpritePlayer = "data/warrior_front.png";
    string leftSpritePlayer = "data/warrior_left.png";
    string rightSpritePlayer = "data/warrior_right.png";

    unsigned int damages = 12;
    unsigned int energyCost = 3;
    unsigned int attackSpeed = 5;
    int type = 1;
    float attackRange = 8;
    string weaponName = "Lance";

    //Caractéristiques du Savage
    Vector2D posSavage;
    int healthSavage = 15;
    int strenghtSavage = 2;
    string idleSpriteSavage= "data/warrior_front.png";
    string leftSpriteSavage= "data/warrior_left.png";
    string rightSpriteSavage= "data/warrior_right.png";

    // //Caratéristiques du Ghost
    Vector2D posGhost;
    int healthGhost = 15;
    int strenghtGhost = 2;
    string idleSpriteGhost = "data/warrior_front.png";
    string leftSpriteGhost = "data/warrior_left.png";
    string rightSpriteGhost = "data/warrior_right.png";

    Weapon weapon(damages, energyCost, attackSpeed, type, attackRange, weaponName);

    dungeonGenerator.generateDungeon(dungeon);

    currRoomX = (int)MAZE_SIZE / 2;
    currRoomY = (int)MAZE_SIZE / 2;
    currentRoom = getConstRoom((int)MAZE_SIZE / 2, (int)MAZE_SIZE / 2);

    tilemap = new TileMap();
    tilemap->init("data/tileset.tsx");
    tilemap->fetchRoomFromFile(currentRoom.tilemapName);
    pos = {(float)tilemap->playerSpawn.x, (float)tilemap->playerSpawn.y};
    player = new Player(pos, force, health, energy, shield, weapon, idleSpritePlayer, leftSpritePlayer, rightSpritePlayer);

    ghost = new Ghost(posGhost, force, healthGhost, strenghtGhost, idleSpriteGhost, leftSpriteGhost, rightSpriteGhost);
    
    // Point ennemyPos = tilemap->enemySpawns[rand() % tilemap->enemySpawns.size()];
    
    savage = new Savage(posSavage, force, healthSavage, strenghtSavage, idleSpriteSavage, leftSpriteSavage, rightSpriteSavage); //Utilier getStrenght ?
    isJumping = false;
}

void Game::keyboardActions(char action)
{
    switch (action)
    {
    case 'r':
        player->moveRight(*tilemap);
        player->movingRight = true;
        player->movingLeft = false;
        checkRoomChange('r');
        break;
    case 'l':
        player->moveLeft(*tilemap);
        player->movingLeft = true;
        player->movingRight = false;
        checkRoomChange('l');
        break;
    case 't':
        player->jump();
        break;
    case 'e':
        playerShoot(player->movingRight);
        break;
    default:
        break;
    }
}

void Game::automaticActions()
{
    checkRoomChange(' ');
    updateProjectile();
}

void Game::checkSpikes()
{
    if (tilemap->getXY(round(player->position.x), (int)round(player->position.y)).type == spike) {
        player->receiveDamage(1);
    }
}

void Game::checkRoomChange(char direction)
{
    if (tilemap->getXY(player->position.x, player->position.y).type == background)
    {
        if (player->position.x >= 14.8f && player->movingRight && currentRoom.schema.openRight)
            changeRoom('r');
        else if (player->position.x <= 1.0f && player->movingLeft && currentRoom.schema.openLeft)
            changeRoom('l');
        else if (player->position.y >= 14.8f && currentRoom.schema.openBottom)
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


void Game::playerShoot(bool right)
{
    Vector2D position;
    Vector2D velocity = {PROJECTILE_SPEED, 0};
    if(right)
    {
        position = {player->position.x,player->position.y};
    }
    else
    {
        position = {player->position.x,player->position.y};
        velocity.x = -PROJECTILE_SPEED;
    }

    Projectile p(position, velocity, PROJECTILE_DAMAGES, "data/blanc.jpg");
    projectiles.push_back(p);      
}

void Game::updateProjectile()
{
    for(int i = 0; i < projectiles.size(); i++)
    {
        projectiles[i].move();
    }
}