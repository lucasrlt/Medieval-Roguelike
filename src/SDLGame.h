//
// Created by hadrien on 14/03/19.
//

#ifndef MEDIEVAL_ROGUELIKE_SDLGAME_H
#define MEDIEVAL_ROGUELIKE_SDLGAME_H

#include <SDL.h>
#include <SDL_ttf.h>

class SDLGame {

private :

    SDL_Window * window;
    SDL_Renderer * renderer;

    //TTF_Font * font;
    //Image font_im;
    //SDL_Color font_color;


public :

    SDLGame();
    ~SDLGame ();
    //void SDLLoop ();
    //void SDLShow ();

};

#endif //MEDIEVAL_ROGUELIKE_SDLGAME_H
