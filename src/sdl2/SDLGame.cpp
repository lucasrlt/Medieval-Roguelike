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
    //font_im.setSurface(TTF_RenderText_Solid(font,"VOUS ETES MORT CHEH",font_color));
    //font_im.loadFromCurrentSurface(renderer);


}

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

    /*if(isSelectionScreen)
        drawSelectionScreen();
    else*/
        if (!g.playerDead) 
        {
            drawBackground(g);
            drawCurrentRoom(g);
            drawPlayerHeart(g);
            drawPlayer(g.getConstPlayer());
            drawEnemiesHeart(g);        
            drawEnemies(g);
            drawProjectiles(g);
            drawMap(g, !drawBigMap);
        } 
    else {
        drawDeathScreen();
    }
}

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
    if(g.getConstSavage() != NULL && g.getConstSavage()->isDeadSavage == false){
        for(int i = 0 ; i < g.getConstSavage()->getHealth() ; i++)
        {
            heartSprite.draw(renderer, (g.getConstSavage()->position.x * SCALE * 16) + (i * (SCALE + 10)) -8, g.getConstSavage()->position.y * SCALE * 16 -20, 4 * SCALE, 4 * SCALE);
        }
    }
}

void SDLGame::drawPlayer(Player *player)
{
    int direction = (left ? 0 : (right ? 2 : 1));
    const int numSprites = 7;
    const int spriteWidth = 258;

    if (SDL_GetTicks() - lastTickTime > 100) {
        currPlayerSprite++;
        if (currPlayerSprite > numSprites) currPlayerSprite = 0;

        lastTickTime = SDL_GetTicks();
    }

    SDL_Rect clipRect = {currPlayerSprite * spriteWidth, direction * spriteWidth, spriteWidth, spriteWidth};
    SDL_Rect destRect = {(int) (player->position.x * TILE_SIZE * SCALE), 
                         (int) (player->position.y * TILE_SIZE * SCALE),
                        TILE_SIZE * SCALE,
                        TILE_SIZE * SCALE};

    Image imgToDisplay = (isPlayerAttacking ? playerAttackAnimation : (isPlayerShooting ? playerShootAnimation : playerImages));
    SDL_RenderCopy(renderer, imgToDisplay.getTexture(), &clipRect, &destRect);
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
    if(game.getConstSavage() != NULL && game.getConstSavage()->isDeadSavage == false) 
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
    Image imgToDisplay;
    for(int i = 0; i < g.projectiles.size(); i++)
    {
        if(g.projectiles[i].isHit == false)
        {
            imgToDisplay = g.projectiles[i].isGoingRight() ? projectileRight : projectileLeft;
            imgToDisplay.draw(renderer,g.projectiles[i].position.x * TILE_SIZE * SCALE,g.projectiles[i].position.y * TILE_SIZE * SCALE,16,16);
        } 
    }
}

void SDLGame::drawHitFilter() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 32);
    SDL_Rect r = {0, 0, dimx, dimy};
    SDL_RenderFillRect(renderer, &r);
}

void SDLGame::drawDeathScreen() {
    deathScreen.loadFromFile("data/deathscreen.jpg", renderer);
    deathScreen.draw(renderer,0,0,dimx,dimy);

    //font_color = {255, 0, 0};

    newGame.setSurface(TTF_RenderText_Solid(font,"NOUVELLE PARTIE",font_color));
    newGame.loadFromCurrentSurface(renderer);

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);

    SDL_Rect newGameButton;
    newGameButton.x = dimx / 2 - 100; 
    newGameButton.y = dimy / 2 + 200;
    newGameButton.w = 200;
    newGameButton.h = 50;

    SDL_RenderFillRect(renderer,&newGameButton);
    SDL_RenderCopy(renderer,newGame.getTexture(),NULL,&newGameButton);
}

