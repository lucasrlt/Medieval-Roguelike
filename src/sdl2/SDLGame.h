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

  Image playerStop;
  Image playerLeft;
  Image playerRight;

  Image savageStop; //Image d'attente pour le savage
  Image savageLeft;
  Image savageRight;
  
  SDL_Window *window;
  SDL_Renderer *renderer;
  Image tilesetImg;
  Image heartSprite;
  void drawCurrentRoom(const Game &g);
  void drawPlayer(Player *player);
  void drawSavage(Savage *savage);

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
