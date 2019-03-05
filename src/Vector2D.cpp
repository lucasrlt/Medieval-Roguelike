//
// Created by alexandre on 2019-03-05.
//

#include "Vector2D.h"
#include <fstream>

/**
 @brief Initialisation du vecteur 2D par défaut à 0.
 */

Vector2D::Vector2D(){
    x = 0;
    y = 0;
}

/**
 @brief Initialisation du vecteur 2D avec des valeurs.
 */

Vector2D::Vector2D(float a, float b){
    x = a;
    y = b;
}

/**
 @brief Destructeur du Vector2D.
 */
Vector2D::~Vector2D(){
    x = 0;
    y = 0;
}

/**
 @brief Addition de 2 complexes.
 */
Vector2D operator+(Vector2D a, Vector2D b) {
    Vector2D c = {a.x + b.x, a.y + b.y};
    return c;
}

/**
 @brief Soustraction de 2 complexes.
 */
Vector2D operator-(Vector2D a, Vector2D b){
    Vector2D c = {a.x - b.x, a.y - b.y};
    return c;
}

/**
 @brief Multiplication d'un complexe par un coefficient.
 */
Vector2D operator*(Vector2D a, float b){
    Vector2D c = {a.x*b, a.y*b};
    return c;
}

/**
 @brief Division d'un complexe par un coefficient.
 */
Vector2D operator/(Vector2D a, float b){
    Vector2D c = {a.x/b, a.y/b};
    return c;
}