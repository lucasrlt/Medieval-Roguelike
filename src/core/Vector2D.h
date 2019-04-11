#ifndef MEDIEVAL_ROGUELIKE_VECTOR2D_H
#define MEDIEVAL_ROGUELIKE_VECTOR2D_H

/**
 @brief Module gérant les Vecteurs 2D.

 @file Vector2D.h
 @date 05/03/2019
 @author Alexandre PUILLET
 */
struct Point
{
  int x;
  int y;
};
/**
 * @brief Classe représentant un point de coordonnées x et y
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
    * @brief Initialisation du vecteur 2D avec des valeurs.
    * @param x valeur de la partie réelle du vecteur.
    * @param y valeur de la partie imaginaire du vecteur.
    */
    Vector2D(float x, float y);

    /**
     @brief Surcharge opérateur pour l'addition de 2 complexes.
    */
    const Vector2D operator+(const Vector2D &vec);
    const Vector2D operator+(float b);

    /**
     @brief Surcharge opérateur pour la soustraction de 2 complexes.
    */
    Vector2D operator-(const Vector2D &vec);

    /**
     @brief Surcharge opérateur pour la multiplication d'un complexe avec un coefficient.
    */
    const Vector2D operator*(const Vector2D &vec);

    Vector2D operator*(float b);

    /**
    @brief Surcharge opérateur pour la division d'un complexe avec un coefficient.
    */
    const Vector2D operator/(float b);

    /**
     * @brief Crée le module du vecteur
     */
    const float module();

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

#endif //MEDIEVAL_ROGUELIKE_VECTOR2D_H
