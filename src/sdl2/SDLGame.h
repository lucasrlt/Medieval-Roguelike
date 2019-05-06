/**
 * @file SDLGame.h
 * @author Hadrien GUY
 * @brief Contient le code du jeu SDL, gère l'affichage graphique et
 * les actions executées en fonction du temps.
 * @date 2019-03-14 
 */

#ifndef MEDIEVAL_ROGUELIKE_SDLGAME_H
#define MEDIEVAL_ROGUELIKE_SDLGAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Image.h"
#include "Animator.h"
#include "../core/Game.h"
#include "../core/Room.h"
#include "../core/Button.h"

const int SCALE = 3;
const int dimx = GRID_SIZE * TILE_SIZE * SCALE;
const int dimy = GRID_SIZE * TILE_SIZE * SCALE;
const int numSprites = 7;

/**
 * @brief Classe gérant tout l'affichage du jeu avec la SDL.
 * Ce jeu fait appel aux fonctions d'update du module Game, il s'occupe uniquement 
 * de la gestion des inputs et de l'affichage à l'écran.
 */
class SDLGame
{
private:
  /* ==== GESTION DE L'ETAT DU JEU ==== */
  bool drawBigMap; // dessine la map en petit ou en grand
  bool isPlaying; // vrai si le jeu est lancé

  /* === GESTION DES ECRANS DE MENU === */
  bool isSelectionScreen; // écran principal / d'acceuil
  bool isHTPScreen; // écran "how to play" 
  bool isDeathScreen; // écran de mort
  bool isPauseScreen; // écran de pause
  
  /* ==== GESTION DU SON ==== */
  bool withSound;
  struct _Mix_Music *backGroundMusic;
  struct Mix_Chunk *hitPlayerSound;
  struct Mix_Chunk *playerAttackSwordSound;
  struct Mix_Chunk *playerProjectileSound;
  struct Mix_Chunk *regenItemSound;

  /* ==== GESTION DES ANIMATIONS ==== */
  bool isGhostAttacking;
  Animator ghostAnimator;
  Animator bossAnimator;

  bool isSavageAttacking;
  Animator savageAnimator;

  bool isPlayerAttacking;
  bool isPlayerShooting;
  Animator playerAnimator;

  /* ==== GESTION DU TEMPS ==== */
  Uint32 lastTickTime;
  Uint32 playerAttackTime; // dernière attaque du joueur (CàC)
  Uint32 playerShootTime; // dernier tir du jouer (flèche distance)
  Uint32 hitTime; // dernière fois que le joueur a été touché

  /* ==== IMAGES ==== */
  Image playerIdle;
  Image projectileLeft;
  Image projectileRight;
  Image itemIdle;
  Image backgroundExterior;
  Image backgroundInterior;
  Image deathScreen;  
  Image selectionScreen;
  Image htpScreen;
  Image menuScreen;
  Image victoryScreen;
  Image tilesetImg;
  Image heartSprite;
  Image energySprite;

  /* === BOUTONS DES MENUS === */
  Button returnToSelectionScreen;
  Button goToHTP;
  Button newGameSelectionScreen;
  Button newGameDeathScreen;
  Button goBackToGame;
  Button goBackToFirstScreen;
  Button afterVictoryScreen;
  
  /* === POLICE ET COULEUR DE POLICE */
  TTF_Font * font;
  SDL_Color font_color;
  
  SDL_Window *window;
  SDL_Renderer *renderer;


  /* ==== FONCTIONS LOGIQUES ==== */

  /**
   * @brief Initialise la SDL et ses librairies (SDL_mixer, SDL_ttf, SDL_image),
   * et crée la fenêtre du jeu.
   */
  void initSDL();

  /**
   * @brief Initialise le jeu.
   */
  void initSDLGame();

  /**
   * @brief Charge toutes les données du jeu (images, fonts, sons, ...).
   */
  void loadAssets();

  /**
   * @brief Gère les actions de l'utilisateur. Prend en compte les actions clavier et les actions souris, 
   * et exécute les actions nécessaires.
   * 
   * @param g instance du jeu
   * @return true le joueur souhaite quitter le jeu
   */
  bool handleInputs(Game& g);

  /**
   * @brief Exécute toutes les actions devant être exécutées à chaque ticks (déplacements,
   * actions timées comme la prise de dégats, ...).
   * 
   * @param g instance du jeu.
   * @param dt intervalle entre deux ticks, calculé dans gameLoop()
   */
  void updateGame(Game& g, float dt);

  /* ==== FONCTIONS D'AFFICHAGE ==== */
  void drawGame(const Game &g);
  void drawCurrentRoom(const Game &g);
  void drawPlayer(const Player *player);
  void drawPlayerHeart(const Game &g);
  void drawPlayerEnergy(const Game &g);
  void drawBackground(const Game& g);
  void drawProjectiles(const Game &g);

  void drawHitFilter();
  void drawDeathScreen();
  void drawSelectionScreen();
  void drawHTPScreen();
  void drawMenuScreen();
  void drawVictoryScreen();

  void drawEnemies(const Game &g);
  void drawEnemiesHeart(const Game &g);
  

  /**
   * @brief Affiche du texte à l'écran.
   * 
   * @param text le texte à afficher
   * @param rect le SDL_Rect dans lequel sera affiché le texte
   * @param renderBg dessiner un fond derrière le texte ?
   * @param bg couleur du fond
   */
  void drawText(const string& text, const SDL_Rect& rect, bool renderBg = false, const SDL_Color bg = {0, 0, 0});

  /**
   * @brief Dessine les items récupérables par le joueur.
   * 
   * @param g instance du jeu
   */
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
  
  /**
   * @brief Fonction gérant les actions lors des clics sur les boutons de menus.
   * 
   * @param xm position x de la souris
   * @param ym position y de la souris
   * @param g instance du jeu
   * 
   * @note L'écran courant du menu à afficher est géré par différentes variables booléennes.
   */
  void updateButtons(int &xm, int &ym, Game &g);

public:
  /**
   * @brief Crée un objet SDLGame. Initialise les librairies SDL2, SDL_image, SDL_ttf, SDL_mixer,
   * puis initialise l'état du jeu et charge les assets.
   */ 
  SDLGame();

  /**
   * @brief Détruit un objet SDLGame en libérant les textures, renderer, polices d'écritures, et les sons.
   */
  ~SDLGame();

  /**
   * @brief Boucle principale du jeu. Dans cette boucle sont effectuées
   * toutes les actions nécessaires au fonctionnement du jeu (update, draw, inputs).
   * 
   * @param g instance du jeu.
   */
  void gameLoop(Game &g);
};

#endif //MEDIEVAL_ROGUELIKE_SDLGAME_H
