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

SDLGame::SDLGame()
{
    drawBigMap = false;
    isPlayerAttacking = false;
    isSelectionScreen = false;
    right = false;
    left = false;
    stop = true;

    initSDL();
    loadAssets();

    hitTime = SDL_GetTicks();
}

SDLGame::~SDLGame()
{
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    Mix_FreeChunk(hitPlayerSound);
    Mix_FreeChunk(playerAttackSwordSound);
    Mix_FreeChunk(playerProjectileSound);
    Mix_FreeMusic(backGroundMusic);
    Mix_FreeMusic(deathMusic);
    Mix_CloseAudio();

}

void SDLGame::initSDL() {
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() != 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // Initialisation de SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        cout << "No sound !!!" << endl;
        //SDL_Quit();exit(1);
        withSound = false;
    }
    else{
        withSound = true;
    }


    // Creation de la fenetre
    window = SDL_CreateWindow("Medieval Rogue-Like", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // Création du renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    if (withSound)
    {
        Mix_AllocateChannels(10); // Alloue 10 cannaux pour le son
        //0 = hitPlayerSound
        //1 = playerAttackSwordSound
        //2 = playerProjectileSound
    }

}

void SDLGame::drawGame(const Game &g)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    if (isSelectionScreen) {
        drawSelectionScreen();
    } else {
        if (!g.playerDead) {
            drawBackground(g);
            drawCurrentRoom(g);
            drawPlayerHeart(g);
            drawPlayer(g.getConstPlayer());
            drawEnemiesHeart(g);        
            drawEnemies(g);
            drawProjectiles(g);
            drawItemsRegen(g);
            drawMap(g, !drawBigMap);
        } else {
            withSound = false;
            Mix_PlayMusic(deathMusic, -1);
            drawDeathScreen();
        }
    }
}

void SDLGame::loadAssets() {
    /* === IMAGES === */
    tilesetImg.loadFromFile("data/tileset_img.png", renderer);
    heartSprite.loadFromFile("data/heart_sprite.png", renderer);
    backgroundExterior.loadFromFile("data/exterior_background.png", renderer);
    backgroundInterior.loadFromFile("data/interior_background.png", renderer);
    selectionScreen.loadFromFile("data/pixelart-1556009879434-1876.jpg", renderer);
    itemIdle.loadFromFile("data/burger.png", renderer);
    playerIdle.loadFromFile("data/warrior_front.png", renderer);
    projectileRight.loadFromFile("data/arrow_right.png",renderer);
    projectileLeft.loadFromFile("data/arrow_left.png", renderer);
    deathScreen.loadFromFile("data/deathscreen.jpg", renderer);
    selectionScreen.loadFromFile("data/pixelart-1556009879434-1876.jpg", renderer);


    /* === ANIMATORS === */
    ghostAnimator.init(renderer, "data/ghost_spritesheet.png", 6, 258, TILE_SIZE * SCALE);
    playerAnimator.init(renderer, "data/player_spritesheet.png", 7, 258, TILE_SIZE * SCALE);
    savageAnimator.init(renderer, "data/savage_spritesheet.png", 7, 258, TILE_SIZE * SCALE);


    /* === SONS === */
    if (withSound) {
        hitPlayerSound = Mix_LoadWAV("data/sounds/hitPlayerSound.wav");
        playerAttackSwordSound = Mix_LoadWAV("data/sounds/playerAttackSwordSound.wav");
        playerProjectileSound = Mix_LoadWAV("data/sounds/playerProjectileSound.wav");

        //Musiques utilisées dans le jeu
        backGroundMusic = Mix_LoadMUS("data/sounds/backGroundMusic.wav");
        deathMusic = Mix_LoadMUS("data/sounds/deathMusic.wav");

        if (hitPlayerSound == NULL || playerAttackSwordSound == NULL || playerProjectileSound == NULL ||
            backGroundMusic == NULL || deathMusic == NULL) 
        {
            cout << "Failed to load a music file: SDL_mixer Error: " << Mix_GetError() << endl; SDL_Quit(); exit(1);
        }
    }

    /* === FONTS === */
    font = TTF_OpenFont("data/The Wild Breath of Zelda.otf", 75);
    if (font == NULL) {
        cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: " << TTF_GetError() << endl; SDL_Quit(); exit(1);
    }
    font_color = {255, 255, 255};

}

void SDLGame::drawBackground(const Game &g) {
    const Room& r = g.getConstRoom(g.getCurrentRoomX(), g.getCurrentRoomY());

    // le fond n'est pas le même en extérieur qu'en intérieur
    if (r.exterior) {
        backgroundExterior.draw(renderer, 0, 0, dimx, dimy);
    } else {
        backgroundInterior.draw(renderer, 0, 0, dimx, dimy);
    }
}

