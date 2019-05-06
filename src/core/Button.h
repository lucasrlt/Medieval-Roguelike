#ifndef MEDIEVALROGUELIKE_BUTTON_H
#define MEDIEVALROGUELIKE_BUTTON_H

#include "Vector2D.h"
#include <string>

/**
 * @brief Module gérant les boutons du jeu.

 * @file Button.h
 * @date 30/04/2019
 * @author Hadrien GUY
 */

using namespace std;

/**
 * @brief Principalement utiles dans la SDL, un bouton est un rectangle dans lequel
 * on peut cliquer. 
 */
class Button
{
    private:
        Point pos;
        string name;
        Vector2D size;

    public:
        Button();
        Button(const Button &_button);
        Button(const string &_name, const Point &_pos, const Vector2D &_size);
        ~Button();

        /**
         * @brief Retourne le nom du bouton
         * 
         * @return string 
         */

        string getName();
        /**
         * @brief Retourne la position du bouton
         * 
         * @return Point 
         */
        Point getPos();

        /**
         * @brief Retourne la taille du bouton
         * 
         * @return Vector2D 
         */
        Vector2D getSize();

        /**
         * @brief Set le nom du bouton
         * 
         * @param _name nom du bouton
         */
        void setName(const string &_name);

        /**
         * @brief Set la position du bouton
         * 
         * @param _pos position du bouton
         */
        void setPos(const Point &_pos);

        /**
         * @brief Set la taille du bouton
         * 
         * @param _size taille du bouton
         */
        void setSize(const Vector2D &_size);

        /**
         * @brief Vérifie si le curseur est dans la position du bouton au moment du click
         * 
         * @param pos position du curseur
         * @return true si la position du curseur lors du click est dans la position du bouton
         * @return false sinon
         */
        bool clickZone(const Point &pos);
};

#endif //MEDIEVALROGUELIKE_BUTTON_H
