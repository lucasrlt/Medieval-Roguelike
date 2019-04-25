//
// Created by hadrien on 14/03/19.
//

#ifndef MEDIEVAL_ROGUELIKE_SDLGAME_H
#define MEDIEVAL_ROGUELIKE_SDLGAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Image.h"
#include "Animator.h"
#include "../core/Game.h"
#include "../core/Room.h"

const int SCALE = 3;
const int dimx = GRID_SIZE * TILE_SIZE * SCALE;
const int dimy = GRID_SIZE * TILE_SIZE * SCALE;
const int numSprites = 7;

class SDLGame
{
private:
  /* ==== GESTION DE L'ETAT DU JEU ==== */
  bool left;
  bool right;
  bool stop;
  bool drawBigMap;
  bool isSelectionScreen;
  
  /* ==== GESTION DU SON ==== */
  bool withSound;
  struct _Mix_Music *backGroundMusic;
  struct _Mix_Music *deathMusic;
  struct Mix_Chunk *hitPlayerSound;
  struct Mix_Chunk *playerAttackSwordSound;
  struct Mix_Chunk *playerProjectileSound;

  /* ==== GESTION DES ANIMATIONS ==== */
  bool isGhostAttacking;
  Animator ghostAnimator;

  bool isSavageAttacking;
  Animator savageAnimator;

  bool isPlayerAttacking;
  bool isPlayerShooting;
  Animator playerAnimator;

  /* ---- GESTION DU TEMPS ---- */
  Uint32 lastTickTime;
  Uint32 playerAttackTime;
  Uint32 playerShootTime;

  /* ==== IMAGES ==== */
  Image playerIdle;
  
  Image projectileLeft;
  Image projectileRight;

  Image itemIdle;

  Image backgroundExterior;
  Image backgroundInterior;

  Image deathScreen;
  Image newGame;
  
  Image selectionScreen;
  Image playButtonFont;
  Image font_gameName;
  Image htpButtonFont;
  Image contactButtonFont;

  TTF_Font * font;
  SDL_Color font_color;

  
  SDL_Window *window;
  SDL_Renderer *renderer;
  Image tilesetImg;
  Image heartSprite;

  /* ==== FONCTIONS D'AFFICHAGE ==== */
  void drawCurrentRoom(const Game &g);
  void drawPlayer(Player *player);

  void drawPlayerHeart(const Game &game);
  void drawBackground(const Game& g);
  void renderProjectiles(const Game &g);
  void drawHitFilter();
  void drawDeathScreen();
  void drawSelectionScreen();
  void drawEnemies(const Game &g);
  void drawEnemiesHeart(const Game &g);
  void drawItemsRegen(const Game &g);

  /**
   * @brief Dessine un ennemi (fantôme ou sauvage) avec son animation.
   * 
   * @param pos position absolue de l'ennemi
   * @param animator animator lié à l'ennemi
   * @param goingRight direction de l'ennemi (droite/gauche)
   * @param isAttacking si vrai, l'animation d'attaque est affichée
   * @param isDead  si vrai, affiche l'animation de mort
   */
  void drawEnemy(Vector2D pos, Animator animator, bool goingRight, bool isAttacking, bool isDead);



  /**
   * @brief Affiche la carte du niveau sur l'écran du joueur.
   * 
   * @param g instance du jeu.
   * @param minimap si minimap est vrai, affiche la map sous forme miniature en haut à droite de l'aécran.
   * Sinon, affiche la map au centre de l'écran.
   */
  void drawMap(const Game& g, bool minimap = true);
  
  
  void drawProjectiles(const Game &g);


public:
  SDLGame();
  ~SDLGame();
  void SDLLoop(Game &g);
  void SDLShow(const Game &g);
};

#endif //MEDIEVAL_ROGUELIKE_SDLGAME_H
