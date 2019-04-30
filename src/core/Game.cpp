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
    if(savage != NULL)
        delete savage;
    if (ghost != NULL)
        delete ghost;
    if (item != NULL){
        delete item;
    }
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

Item *Game::getConstItems() const
{
    return item;
}

void Game::spawnGhost(){
    // if (ghost != NULL) {
    //     cout << "coucou" << endl;
    //     delete ghost;
    // }

    //Caratéristiques du Ghost
    Vector2D posGhost;
    int healthGhost = 3;
    int strengthGhost = 2;
    bool isDead = false;
    Vector2D force(0, 0);
    string idleSpriteGhost = "data/warrior_front.png";
    string leftSpriteGhost = "data/warrior_left.png";
    string rightSpriteGhost = "data/warrior_right.png";
    posGhost = {(float)tilemap->enemySpawns[0].x, (float)tilemap->enemySpawns[0].y};
    
    // ghost->position = posGhost;
    ghost = new Ghost(posGhost, force, healthGhost, strengthGhost, isDead, idleSpriteGhost, leftSpriteGhost, rightSpriteGhost);
}

void Game::spawnSavage(){
    //Caratéristiques du Savage
    Vector2D posSavage;
    int healthSavage = 5;
    int strengthSavage = 3;
    bool isDead = false;
    Vector2D force(0, 0);
    string idleSpriteSavage = "data/warrior_front.png";
    string leftSpriteSavage = "data/warrior_left.png";
    string rightSpriteSavage = "data/warrior_right.png";

    if(tilemap->savageSpawns.size() > 0)
    {
        posSavage = {(float)tilemap->savageSpawns[0].x, (float)tilemap->savageSpawns[0].y};
        savage = new Savage(posSavage, force, healthSavage, strengthSavage, isDead, idleSpriteSavage,
                             leftSpriteSavage, rightSpriteSavage);
    } 
    else 
        savage = NULL; 
}

void Game::spawnRegenItem(){
    string pathName = "data/burger.png";
    bool isTakenItem = false;
    Vector2D posItem;
    if (tilemap->itemSpawns.size() > 0) {
        posItem = {(float)tilemap->itemSpawns[0].x, (float)tilemap->itemSpawns[0].y};
        item = new Item(posItem, pathName, isTakenItem);
    }
    else{
        item = NULL;
    }
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

    unsigned int damages = 1;
    unsigned int energyCost = 3;
    unsigned int attackSpeed = 5;
    int type = 1;
    float attackRange = 2;
    string weaponName = "Lance";

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
    
    // Point ennemyPos = tilemap->enemySpawns[rand() % tilemap->enemySpawns.size()];
        isJumping = false;

    spawnGhost();
    spawnSavage();
    spawnRegenItem();
}

void Game::attackSword(){
    if((player->position.x - player->weapon.attackRange <= ghost->position.x && player->position.x + player->weapon.attackRange >= ghost->position.x) && 
    (player->position.y <= ghost->position.y + 1 && player->position.y >= ghost->position.y - 1))
    {
        ghost->receiveDamage(player->weapon.damages);
        if(ghost->getHealth() <= 0)
        {
            ghost->isDead = true;
        }
    }
    if(savage != NULL && (player->position.x <= savage->position.x + 1 && player->position.x >= savage->position.x - 1) && 
    (player->position.y <= savage->position.y + 1 && player->position.y >= savage->position.y - 1))
    {
        savage->receiveDamage(player->weapon.damages);
        if(savage->getHealth() <= 0)
        {
           savage->isDead = true;
        }
    }
}

void Game::takeItem(){
    if((player->position.x <= item->position.x + 1 && player->position.x >= item->position.x - 1) && 
    (player->position.y <= item->position.y + 1 && player->position.y >= item->position.y - 1)){
        if(!item->isTaken){
            item->isTaken = true;
            player->receiveDamage(-3);
        }
    }
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
    case 'h':
        attackSword();
        break;
    case 'd':
        takeItem();
        break;
    default:
        break;
    }
}

void Game::automaticActions(float dt)
{
    checkRoomChange(' ');
    ghost->flyToPlayer(player);
    if (savage != NULL)
        savage->runToPlayer(player,getConstTilemap(),dt);
    updateProjectile();

    if (player->getHealth() <= 0) {
        playerDead = true;
    }
    projectileHitEnnemy();

    if(item != NULL){
        takeItem();
    }
}

bool Game::checkSpikes()
{
    if (tilemap->getXY(round(player->position.x), (int)round(player->position.y)).type == spike) {
        player->receiveDamage(1);
        return true;
    }
    return false;
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
    projectiles.clear();
    spawnGhost();
    spawnSavage();
    spawnRegenItem();
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

void Game::projectileHitEnnemy()
{
    for(int i = 0; i < projectiles.size(); i++)
    {
        if((projectiles[i].position.x <= ghost->position.x + 0.75f && projectiles[i].position.x >= ghost->position.x - 0.75f)
        && (projectiles[i].position.y <= ghost->position.y + 0.75f && projectiles[i].position.y >= ghost->position.y - 0.75f) && !projectiles[i].isHit)
        {
            projectiles[i].hit(*ghost);
        }
          
        if(savage != NULL && (projectiles[i].position.x <= savage->position.x + 0.75f && projectiles[i].position.x >= savage->position.x - 0.75f)
        && (projectiles[i].position.y <= savage->position.y + 0.75f && projectiles[i].position.y >= savage->position.y - 0.75f) && !projectiles[i].isHit)
        {
            projectiles[i].hit(*savage);
        }
    }
}

void Game::updateProjectile()
{
    for(int i = 0; i < projectiles.size(); i++)
    {
        projectiles[i].move();
        projectiles[i].checkCollision(*tilemap);
    }
}