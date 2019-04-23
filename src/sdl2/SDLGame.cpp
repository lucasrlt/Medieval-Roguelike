//
// Created by hadrien on 14/03/19.
//

#include <cassert>
#include <time.h>
#include "SDLGame.h"
#include <stdlib.h>
#include <SDL_image.h>
#include <assert.h>
#include "../core/TileMap.h"
#include <iostream>
#include "../core/Game.h"
#include "../core/Projectile.h"
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
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    tilesetImg.loadFromFile("data/tileset_img.png", renderer);
    heartSprite.loadFromFile("data/heart_sprite.png", renderer);
    backgroundExterior.loadFromFile("data/exterior_background.png", renderer);
    backgroundInterior.loadFromFile("data/interior_background.png", renderer);

    font = TTF_OpenFont("data/The Wild Breath of Zelda.otf", 75);
    if (font == NULL) {
        cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: " << TTF_GetError() << endl; SDL_Quit(); exit(1);
    }
    font_color = {255, 255, 255};
    font_im.setSurface(TTF_RenderText_Solid(font,"VOUS ETES MORT CHEH",font_color));
    font_im.loadFromCurrentSurface(renderer);

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
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDLGame::SDLShow(const Game &g)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    if (!g.playerDead) {
        drawBackground(g);
        drawCurrentRoom(g);

        drawPlayerHeart(g);
        drawPlayer(g.getConstPlayer());
        drawEnemiesHeart(g);        
        drawEnemies(g);
        drawProjectiles(g);
        drawMap(g, !drawBigMap);
    } else {
        drawDeathScreen();
    }
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
void SDLGame::drawBackground(const Game &g) {
    const Room& r = g.getConstRoom(g.getCurrentRoomX(), g.getCurrentRoomY());

    if (r.exterior) {
        backgroundExterior.draw(renderer, 0, 0, dimx, dimy);
    } else {
        backgroundInterior.draw(renderer, 0, 0, dimx, dimy);
    }
}

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

void SDLGame::drawPlayerHeart(const Game &game){
    for (int i = 0; i < game.getConstPlayer()->getHealth(); i++)
    {
        heartSprite.draw(renderer, 1 + (i * (SCALE + 20)), 0, 8 * SCALE, 8 * SCALE);
    }
}

void SDLGame::drawEnemiesHeart(const Game &g){
    if(g.getConstGhost()->isDead == false){
        for(int i = 0 ; i < g.getConstGhost()->getHealth() ; i++)
        {
            heartSprite.draw(renderer, (g.getConstGhost()->position.x * SCALE * 16) + (i * (SCALE + 10)) + 5, g.getConstGhost()->position.y * SCALE * 16 -20, 4 * SCALE, 4 * SCALE);
        }
    }
    if(g.getConstSavage()->isDeadSavage == false){
        for(int i = 0 ; i < g.getConstSavage()->getHealth() ; i++)
        {
            heartSprite.draw(renderer, (g.getConstSavage()->position.x * SCALE * 16) + (i * (SCALE + 10)) -8, g.getConstSavage()->position.y * SCALE * 16 -20, 4 * SCALE, 4 * SCALE);
        }
    }
}

void SDLGame::drawPlayer(Player *player)
{
    if(left){
        playerLeft.draw(renderer, player->position.x * TILE_SIZE * SCALE, player->position.y * TILE_SIZE * SCALE, 16 * SCALE, 16 * SCALE);
    }
    else if(right){
        playerRight.draw(renderer, player->position.x * TILE_SIZE * SCALE, player->position.y * TILE_SIZE * SCALE, 16 * SCALE, 16 * SCALE);
    }
    else if(stop){
        playerIdle.draw(renderer, player->position.x * TILE_SIZE * SCALE, player->position.y * TILE_SIZE * SCALE, 16 * SCALE, 16 * SCALE);
    }
}

