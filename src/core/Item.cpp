#include <iostream>
#include "Item.h"

Item::Item(){
    position = {0, 0};
    isTaken = false;
}

Item::Item(Vector2D posInit, bool isTakenCheck){
    position = posInit;
    isTaken = isTakenCheck;
}

Item::~Item(){

}

Vector2D Item::getPosition() const {
    return position;
}

void Item::regressionTest(){
    Item item({15, 15}, false);
    cout << endl << endl << "- TESTS Item-" << endl;
    cout << "**************************" << endl;
    cout << "--> Item initialisé OK" << endl;
}
