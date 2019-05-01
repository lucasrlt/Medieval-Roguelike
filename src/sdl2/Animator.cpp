#include "Animator.h"

Animator::Animator() {
    currSprite = 0;
    lastUpdateTime = 0;
}

void Animator::init(SDL_Renderer *renderer, const string& filename, int num_sprites, int sprite_width, int draw_width, int draw_scale) {
    spritesheet.loadFromFile(filename.c_str(), renderer);
    numSprites = num_sprites;
    spritesWidth = sprite_width;
    scale = draw_scale;
    drawWidth = draw_width * scale;
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
    SDL_Rect destRect = {(int) (pos.x * (drawWidth / scale)), (int) (pos.y * (drawWidth / scale)), drawWidth, drawWidth};
    SDL_RenderCopyEx(renderer, spritesheet.getTexture(), &clipRect, &destRect, 0, nullptr, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
