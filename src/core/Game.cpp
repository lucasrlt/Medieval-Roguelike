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

    dungeonGenerator.deleteDungeon(dungeon);
}

Game::Game() {
    wasInitialized = false;

    ghost = nullptr;
    savage = nullptr;
    item = nullptr;
    dungeon = nullptr;

    initDungeon();
}

Room &Game::getConstRoom(int x, int y) const {return dungeon[x][y]; }

const TileMap &Game::getConstTilemap() const { return *tilemap; }

Player *Game::getConstPlayer() const { return player; }

Savage *Game::getConstSavage() const { return savage; }

Ghost *Game::getConstGhost() const { return ghost; }

Item *Game::getConstItems() const { return item; }

int Game::getCurrentRoomX() const { return currRoomX; }
int Game::getCurrentRoomY() const { return currRoomY; }


void Game::spawnGhost(){
    //Caratéristiques du Ghost
    // Le boss est un fantôme spécial, donc ses caractéristiques ne sont pas les mêmes
    int healthGhost = currentRoom.isBossRoom ? 8 : 3;
    int strengthGhost = currentRoom.isBossRoom ? 3 : 1;
    Vector2D posGhost = {(float)tilemap->enemySpawns[0].x, (float)tilemap->enemySpawns[0].y};

    if (ghost != nullptr)
        delete ghost;

    ghost = new Ghost(posGhost, {0, 0}, healthGhost, strengthGhost, false);
    if (currentRoom.isBossRoom) {
        ghost->isBoss = true;
    }
}

void Game::spawnSavage() {
    if (savage != nullptr) {
        delete savage;
        savage = nullptr;
    }

    if(tilemap->savageSpawns.size() > 0)
    {
        Vector2D posSavage = {(float)tilemap->savageSpawns[0].x, (float)tilemap->savageSpawns[0].y};
        savage = new Savage(posSavage, {0, 0}, 5, 3, false);
    } 
}

void Game::spawnRegenItem(){
    if (item != nullptr)
        delete item;

    if (tilemap->itemSpawns.size() > 0) {
        Vector2D posItem = {(float)tilemap->itemSpawns[0].x, (float)tilemap->itemSpawns[0].y};
        item = new Item(posItem, false);
    }
    else {
        item = nullptr;
    }
}

void Game::initDungeon()
{
    // Si wasInitialized == true, alors ce n'est pas le premier appel à initDungeon
    // (nouvelle partie) donc il faut supprimer les anciens éléments
    if (wasInitialized) {
        delete player;
        delete tilemap;
        dungeonGenerator.deleteDungeon(dungeon);
    }


    // Init donjon
    dungeonGenerator.generateDungeon(dungeon);
    currRoomX = (int)MAZE_SIZE / 2;
    currRoomY = (int)MAZE_SIZE / 2;
    currentRoom = getConstRoom((int)MAZE_SIZE / 2, (int)MAZE_SIZE / 2);

    // Init tilemap
    tilemap = new TileMap();
    tilemap->init("data/tileset.tsx");
    tilemap->fetchRoomFromFile(currentRoom.tilemapName);

    // Init joueur
    Weapon playerWeapon(1, 5, 2);
    Vector2D playerPos = {(float)tilemap->playerSpawn.x, (float)tilemap->playerSpawn.y};
    player = new Player(playerPos, {0, 0}, 10, 5, playerWeapon);

    // Init l'état du jeu
    playerDead = false;
    hasWon = false;
    projectiles.clear();
    wasInitialized = true;

    // Init le contenu de la salle (ennemis/items)
    spawnGhost();
    spawnSavage();
    spawnRegenItem();

}


void Game::attackSword(){
    float width = ghost->isBoss ? 2 : 1;

    if((player->getPosition().x - player->getWeapon().attackRange <= ghost->getPosition().x && player->getPosition().x + player->getWeapon().attackRange >= ghost->getPosition().x) && 
    (player->getPosition().y <= ghost->getPosition().y + width && player->getPosition().y >= ghost->getPosition().y - width))
    {
        ghost->receiveDamage(player->getWeapon().damages);   //Dégâts pris par le ghost en fonction de l'arme du joueur
        if(ghost->getHealth() <= 0)
        {
            ghost->isDead = true;
        }
    }
    if(savage != NULL && (player->getPosition().x <= savage->getPosition().x + 1 && player->getPosition().x >= savage->getPosition().x - 1) && 
    (player->getPosition().y <= savage->getPosition().y + 1 && player->getPosition().y >= savage->getPosition().y - 1))
    {
        savage->receiveDamage(player->getWeapon().damages);  //Dégâts pris par le savage en fonction de l'arme du joueur
        if(savage->getHealth() <= 0)
        {
           savage->isDead = true;
        }
    }
}

void Game::checkItemTaken(){
    if((player->getPosition().x <= item->getPosition().x + 1 && player->getPosition().x >= item->getPosition().x - 1) && 
    (player->getPosition().y <= item->getPosition().y + 1 && player->getPosition().y >= item->getPosition().y - 1)){
        if(!item->isTaken){
            item->isTaken = true;
            player->receiveDamage(-3);
        }
    }
}