void SDLGame::drawCurrentRoom(const Game &g)
{
    const TileMap &tilemap = g.getConstTilemap();

    // Dessine toutes les tiles d'une salle.
    for (int y = 0; y < GRID_SIZE; ++y)
    {
        for (int x = 0; x < GRID_SIZE; ++x)
        {
            const Tile &currTile = tilemap.getXY(x, y);
            if (currTile.id != 0)
            {
                SDL_Rect clipRect = {currTile.posX, currTile.posY, TILE_SIZE, TILE_SIZE};
                SDL_Rect destRect = {x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE, TILE_SIZE * SCALE, TILE_SIZE * SCALE};
                SDL_RenderCopy(renderer, tilesetImg.getTexture(), &clipRect, &destRect);
            }
        }
    }
}

void SDLGame::drawPlayerHeart(const Game &g){
    for (int i = 0; i < g.getConstPlayer()->getHealth(); i++)
    {
        heartSprite.draw(renderer, 1 + (i * (SCALE + 20)), 0, 8 * SCALE, 8 * SCALE);
    }
}

void SDLGame::drawEnemiesHeart(const Game &g) {
    Ghost* ghost = g.getConstGhost();
    Savage* savage = g.getConstSavage();

    if(!ghost->isDead){
        for(int i = 0 ; i < ghost->getHealth() ; i++)
        {
            heartSprite.draw(renderer, 
                             (ghost->position.x * SCALE * 16) + (i * (SCALE + 10)) + 5, 
                             ghost->position.y * SCALE * 16 -20, 
                             4 * SCALE, 4 * SCALE);
        }
    }
    if(savage != NULL && !savage->isDead){
        for(int i = 0 ; i < g.getConstSavage()->getHealth() ; i++)
        {
            heartSprite.draw(renderer, 
                             (savage->position.x * SCALE * 16) + (i * (SCALE + 10)) - 8, 
                             savage->position.y * SCALE * 16 -20, 
                             4 * SCALE, 4 * SCALE);
        }
    }
}

void SDLGame::drawItemsRegen(const Game &g){
    Item *item = g.getConstItems();

    if(item != NULL && !item->isTaken){
        itemIdle.draw(renderer, item->position.x * SCALE * 16, (item->position.y + 0.5f) * SCALE * 16, 8 * SCALE, 8 * SCALE);
    }
}


void SDLGame::drawPlayer(Player *player)
{
    int spritesheetRow = 1;
    if (isPlayerAttacking) spritesheetRow = 0;
    else if (isPlayerShooting) spritesheetRow = 2;

    playerAnimator.draw(renderer, player->position, spritesheetRow, player->movingRight);
}

void SDLGame::drawEnemy(Vector2D pos, Animator animator, bool goingRight, bool isAttacking, bool isDead) {
    // La spritesheet d'un ennemi est décomposé de cette manière: 
    // ligne 0 = marche / 1 = attaque / 2 = mort
    if (isDead) {
        animator.draw(renderer, pos, 2, goingRight);
    } else {
        if (isAttacking) {
            animator.draw(renderer, pos, 1, goingRight);
        } else {
            animator.draw(renderer, pos, 0, goingRight);
        }
    }

}

