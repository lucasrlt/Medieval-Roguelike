//
// Created by hadrien on 14/03/19.
//

#ifndef MEDIEVAL_ROGUELIKE_SDLGAME_H
#define MEDIEVAL_ROGUELIKE_SDLGAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "Room.h"

class Image {

private:

    SDL_Surface * surface;
    SDL_Texture * texture;
    bool has_changed;

public:
    Image () ;
    void loadFromFile (const char* filename, SDL_Renderer * renderer);
    void loadFromCurrentSurface (SDL_Renderer * renderer);
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
    SDL_Texture * getTexture() const;
    void setSurface(SDL_Surface * surf);
};


class SDLGame {

private :

    SDL_Window * window;
    SDL_Renderer * renderer;

    void renderRoom(Room room);
    //TTF_Font * font;
    //Image font_im;
    //SDL_Color font_color;


public :

    SDLGame();
    ~SDLGame ();
    void SDLLoop ();
    void SDLShow ();
    //Image im_mur;
    //Image im_pastille;
    //Image im_fantome;


};

#endif //MEDIEVAL_ROGUELIKE_SDLGAME_H
