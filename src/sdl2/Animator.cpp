#include "Animator.h"

Animator::Animator() {
    currSprite = 0;
    lastUpdateTime = 0;
}

void Animator::init(SDL_Renderer *renderer, const string& filename, int num_sprites, int sprite_width) {
    spritesheet.loadFromFile(filename.c_str(), renderer);
    numSprites = num_sprites;
    spritesWidth = sprite_width;
}

void Animator::updateCurrSprite() {
    // Toutes les 100ms, change le sprite courant.
    if (SDL_GetTicks() - lastUpdateTime > ANIMATION_INTERVAL) {
        currSprite++;
        if (currSprite > numSprites) currSprite = 0;

        lastUpdateTime = SDL_GetTicks();
    }
}

void Animator::draw(SDL_Renderer *renderer, Vector2D pos, int row, bool flip) {
    updateCurrSprite();
    
    // On n'affiche que la partie nécessaire de la spritesheet.
    SDL_Rect clipRect = {currSprite * spritesWidth, row * spritesWidth, spritesWidth, spritesWidth};
    SDL_Rect destRect = {(int) (pos.x * TILE_SIZE * SCALE), 
                        (int) (pos.y * TILE_SIZE * SCALE),
                    TILE_SIZE * SCALE,
                    TILE_SIZE * SCALE};
    SDL_RenderCopyEx(renderer, spritesheet.getTexture(), &clipRect, &destRect, 0, nullptr, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