void SDLGame::drawEnemies(const Game &game){
    // savageLeft.draw(renderer, game.getConstSavage()->position.x * TILE_SIZE * SCALE, game.getConstSavage()->position.y * TILE_SIZE * SCALE, 16 * SCALE, 16 * SCALE);
    if(game.getConstGhost()->isDead == false) 
    {
        if(game.getConstGhost()->position.x < game.getConstPlayer()->position.x)
            ghostRight.draw(renderer, game.getConstGhost()->position.x * TILE_SIZE * SCALE, game.getConstGhost()->position.y * TILE_SIZE * SCALE, 16 * SCALE, 16 * SCALE);

        else if(game.getConstGhost()->position.x > game.getConstPlayer()->position.x)
            ghostLeft.draw(renderer, game.getConstGhost()->position.x * TILE_SIZE * SCALE, game.getConstGhost()->position.y * TILE_SIZE * SCALE, 16 * SCALE, 16 * SCALE);
    
        else if(game.getConstGhost()->position.x == game.getConstPlayer()->position.x)
            ghostIdle.draw(renderer, game.getConstGhost()->position.x * TILE_SIZE * SCALE, game.getConstGhost()->position.y * TILE_SIZE * SCALE, 16 * SCALE, 16 * SCALE);
    }
    if(game.getConstSavage()->isDeadSavage == false) 
    {
        if(game.getConstSavage()->position.x < game.getConstPlayer()->position.x)
            savageRight.draw(renderer, game.getConstSavage()->position.x * TILE_SIZE * SCALE, game.getConstSavage()->position.y * TILE_SIZE * SCALE, 16 * SCALE, 16 * SCALE);

        else if(game.getConstSavage()->position.x > game.getConstPlayer()->position.x)
            savageLeft.draw(renderer, game.getConstSavage()->position.x * TILE_SIZE * SCALE, game.getConstSavage()->position.y * TILE_SIZE * SCALE, 16 * SCALE, 16 * SCALE);
    
        else if(game.getConstSavage()->position.x == game.getConstPlayer()->position.x)
            savageIdle.draw(renderer, game.getConstSavage()->position.x * TILE_SIZE * SCALE, game.getConstSavage()->position.y * TILE_SIZE * SCALE, 16 * SCALE, 16 * SCALE);
    }
}

void SDLGame::drawProjectiles(const Game &g)
{
    projectile.loadFromFile("data/blanc.jpg",renderer);
    
    for(int i = 0; i < g.projectiles.size(); i++)
    {
        if(g.projectiles[i].isHit == false)
        {
            projectile.draw(renderer,g.projectiles[i].position.x * TILE_SIZE * SCALE,g.projectiles[i].position.y * TILE_SIZE * SCALE,16,16);
        } 
    }
}

void SDLGame::drawHitFilter() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 32);
    SDL_Rect r = {0, 0, dimx, dimy};
    SDL_RenderFillRect(renderer, &r);
}

void SDLGame::drawDeathScreen() {
    SDL_SetRenderDrawColor(renderer, 80, 0, 0, 255);
    
    SDL_Rect r = {0, 0, dimx, dimy};
    SDL_RenderFillRect(renderer, &r);

    SDL_Rect positionTitre;
    positionTitre.x = dimx / 2 - 300; 
    positionTitre.y = dimy / 2 - 100;
    positionTitre.w = 600;
    positionTitre.h = 200;
    SDL_RenderCopy(renderer,font_im.getTexture(),NULL,&positionTitre);
}

void SDLGame::drawMap(const Game& g, bool minimap) {
    SDL_Rect r = {0, 0, 0, 0}; // sera utilisé pour l'affichage des rectangles


    // le viewport est le rectangle dans le quel est dessiné la carte
    const int viewportOffset = minimap ? 580 : 175;
    const int viewportWidth = dimx - viewportOffset * (minimap ? 1 : 2) - (minimap ? 10 : 0);

    
    const int roomWidth = viewportWidth / 5, doorWidth = roomWidth / 4; // largeur d'une salle et d'une porte
    const int borderWidth = 4;

    const unsigned char mapOpacity = minimap ? 96 : 255;
    
    int roomPosX, roomPosY;

    Room *room;
    for (int y = 0; y < MAZE_SIZE; y++) { // boucle sur toutes les salles du dnjon
        for (int x = 0; x < MAZE_SIZE; x++) {
            room = g.dungeon[x][y];

            roomPosX = x * (viewportWidth / MAZE_SIZE) + viewportOffset; // position initiale d'une salle
            roomPosY = y * (viewportWidth / MAZE_SIZE) + (minimap ? 10 : viewportOffset);

            if (room != NULL) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, mapOpacity);
                r.x = roomPosX;
                r.y = roomPosY;
                r.w = r.h = roomWidth;
                SDL_RenderFillRect(renderer, &r); // dessine la bordure 

                SDL_SetRenderDrawColor(renderer, 192, 192, 192, mapOpacity);
                r.x = roomPosX + borderWidth;
                r.y = roomPosY + borderWidth;
                r.w = r.h = roomWidth - 2 * borderWidth;
                SDL_RenderFillRect(renderer, &r); // dessine l'intérieur de la salle

                // affiche le sprite du joueur dans la salle actuelle
                if (x == g.getCurrentRoomX() && y == g.getCurrentRoomY()) {
                    playerIdle.draw(renderer, roomPosX + roomWidth / 2 - (doorWidth * 1.5) / 2, 
                                              roomPosY + roomWidth / 2 - (doorWidth * 1.5) / 2, 
                                              doorWidth * 1.5, 
                                              doorWidth * 1.5);
                }


                SDL_SetRenderDrawColor(renderer, 192, 192, 192, mapOpacity);
                r.w = r.h = doorWidth;

                // pour chaque salle, on dessine un carré à chacune des ouvertures
                // afin de couper la bordure noire pour rendre l'ouverture visible. 
                r.y = roomPosY + roomWidth / 2 - doorWidth / 2; // les portes droite/gauche ont la même pos y
                if (room->schema.openLeft) {
                    r.x = roomPosX - doorWidth / 2;
                    SDL_RenderFillRect(renderer, &r);
                } 
                if (room->schema.openRight) {
                    r.x = roomPosX + roomWidth - doorWidth / 2;
                    SDL_RenderFillRect(renderer, &r);
                }

                r.x = roomPosX + roomWidth / 2 - doorWidth / 2; // les portes haut/bas ont la même pos x
                if (room->schema.openTop) {
                    r.y = roomPosY - doorWidth / 2;
                    SDL_RenderFillRect(renderer, &r);
                }
                if (room->schema.openBottom) {
                    r.y = roomPosY + roomWidth - doorWidth / 2;
                    SDL_RenderFillRect(renderer, &r);
                }
            }
        }
    }
}

