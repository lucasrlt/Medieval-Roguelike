/**
 * @file Animator.h
 * @author Lucas ROLLET
 * @brief Module simplifiant la gestion des animations pour la SDL.
 */

#ifndef MEDIEVAL_ROGUELIKE_ANIMATOR_H
#define MEDIEVAL_ROGUELIKE_ANIMATOR_H

#include <SDL.h>
#include "../core/TileMap.h"
#include "Image.h"
#include <string>
#include "../core/Vector2D.h"

using namespace std;
const int ANIMATION_INTERVAL = 100;

/**
 * @brief Une animation est un enchaînement de sprites qui s'enchainent à intervalle régulier.
 */
class Animator {
private:
  Image spritesheet;
  int currSprite, numSprites, spritesWidth, drawWidth, scale;
  Uint32 lastUpdateTime;

  /** @brief Change le sprite courant de l'animation. */
  void updateCurrSprite();

public: 
  Animator();

  /**
   * @brief Initialise un Animator.
   * 
   * @param renderer le renderer sur lequel seront affichées les images.
   * @param filename la spritesheet d'où sont issues les animations
   * @param numSprites le nombre de sprites sur la spritesheet
   * @param sprite_width largeur d'un sprite sur la spritesheet
   * @param draw_width dimension de l'image à dessiner
   * @param draw_scale échelle à laquelle dessiner l'image
   */
  void init(SDL_Renderer *renderer, const string& filename, int numSprites, int sprite_width, int draw_width, int draw_scale = 1);

  /**
   * @brief Affiche l'image courante de l'animation à l'écran.
   * 
   * @param renderer le renderer sur lequel sera affichée l'image
   * @param pos la position de l'entité à afficher dans le jeu
   * @param row ligne de la spritesheet à animer
   * @param flip retourner l'image sur l'axe X.
   */
  void draw(SDL_Renderer *renderer, Vector2D pos, int row, bool flip = false);
};

#endif