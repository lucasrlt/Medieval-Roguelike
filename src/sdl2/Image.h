#ifndef MEDIEVAL_ROGUELIKE_IMAGE_H
#define MEDIEVAL_ROGUELIKE_IMAGE_H

#include <SDL.h>
#include <SDL_image.h>
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

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
  void draw(SDL_Renderer *renderer, int x, int y, int w = -1, int h = -1, bool flipX = false);
  SDL_Texture *getTexture() const;
  void setSurface(SDL_Surface *surf);
};

#endif