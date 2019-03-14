#ifndef MEDIEVAL_ROGUELIKE_VECTOR2D_H
#define MEDIEVAL_ROGUELIKE_VECTOR2D_H

/**
 @brief Module gérant les Vecteurs 2D.

 @file Vector2D.h
 @date 05/03/2019
 @author Alexandre PUILLET
 */


/**
 * @brief Classe représentant un point de coordonnées x et y
 */

class Vector2D {
public:
    float x;
    float y;

    /**
    @brief Initialisation du vecteur 2D par défaut à 0.
    */
    Vector2D();

    /**
    * @brief Initialisation du vecteur 2D avec des valeurs.
    * @param x valeur de la partie réelle du vecteur.
    * @param y valeur de la partie imaginaire du vecteur.
    */
    Vector2D(float x, float y);

    /**
     @brief Destructeur du vecteur 2D.
     */
    ~Vector2D();

    /**
     * @brief Affiche le vecteur.
     */
    void show();

    /**
    * @brief Tests du module.
    */
    void regressionTest();

};

/**
 @brief Surcharge opérateur pour l'addition de 2 complexes.
 */
void operator+(Vector2D &a, Vector2D b);

/**
 @brief Surcharge opérateur pour la soustraction de 2 complexes.
 */
void operator-(Vector2D &a, Vector2D b);

/**
 @brief Surcharge opérateur pour la multiplication d'un complexe avec un coefficient.
 */
void operator*(Vector2D &a, float b);

/**
 @brief Surcharge opérateur pour la division d'un complexe avec un coefficient.
 */
void operator/(Vector2D &a, float b);


#endif //MEDIEVAL_ROGUELIKE_VECTOR2D_H