void SDLGame::SDLLoop(Game &g)
{
    Player *p = g.getConstPlayer();
    Savage *s = g.getConstSavage();
    Ghost *gh = g.getConstGhost();
    const TileMap &tm = g.getConstTilemap();
    drawBigMap = false;


    // Charge les sprites du Ghosts (faire tableau de Ghost après).
    gh->idleSprite = "data/warrior_front.png";
    ghostIdle.loadFromFile(gh->idleSprite.c_str(), renderer);

    gh->leftSprite = "data/warrior_left.png";
    ghostLeft.loadFromFile(gh->leftSprite.c_str(), renderer);

    gh->idleSprite = "data/warrior_right.png";
    ghostRight.loadFromFile(gh->rightSprite.c_str(), renderer);

    // Charge les sprites du Savages (faire tableau de Savage après).
    s->idleSprite = "data/warrior_front.png";
    savageIdle.loadFromFile(s->idleSprite.c_str(), renderer);

    s->leftSprite = "data/warrior_left.png";
    savageLeft.loadFromFile(s->leftSprite.c_str(), renderer);

    s->rightSprite = "data/warrior_right.png";
    savageRight.loadFromFile(s->rightSprite.c_str(), renderer);

    // Charge les sprites du Player.
    p->idleSprite = "data/warrior_front.png";
    playerIdle.loadFromFile(p->idleSprite.c_str(), renderer); // Charge les sprite du joueur

    p->leftSprite = "data/warrior_left.png";
    playerLeft.loadFromFile(p->leftSprite.c_str(), renderer);

    p->rightSprite = "data/warrior_right.png";
    playerRight.loadFromFile(p->rightSprite.c_str(), renderer);
    
    SDL_Event events;
    bool quit = false;
    Room room;
    Uint32 t = SDL_GetTicks(), t2 = SDL_GetTicks(), nt, hitTime;
    float deltaTime = 0.f;
    right = false;
    left = false;
    stop = true;

    // tant que ce n'est pas la fin ...
    while (!quit)
    {       
        gh = g.getConstGhost();
        s = g.getConstSavage();
        nt = SDL_GetTicks();
        deltaTime = (nt - t) / 1000.f;

        // tant qu'il y a des evenements à traiter (cette boucle n'est pas bloquante)
        while (SDL_PollEvent(&events))
        {
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
                        right = true;
                        left = false;
                        g.keyboardActions('r');
                        break;
                    case SDL_SCANCODE_LEFT:
                        left = true;
                        right = false;
                        g.keyboardActions('l');
                        break;
                    case SDL_SCANCODE_UP:
                        g.keyboardActions('t');
                        break;
                    case SDL_SCANCODE_SPACE:
                        g.keyboardActions('e');
                        break;
                    case SDL_SCANCODE_H:
                        g.keyboardActions('h');
                        break;
                    case SDL_SCANCODE_TAB:
                        drawBigMap = true;
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
                        stop = true;
                        right = false;
                        p->moveLeft(tm);
                        break;
                    case SDL_SCANCODE_LEFT:
                        stop = true;
                        left = false;
                        p->moveRight(tm);
                        break;
                    case SDL_SCANCODE_TAB:
                        drawBigMap = false;
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
        if (SDL_GetTicks() - hitTime < 250 && !g.playerDead) drawHitFilter();

        if (nt - t2 > 500)
        {
            if(g.checkSpikes() || gh->checkHit(p) || s->checkHit(p))
            {
                hitTime = SDL_GetTicks();
                t2 = nt;
            } 
        }
        t = nt;


        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }
}
