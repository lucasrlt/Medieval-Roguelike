//
// Created by alexandre on 2019-03-05.
//

#ifndef MEDIEVAL_ROGUELIKE_VECTOR2D_H
#define MEDIEVAL_ROGUELIKE_VECTOR2D_H

/**
 @brief Création de la classe Vector2D, qui servira à établir les positions et la force.
 */

class Vector2D
{
  public:
    /**
     @brief Création d'un nombre complexe, avec x = partie réelle et y = partie imaginaire.
     */
    float x;
    float y;

    /**
    @brief Initialisation du vecteur 2D par défaut à 0.
    */
    Vector2D();

    /**
    @brief Initialisation du vecteur 2D avec des valeurs.
    */
    Vector2D(float a, float b);
};

/**
 @brief Surcharge opérateur pour l'addition de 2 complexes.
 */
Vector2D operator+(Vector2D a, Vector2D b);

/**
 @brief Surcharge opérateur pour la soustraction de 2 complexes.
 */
Vector2D operator-(Vector2D a, Vector2D b);

/**
 @brief Surcharge opérateur pour la multiplication d'un complexe avec un coefficient.
 */
Vector2D operator*(Vector2D a, float b);

/**
 @brief Surcharge opérateur pour la division d'un complexe avec un coefficient.
 */
Vector2D operator/(Vector2D a, float b);

#endif //MEDIEVAL_ROGUELIKE_VECTOR2D_H
