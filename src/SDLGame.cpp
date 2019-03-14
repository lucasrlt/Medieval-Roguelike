//
// Created by hadrien on 14/03/19.
//

#include <cassert>
#include <time.h>
#include "SDLGame.h"
#include <stdlib.h>
#include "TileMap.h"
//#include "Game.h"

#include <iostream>
using namespace std;

SDLGame::SDLGame ()
{
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;SDL_Quit();exit(1);
    }

    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;SDL_Quit();exit(1);
    }

    int dimx, dimy;
    dimx = GRID_SIZE;
    dimy = GRID_SIZE;
    dimx *= TILES_WIDTH;
    dimy *= TILES_HEIGHT;

    // Creation de la fenetre
    window = SDL_CreateWindow("Medieval Rogue-Like", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; SDL_Quit(); exit(1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
/*
    // IMAGES //TODO : Ajouter les images
    im_pacman.loadFromFile("data/pacman.png",renderer);
    im_mur.loadFromFile("data/mur.png",renderer);
    im_pastille.loadFromFile("data/pastille.png",renderer);
    im_fantome.loadFromFile("data/fantome.png",renderer);

    // FONTS
    font = TTF_OpenFont("data/DejaVuSansCondensed.ttf",50);
    if (font == NULL) {
        cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: " << TTF_GetError() << endl; SDL_Quit(); exit(1);
    }*//*
    font_color.r = 50;font_color.g = 50;font_color.b = 255;
    font_im.setSurface(TTF_RenderText_Solid(font,"Pacman",font_color));
    font_im.loadFromCurrentSurface(renderer);

*/}

/*SDLGame::~SDLGame ()
{
    //TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}*/

void SDLGame::SDLShow () {
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);}
/*
    Game game;
    int x,y;
    const Room& ro = game.getConstRoom();
    const Player& pl = game.getConstPlayer();
//const Ennemies& en = game.getConstEnnemies();

// Afficher les sprites des murs et des pastilles
  for (x=0;x<ter.getDimX();++x)
      for (y=0;y<ter.getDimY();++y)
          if (ter.getXY(x,y)=='#')
              im_mur.draw(renderer,x*TAILLE_SPRITE,y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);
          else if (ter.getXY(x,y)=='.')
              im_pastille.draw(renderer,x*TAILLE_SPRITE,y*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);

  // Afficher le sprite de Pacman
  im_pacman.draw(renderer,pac.getX()*TAILLE_SPRITE,pac.getY()*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);

  // Afficher le sprite du Fantome
  im_fantome.draw(renderer,fan.getX()*TAILLE_SPRITE,fan.getY()*TAILLE_SPRITE,TAILLE_SPRITE,TAILLE_SPRITE);

  // Ecrire un titre par dessus
  SDL_Rect positionTitre;
  positionTitre.x = 270;positionTitre.y = 49;positionTitre.w = 100;positionTitre.h = 30;
  SDL_RenderCopy(renderer,font_im.getTexture(),NULL,&positionTitre);

}
*/
void SDLGame::SDLLoop () {
  SDL_Event events;
  bool quit = false;

  // tant que ce n'est pas la fin ...
  while (!quit) {

      // tant qu'il y a des evenements à traiter (cette boucle n'est pas bloquante)
      while (SDL_PollEvent(&events)) {
          if (events.type == SDL_QUIT) quit = true;           // Si l'utilisateur a clique sur la croix de fermeture
      }

      // on affiche le jeu sur le buffer caché
      SDLShow();

      // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
      SDL_RenderPresent(renderer);
  }
}

