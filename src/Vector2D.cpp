//
// Created by alexandre on 2019-03-05.
//

#include "Vector2D.h"
#include <fstream>


Vector2D::Vector2D(){
    x = 0;
    y = 0;
}

Vector2D::Vector2D(float a, float b){
    x = a;
    y = b;
}

Vector2D operator+(Vector2D a, Vector2D b) {
    Vector2D c = {a.x + b.x, a.y + b.y};
    return c;
}

Vector2D operator-(Vector2D a, Vector2D b){
    Vector2D c = {a.x - b.x, a.y - b.y};
    return c;
}

Vector2D operator*(Vector2D a, float b){
    Vector2D c = {a.x*b, a.y*b};
    return c;
}

Vector2D operator/(Vector2D a, float b){
    Vector2D c = {a.x/b, a.y/b};
    return c;
}