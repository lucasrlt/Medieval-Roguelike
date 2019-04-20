#include <iostream>
#include "Savage.h"

using namespace std;

Savage::Savage()
{
    position = {0, 0};
    velocity = {0, 0};
    health = 0;
    strenght = 0;
    idleSprite = " ";
    leftSprite = " ";
    rightSprite = " ";
}

Savage::Savage(Vector2D posInit, Vector2D forceInit, int healthInit, int strenghtInit, bool isDeadCheck,
            std::string spriteNameIdle, std::string spriteNameLeft, std::string spriteNameRight) 
            {
    position = posInit;
    velocity = {0, 0};
    health = healthInit;
    strenght = strenghtInit;
    isDeadSavage = isDeadCheck;
    
    idleSprite = spriteNameIdle;
    leftSprite = spriteNameLeft;
    rightSprite = spriteNameRight;
}

Savage::~Savage()
{
}

int Savage::getStrenght() const
{
    return strenght;
}

bool Savage::checkHit(Player *player){
    if(isDeadSavage == false){
        if((position.x <= player->position.x + 0.75f && position.x >= player->position.x - 0.75f) && 
            (position.y <= player->position.y + 0.75f && position.y >= player->position.y - 0.75f))  
        {
            player->receiveDamage(strenght);
            return true;
        } 
    }   
}

void Savage::runToPlayer(){
    // while(position.x != game.getConstPlayer()->position.x){
    //     if(position.x - game.getConstPlayer()->position.x < 0){
    //         position.x += 5;
    //     }
    //     else if(position.x - game.getConstPlayer()->position.x > 0){
    //         position.x -= 5;
    //     }    
    // }
}

void Savage::attackPlayer(){

}