void SDLGame::drawText(const string& text, const SDL_Rect& rect, bool renderBg, const SDL_Color bg) {
    Image txt;
    txt.setSurface(TTF_RenderText_Solid(font, text.c_str(), font_color));
    txt.loadFromCurrentSurface(renderer);

    if (renderBg) {
        SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
    SDL_RenderCopy(renderer, txt.getTexture(), NULL, &rect);
}

void SDLGame::drawEnemies(const Game &g){
    const Ghost* ghost = g.getConstGhost();
    const Savage* savage = g.getConstSavage();

    const Player* player = g.getConstPlayer();

    bool goingLeft = true;
    if (ghost != NULL && !ghost->isDead) {
        if (ghost->position.x <= player->position.x) goingLeft = false;
        drawEnemy(ghost->position, ghostAnimator, goingLeft, isGhostAttacking, ghost->isDead);
    }

    if (savage != NULL && !savage->isDead) {
        goingLeft = false;
        if (savage-> position.x <= player->position.x) goingLeft = true;
        drawEnemy(savage->position, savageAnimator, goingLeft, isSavageAttacking, savage->isDead);
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
    cout << "GO." << endl;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 32);

    SDL_Rect r = {0, 0, dimx, dimy};
    SDL_RenderFillRect(renderer, &r);
}

void SDLGame::drawDeathScreen() {
    deathScreen.draw(renderer,0,0,dimx,dimy);
    drawText("NOUVELLE PARTIE", {dimx / 2 - 100, dimy / 2 + 200, 200, 50}, true, {30, 30, 30});
}

void SDLGame::drawSelectionScreen() 
{
    selectionScreen.draw(renderer,0,0,dimx,dimy);

    drawText("NOUVELLE PARTIE", {dimx / 2 - 120, dimy / 2, 200, 50}, true, {0, 0, 0});
    drawText("MEDIEVAL ROGUE-LIKE", {0, 0, dimx, 150}, true, {0, 0, 0});
    drawText("COMMENT JOUER ?", { dimx / 2 - 120, dimy / 2 + 100, 200, 50}, true, {0, 0, 0});
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

bool SDLGame::handleInputs(Game& g) {
    SDL_Event events;
    Player* p = g.getConstPlayer();
    const TileMap &tm = g.getConstTilemap();

    
    // tant qu'il y a des evenements à traiter (cette boucle n'est pas bloquante)
    while (SDL_PollEvent(&events))
    {
        if (events.type == SDL_QUIT)
        {
            return true;
        }
        else if (events.type == SDL_KEYDOWN)
        {
            if (events.key.repeat == 0)
            {
                switch (events.key.keysym.scancode)
                {
                case SDL_SCANCODE_RIGHT: // aller à droite
                    g.keyboardActions('r');
                    break;
                case SDL_SCANCODE_LEFT: // aller à gauche
                    g.keyboardActions('l');
                    break;
                case SDL_SCANCODE_UP: // sauter
                case SDL_SCANCODE_Q:
                    g.keyboardActions('t');
                    break;
                case SDL_SCANCODE_SPACE: // tirer
                    g.keyboardActions('e');

                    isPlayerShooting = true;
                    playerShootTime = SDL_GetTicks();
                    Mix_PlayChannel(2, playerProjectileSound, 0);
                    break;
                case SDL_SCANCODE_H: // attaquer càc
                    g.keyboardActions('h');

                    Mix_PlayChannel(1, playerAttackSwordSound, 0);
                    isPlayerAttacking = true;
                    playerAttackTime = SDL_GetTicks();
                    break;
                case SDL_SCANCODE_D:
                    g.keyboardActions('d');
                    break;
                case SDL_SCANCODE_TAB: // afficher la map en grand
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
                case SDL_SCANCODE_RIGHT: // quand on lache la touche droite, remettre la vitesse à droite à 9
                    p->moveLeft(tm);
                    break;
                case SDL_SCANCODE_LEFT: // idem pour la touche gauche
                    p->moveRight(tm);
                    break;
                case SDL_SCANCODE_TAB: // réaffiche la carte en petite taille
                    drawBigMap = false;
                    break;
                default: break;
                }
            }
        }
    }

    return false;
}

void SDLGame::updateGame(Game& g, float dt) {
    Player *p = g.getConstPlayer();
    Savage *s = g.getConstSavage();
    Ghost *gh = g.getConstGhost();
    const TileMap &tm = g.getConstTilemap();
    Uint32 nt = SDL_GetTicks();

    p->updatePosition(tm, dt);
    g.automaticActions(dt);

    // affiche un filtre rouge quand on prend des dégats toutes les 250ms
    if (nt - hitTime < 250 && !g.playerDead) drawHitFilter(); 

    // vérifie si le joueur est touché
    // le joueur ne peut être touché que toutes les 500ms
    if (nt - hitTime > 500)
    {
        isGhostAttacking = gh->checkHit(p);
        isSavageAttacking = (s != NULL && s->checkHit(p));
        if(g.checkSpikes() || isGhostAttacking || isSavageAttacking)
        {
            if(withSound)
                Mix_PlayChannel(0,hitPlayerSound,0);

            hitTime = SDL_GetTicks();
        } 
    }

    // une attaque dure 800ms (pour l'animation)
    if (isPlayerAttacking && nt - playerAttackTime > 800) {
        isPlayerAttacking = false;
    }

    // un tir dure 800ms (pour l'animation)
    if (isPlayerShooting && nt - playerShootTime > 500) {
        isPlayerShooting = false;
    }

}

void SDLGame::gameLoop(Game &g)
{
    bool quit = false;
    float deltaTime = 0.f;

    // lance la musique de fond
    Mix_VolumeMusic(MIX_MAX_VOLUME/5);
    if(withSound) Mix_PlayMusic(backGroundMusic, -1);

    lastTickTime = SDL_GetTicks();
    while (!quit)
    {       
        // temps utilisé pour que les déplacements soient fluides
        deltaTime = (SDL_GetTicks() - lastTickTime) / 1000.0f;

        quit = handleInputs(g);
        drawGame(g);
        updateGame(g, deltaTime);

        lastTickTime = SDL_GetTicks();

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}
