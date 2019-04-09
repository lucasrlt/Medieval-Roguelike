//
// Created by hadrien on 14/03/19.
//

#include <cassert>
#include <time.h>
#include "SDLGame.h"
#include <stdlib.h>
#include "../core/TileMap.h"
#include <SDL_image.h>
#include <assert.h>
#include "../core/Game.h"
#include "../core/TileMap.h"
#include <iostream>
#include "../core/Game.h"
using namespace std;

const int SCALE = 3;
const int dimx = GRID_SIZE * TILE_SIZE * SCALE;
const int dimy = GRID_SIZE * TILE_SIZE * SCALE;

Image::Image()
{
    surface = nullptr;
    texture = nullptr;
    has_changed = false;
}

void Image::loadFromFile(const char *filename, SDL_Renderer *renderer)
{
    surface = IMG_Load(filename);
    if (surface == nullptr)
    {
        string nfn = string("../") + filename;
        cout << "Error: cannot load " << filename << ". Trying " << nfn << endl;
        surface = IMG_Load(nfn.c_str());
        if (surface == nullptr)
        {
            nfn = string("../") + nfn;
            surface = IMG_Load(nfn.c_str());
        }
    }
    if (surface == nullptr)
    {
        cout << "Error: cannot load " << filename << endl;
        exit(1);
    }

    SDL_Surface *surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(surface);
    surface = surfaceCorrectPixelFormat;

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr)
    {
        cout << "Error: problem to create the texture of " << filename << endl;
        exit(1);
    }
    SDL_FreeSurface(surfaceCorrectPixelFormat);
}

void Image::loadFromCurrentSurface(SDL_Renderer *renderer)
{
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr)
    {
        cout << "Error: problem to create the texture from surface " << endl;
        exit(1);
    }
}

void Image::draw(SDL_Renderer *renderer, int x, int y, int w, int h)
{
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w < 0) ? surface->w : w;
    r.h = (h < 0) ? surface->h : h;

    if (has_changed)
    {
        ok = SDL_UpdateTexture(texture, nullptr, surface->pixels, surface->pitch);
        assert(ok == 0);
        has_changed = false;
    }

    ok = SDL_RenderCopy(renderer, texture, nullptr, &r);
    assert(ok == 0);
}

SDL_Texture *Image::getTexture() const
{
    return texture;
}

void Image::setSurface(SDL_Surface *surf)
{
    surface = surf;
}
//-------------------------------------------------------------------------------------------------------------------//

SDLGame::SDLGame()
{
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // Creation de la fenetre
    window = SDL_CreateWindow("Medieval Rogue-Like", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    tilesetImg.loadFromFile("data/tileset_img.png", renderer);
    heartSprite.loadFromFile("data/heart_sprite.png", renderer);
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

SDLGame::~SDLGame()
{
    //TTF_CloseFont(font);
    // TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDLGame::SDLShow(const Game &g)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    drawCurrentRoom(g);

    for (int i = 0; i < g.getConstPlayer()->getHealth(); i++)
    {
        heartSprite.draw(renderer, 1 + (i * (SCALE + 20)), 0, 8 * SCALE, 8 * SCALE);
    }

    drawPlayer(g.getConstPlayer());
}
/*
    Game game;
    int x,y;
    const Room& ro = game.getConstRoom();
    const Player& pl = game.getConstPlayer();
//const Ennemies& en = game.getConstEnnemies();


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
void SDLGame::drawCurrentRoom(const Game &g)
{
    const TileMap &tilemap = g.getConstTilemap();

    for (int y = 0; y < GRID_SIZE; ++y)
    {
        for (int x = 0; x < GRID_SIZE; ++x)
        {
            const Tile &currTile = tilemap.getXY(x, y);
            if (currTile.id != 0)
            {
                SDL_Rect clipRect = {currTile.posX, currTile.posY, TILE_SIZE, TILE_SIZE};
                SDL_Rect destRect = {x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, TILE_SIZE * SCALE, TILE_SIZE * SCALE};
                SDL_RenderCopy(renderer, tilesetImg.texture, &clipRect, &destRect);
            }
        }
    }
}

void SDLGame::drawPlayer(Player *player)
{
    Image playerStop;
    Image playerRight;
    Image playerLeft;

    if (left)
    {
        player->spriteName = "data/warrior_left.png";
        playerLeft.loadFromFile(player->spriteName.c_str(), renderer);
        playerLeft.draw(renderer, player->position.x * TILE_SIZE * SCALE, player->position.y * TILE_SIZE * SCALE, 16 * SCALE, 16 * SCALE);
    }
    else if (right)
    {
        player->spriteName = "data/warrior_right.png";
        playerRight.loadFromFile(player->spriteName.c_str(), renderer);
        playerRight.draw(renderer, player->position.x * TILE_SIZE * SCALE, player->position.y * TILE_SIZE * SCALE, 16 * SCALE, 16 * SCALE);
    }
    else if (stop)
    {
        player->spriteName = "data/warrior_front.png";
        playerStop.loadFromFile(player->spriteName.c_str(), renderer);
        playerStop.draw(renderer, player->position.x * TILE_SIZE * SCALE, player->position.y * TILE_SIZE * SCALE, 16 * SCALE, 16 * SCALE);
    }
}

void SDLGame::SDLLoop(Game &g)
{
    SDL_Event events;
    bool quit = false;
    Room room;
    Uint32 t = SDL_GetTicks(), t2 = SDL_GetTicks(), nt;
    float deltaTime = 0.f;

    Player *p = g.getConstPlayer();
    const TileMap &tm = g.getConstTilemap();

    // tant que ce n'est pas la fin ...
    while (!quit)
    {

        nt = SDL_GetTicks();
        deltaTime = (nt - t) / 1000.f;
        if (nt - t2 > 500)
        {
            // cout << "HEY" << endl;
            g.checkSpikes();
            t2 = nt;
        }
        t = nt;


        // tant qu'il y a des evenements à traiter (cette boucle n'est pas bloquante)
        while (SDL_PollEvent(&events))
        {
            stop = true;
            right = false;
            left = false;
            if (events.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (events.type == SDL_KEYDOWN)
            {
                if (events.key.repeat == 0)
                {
                    switch (events.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_RIGHT:
                        g.keyboardActions('r');
                        break;
                    case SDL_SCANCODE_LEFT:
                        g.keyboardActions('l');
                        break;
                    case SDL_SCANCODE_UP:
                        g.keyboardActions('t');
                        break;
                    case SDL_SCANCODE_SPACE:
                        g.keyboardActions('e');
                        break;
                    default: break;
                    }
                }
            }
            else if (events.type == SDL_KEYUP)
            {
                if (events.key.repeat == 0)
                {
                    switch (events.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_RIGHT:
                        p->moveLeft(tm);
                        break;
                    case SDL_SCANCODE_LEFT:
                        p->moveRight(tm);
                        break;
                    default: break;
                    }
                }
            }
        }

        p->updatePosition(tm, deltaTime);
        g.automaticActions();

        // on affiche le jeu sur le buffer caché
        SDLShow(g);

        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }
}