void Game::keyboardActions(char action)
{
    switch (action)     //Actions à faire en fonction de la touche appuyée (gérée dans la SDL)
    {
    case 'r': // déplacer à droite
        player->moveRight(*tilemap);
        player->lastDirectionRight = true;
        checkRoomChange();
        break;
    case 'l': // déplacer à gauche
        player->moveLeft(*tilemap);
        player->lastDirectionRight = false;
        checkRoomChange();
        break;
    case 'j': // sauter
        player->jump();
        break;
    case 'e': // tirer
        playerShoot();
        break;
    case 'h': // attacker à l'épée
        attackSword();
        break;
    case 's': // sprinter
        player->sprint();
        break;
    default:
        break;
    }
}

void Game::automaticActions(float dt)
{
    checkRoomChange();

    player->updatePosition(*tilemap, dt);
    ghost->flyToPlayer(player, dt);
    if (savage != NULL)
        savage->runToPlayer(player, *tilemap, dt);

    updateProjectiles();
    checkProjectileHit();

    if (player->getHealth() <= 0) {
        playerDead = true;
    }

    if(item != NULL){
        checkItemTaken();
    }

    hasWon = currentRoom.isBossRoom && ghost->isDead;
}

bool Game::checkSpikes()
{
    if (tilemap->getXY(round(player->getPosition().x), (int)round(player->getPosition().y)).type == spike) {
        player->receiveDamage(SPIKES_DAMAGES);
        return true;
    }
    return false;
}

void Game::checkRoomChange()
{
    if (tilemap->getXY(player->getPosition().x, player->getPosition().y).type == background)
    {
        // Vérifie si le joueur est sur sur le bord de l'écran, si oui, on le change de salle.
        if (player->getPosition().x >= 14.8f && player->isMovingRight() && currentRoom.schema.openRight)
            changeRoom('r');
        else if (player->getPosition().x <= 1.0f && !player->isMovingRight() && currentRoom.schema.openLeft)
            changeRoom('l');
        else if (player->getPosition().y >= 14.8f && currentRoom.schema.openBottom)
            changeRoom('b');
        else if (player->getPosition().y < 1.0f && currentRoom.schema.openTop)
            changeRoom('t');
    }
}

void Game::changeRoom(char direction)
{
    switch (direction)      // gère la position du joueur après le changement de room
    {
    case 'r':
        currRoomX += 1;
        player->setPosition({0, 7});
        break;
    case 'l':
        currRoomX -= 1;
        player->setPosition({15, 7});
        break;
    case 'b':
        currRoomY += 1;
        player->setPosition({7, 1});
        break;
    case 't':
        currRoomY -= 1;
        player->setPosition({7, 13});
        break;
    }

    currentRoom = getConstRoom(currRoomX, currRoomY);
    if (currentRoom.isBossRoom) {
        player->setPosition({(float)tilemap->playerSpawn.x, (float)tilemap->playerSpawn.y});
    }
    tilemap->fetchRoomFromFile(currentRoom.tilemapName);
    projectiles.clear();

    spawnGhost();
    spawnSavage();
    spawnRegenItem();
}


void Game::playerShoot()
{
    Vector2D position;
    Vector2D velocity = {PROJECTILE_SPEED, 0};
    if(player->lastDirectionRight)
    {
        position = {player->getPosition().x,player->getPosition().y};
    }
    else
    {
        position = {player->getPosition().x,player->getPosition().y};
        velocity.x = -PROJECTILE_SPEED;
    }

    Projectile p(position, velocity, PROJECTILE_DAMAGES);
    projectiles.push_back(p);      
}

void Game::checkProjectileHit()
{
    float width = ghost->isBoss ? 2.75f : 0.75f;
    for(unsigned int i = 0; i < projectiles.size(); i++)
    {
        if((projectiles[i].position.x <= ghost->getPosition().x + width && projectiles[i].position.x >= ghost->getPosition().x - width)
        && (projectiles[i].position.y <= ghost->getPosition().y + width && projectiles[i].position.y >= ghost->getPosition().y - width) && projectiles[i].isHit == false)
        {
            projectiles[i].hit(*ghost);
        }
          
        if(savage != NULL && (projectiles[i].position.x <= savage->getPosition().x + 0.75f && projectiles[i].position.x >= savage->getPosition().x - 0.75f)
        && (projectiles[i].position.y <= savage->getPosition().y + 0.75f && projectiles[i].position.y >= savage->getPosition().y - 0.75f) && !projectiles[i].isHit)
        {
            projectiles[i].hit(*savage);
        }
    }
}

void Game::updateProjectiles()
{
    for(unsigned int i = 0; i < projectiles.size(); i++)
    {
        projectiles[i].move();
        projectiles[i].checkCollision(*tilemap);
    }
}

void Game::regressionTest(){
    
}