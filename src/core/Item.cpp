#include <iostream>
#include "Item.h"

Item::Item(){
    position = {0, 0};
    itemName = " ";
    isTaken = false;
}

Item::Item(Vector2D posInit, string spriteName, bool isTakenCheck){
    position = posInit;
    itemName = spriteName;
    isTaken = isTakenCheck;
}

Item::~Item(){

}