//
// Created by hadrien on 14/03/19.
//

#ifndef MEDIEVAL_ROGUELIKE_SDLGAME_H
#define MEDIEVAL_ROGUELIKE_SDLGAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "../core/Game.h"
#include "../core/Room.h"


class Image
{

private:
  SDL_Surface *surface;
  bool has_changed;

public:
  SDL_Texture *texture;
  Image();
  void loadFromFile(const char *filename, SDL_Renderer *renderer);
  void loadFromCurrentSurface(SDL_Renderer *renderer);
  void draw(SDL_Renderer *renderer, int x, int y, int w = -1, int h = -1);
  SDL_Texture *getTexture() const;
  void setSurface(SDL_Surface *surf);
};

class SDLGame
{
private:
  bool left;
  bool right;
  bool stop;
  bool drawBigMap;
  
  bool withSound;
  struct _Mix_Music *backGroundMusic;
  struct _Mix_Music *deathMusic;
  struct Mix_Chunk *hitPlayerSound;
  struct Mix_Chunk *playerAttackSwordSound;
  struct Mix_Chunk *playerProjectileSound;

  Uint32 lastTickTime;

  Image projectile;

  Image playerImages;
  int currPlayerSprite;
  Image playerIdle;
  Image playerLeft;
  Image playerRight;

  Image savageIdle;
  Image savageLeft;
  Image savageRight;

  Image ghostIdle;
  Image ghostLeft;
  Image ghostRight;

  Image itemIdle;

  Image backgroundExterior;
  Image backgroundInterior;

  TTF_Font * font;
  Image font_im;
  SDL_Color font_color;

  
  SDL_Window *window;
  SDL_Renderer *renderer;
  Image tilesetImg;
  Image heartSprite;

  void drawCurrentRoom(const Game &g);
  void drawPlayer(Player *player);

  void drawPlayerHeart(const Game &game);
  void drawBackground(const Game& g);
  void renderProjectiles(const Game &g);
  void drawHitFilter();
  void drawDeathScreen();
  void drawEnemies(const Game &g);
  void drawEnemiesHeart(const Game &g);
  void drawItemsRegen(const Game &g);


  /**
   * @brief Affiche la carte du niveau sur l'écran du joueur.
   * 
   * @param g instance du jeu.
   * @param minimap si minimap est vrai, affiche la map sous forme miniature en haut à droite de l'aécran.
   * Sinon, affiche la map au centre de l'écran.
   */
  void drawMap(const Game& g, bool minimap = true);
  
  
  void drawProjectiles(const Game &g);
  //TTF_Font * font;
  //Image font_im;
  //SDL_Color font_color;

public:
  SDLGame();
  ~SDLGame();
  void SDLLoop(Game &g);
  void SDLShow(const Game &g);
  //Image im_mur;
  //Image im_pastille;
  //Image im_fantome;
};

#endif //MEDIEVAL_ROGUELIKE_SDLGAME_H
