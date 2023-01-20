#include <iostream>
#include <vector>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Sprite {
    private:
        void* id = NULL;
        SDL_Renderer* renderer = NULL;
        SDL_Texture* texture = NULL;
        int queriedWidth;
        int queriedHeight;
        SDL_Rect srcRect;
        SDL_Rect destRect;
    public:
        Sprite(
            SDL_Renderer* renderer,
            SDL_Texture* texture,
            Uint32 posX,
            Uint32 posY,
            Uint32 initialSpriteOffset,
            Uint32 width=16,
            Uint32 height=16
        ) {
            this->id = this;
            this->renderer = renderer;
            this->texture = texture;
            if(this->texture == nullptr) exit(1);

            this->srcRect.y = 0;
            this->srcRect.w = width;
            this->srcRect.h = height;
            SDL_QueryTexture(this->texture, NULL, NULL, &queriedWidth, &queriedHeight);
            this->setOffset(initialSpriteOffset);

            this->destRect.x = posX;
            this->destRect.y = posY;
            this->destRect.w = width;
            this->destRect.h = height;
        }
        ~Sprite() {
            SDL_DestroyTexture(this->texture);
        }

        Uint32 getPosX() { return this->destRect.x; }
        Uint32 getPosY() { return this->destRect.y; }
        void setPosX(Uint32 x) { this->destRect.x = x; }
        void setPosY(Uint32 y) { this->destRect.y = y; }

        void setOffset(Uint32 offset) {
            this->srcRect.x = offset * this->srcRect.w;
            if(this->srcRect.x > this->queriedWidth - this->srcRect.w) {
                std::cerr << "Invalid offset. Spritesheet is too short." << std::endl;
                exit(1);
            }
        }
        void setTexture(SDL_Texture* texture) {
            SDL_QueryTexture(texture, NULL, NULL, &queriedWidth, &queriedHeight);
            this->texture = texture;
        }

        void setBrightness(int brightness) {
            SDL_SetTextureColorMod(this->texture, brightness, brightness, brightness);
        }

        void render() {
            SDL_RenderCopy(this->renderer, this->texture, &this->srcRect, &this->destRect);
        }
        void update() {
            // noop.
        }
        void* getId() const {
            return this->id;
        }
        bool operator==(const Sprite &other) {
            return this->id == other.getId();
        }
};
