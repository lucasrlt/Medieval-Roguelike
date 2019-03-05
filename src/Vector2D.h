//
// Created by alexandre on 2019-03-05.
//

#ifndef MEDIEVAL_ROGUELIKE_VECTOR2D_H
#define MEDIEVAL_ROGUELIKE_VECTOR2D_H

/**
 @brief Création de la classe Vector2D, qui servira à établir les positions et la force.
 */

class Vector2D {
public:
    float x;
    float y;

    Vector2D();

    Vector2D(float a, float b);

    ~Vector2D();
};

/**
 @brief Ajout des surcharges opérateurs pour les calculs de complexes.
 */

Vector2D operator+(Vector2D a, Vector2D b);

Vector2D operator-(Vector2D a, Vector2D b);

Vector2D operator*(Vector2D a, float b);

Vector2D operator/(Vector2D a, float b);


#endif //MEDIEVAL_ROGUELIKE_VECTOR2D_H
