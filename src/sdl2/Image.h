/**
 * @file Image.h
 * @author Alexandre MEYER
 * @brief Module permettant une interaction simple avec les images dans la SDL.
 */

#ifndef MEDIEVAL_ROGUELIKE_IMAGE_H
#define MEDIEVAL_ROGUELIKE_IMAGE_H

#include <SDL.h>
#include <SDL_image.h>
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Classe représentant une Image pour la SDL.
 * Cette classe permet de charger et afficher une image depuis un fichier.
 */
class Image
{
private:
  SDL_Surface *surface;
  bool has_changed;
  SDL_Texture *texture;

public:
  Image();

  /**
   * @brief Charge un fichier dans une instance de la classe Image.
   * 
   * @param filename chemin vers le fichier
   * @param renderer renderer sur lequel l'image sera affichée
   */
  void loadFromFile(const char *filename, SDL_Renderer *renderer);

  /**
   * @brief Crée une texture à partir de la surface stockée dans l'Image.
   * 
   * @param renderer renderer sur lequel l'image sera affichée
   */
  void loadFromCurrentSurface(SDL_Renderer *renderer);

/**
   * @brief Dessine une image à l'écran.
   * 
   * @param renderer renderer sur lequel l'image sera affichée
   * @param x,y positions x et y de l'image
   * @param w,h largeur et hauteur de l'image
   * @param flipX renverser l'image sur l'axe X
   */
  void draw(SDL_Renderer *renderer, int x, int y, int w = -1, int h = -1, bool flipX = false);

  SDL_Texture *getTexture() const;
  void setSurface(SDL_Surface *surf);
  ~Image();
};

#endif