void SDLGame::drawSelectionScreen() 
{
    
    selectionScreen.loadFromFile("data/pixelart-1556009879434-1876.jpg", renderer);
    selectionScreen.draw(renderer,0,0,dimx,dimy);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);


    playButtonFont.setSurface(TTF_RenderText_Solid(font,"NOUVELLE PARTIE",font_color));
    playButtonFont.loadFromCurrentSurface(renderer);

    SDL_Rect playButton;
    playButton.x = dimx / 2 - 120; 
    playButton.y = dimy / 2;
    playButton.w = 200;
    playButton.h = 50;

    font_gameName.setSurface(TTF_RenderText_Solid(font,"MEDIEVAL ROGUE-LIKE",font_color));
    font_gameName.loadFromCurrentSurface(renderer);

    SDL_Rect gameTitle;
    gameTitle.x = 0; 
    gameTitle.y = 0;
    gameTitle.w = dimx;
    gameTitle.h = 150;

    htpButtonFont.setSurface(TTF_RenderText_Solid(font,"COMMENT JOUER?",font_color));
    htpButtonFont.loadFromCurrentSurface(renderer);

    SDL_Rect htpButton;
    htpButton.x = dimx / 2 - 120; 
    htpButton.y = dimy / 2 + 100;
    htpButton.w = 200;
    htpButton.h = 50;

    contactButtonFont.setSurface(TTF_RenderText_Solid(font,"NOUS CONTACTER",font_color));
    contactButtonFont.loadFromCurrentSurface(renderer);

    SDL_Rect contactButton;
    contactButton.x = dimx / 2 - 120; 
    contactButton.y = dimy / 2 + 200;
    contactButton.w = 200;
    contactButton.h = 50;

    SDL_RenderFillRect(renderer,&playButton);
    SDL_RenderFillRect(renderer,&gameTitle);
    SDL_RenderFillRect(renderer,&htpButton);
    SDL_RenderFillRect(renderer,&contactButton);

    SDL_RenderCopy(renderer,playButtonFont.getTexture(),NULL,&playButton);
    SDL_RenderCopy(renderer,font_gameName.getTexture(),NULL,&gameTitle);
    SDL_RenderCopy(renderer,htpButtonFont.getTexture(),NULL,&htpButton);
    SDL_RenderCopy(renderer,contactButtonFont.getTexture(),NULL,&contactButton);

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
    isPlayerAttacking = false;

    isSelectionScreen = true;

    // Charge les sprites du Ghosts (faire tableau de Ghost après).
    gh->idleSprite = "data/warrior_front.png";
    ghostIdle.loadFromFile(gh->idleSprite.c_str(), renderer);

    gh->leftSprite = "data/warrior_left.png";
    ghostLeft.loadFromFile(gh->leftSprite.c_str(), renderer);

    gh->idleSprite = "data/warrior_right.png";
    ghostRight.loadFromFile(gh->rightSprite.c_str(), renderer);

    // Charge les sprites du Savages (faire tableau de Savage après).
    // s->idleSprite = "data/warrior_front.png";
    savageIdle.loadFromFile("data/warrior_front.png", renderer);

    // s->leftSprite = "data/warrior_left.png";
    savageLeft.loadFromFile("data/warrior_left.png", renderer);

    // s->rightSprite = "data/warrior_right.png";
    savageRight.loadFromFile("data/warrior_right.png", renderer);

    // Charge les sprites du Player.
    p->idleSprite = "data/warrior_front.png";
    playerIdle.loadFromFile(p->idleSprite.c_str(), renderer); // Charge les sprite du joueur

    p->leftSprite = "data/warrior_left.png";
    playerLeft.loadFromFile(p->leftSprite.c_str(), renderer);

    p->rightSprite = "data/warrior_right.png";
    playerRight.loadFromFile(p->rightSprite.c_str(), renderer);

    projectileRight.loadFromFile("data/arrow_right.png",renderer);
    projectileLeft.loadFromFile("data/arrow_left.png", renderer);

    playerImages.loadFromFile("data/player_sprites.png", renderer);
    playerAttackAnimation.loadFromFile("data/player_attack_sprites.png", renderer);
    playerShootAnimation.loadFromFile("data/player_shoot_sprites.png", renderer);
    
    SDL_Event events;
    bool quit = false;
    Room room;
    Uint32 t = SDL_GetTicks(), t2 = SDL_GetTicks(), nt, hitTime;
    float deltaTime = 0.f;
    right = false;
    left = false;
    stop = true;

    // tant que ce n'est pas la fin ...
        lastTickTime = SDL_GetTicks();
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
                    case SDL_SCANCODE_Q:
                        g.keyboardActions('t');
                        break;
                    case SDL_SCANCODE_SPACE:
                        if (!isPlayerShooting) {
                            g.keyboardActions('e');
                            isPlayerShooting = true;
                            playerShootTime = SDL_GetTicks();
                        }
                        break;
                    case SDL_SCANCODE_H:
                        g.keyboardActions('h');

                        isPlayerAttacking = true;
                        playerAttackTime = SDL_GetTicks();
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
                if (events.key.repeat == 0) {
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
        g.automaticActions(deltaTime);

        // on affiche le jeu sur le buffer caché
        SDLShow(g);
        if (SDL_GetTicks() - hitTime < 250 && !g.playerDead) drawHitFilter();

        if (nt - t2 > 500)
        {
            if(g.checkSpikes() || gh->checkHit(p) || (s != NULL && s->checkHit(p)))
            {
                hitTime = SDL_GetTicks();
                t2 = nt;
            } 
        }
        t = nt;

        if (isPlayerAttacking && SDL_GetTicks() - playerAttackTime > 800) {
            isPlayerAttacking = false;
        }


        if (isPlayerShooting && SDL_GetTicks() - playerShootTime > 500) {
            isPlayerShooting = false;
        }


        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }
}
