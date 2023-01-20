#include <iostream>
#include <vector>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Text {
  public:
    Text(SDL_Renderer* renderer, std::string message, int fontSize = 16, int scale = 1) {
      this->renderer = renderer;
      if (TTF_Init() == -1) { std::cerr << "Unable to initialize SDL_tff: " << TTF_GetError() << std::endl; exit(1); }
      this->font = TTF_OpenFont("fonts/OpenSans-Regular.ttf", fontSize);
      if(this->font == NULL) { std::cout << "Failed to load font." << std::endl << SDL_GetError() << std::endl; exit(1); }
      const char *cstr = message.c_str();
      this->scale = scale;
      this->messageColor = { 255, 255, 255 };
      this->messageSurface = TTF_RenderText_Solid(this->font, cstr, this->messageColor);
      this->messageTexture = SDL_CreateTextureFromSurface(this->renderer, this->messageSurface);
      SDL_QueryTexture(this->messageTexture, NULL, NULL, &this->textureWidth, &this->textureHeight);
    }
    ~Text() {
      SDL_FreeSurface(this->messageSurface);
      SDL_DestroyTexture(this->messageTexture);
    }
    
    int getWidth() { return this->textureWidth * this->scale; }
    int getHeight() { return this->textureHeight * this->scale; }

    void render(int x, int y) {
      this->textLocation = { x, y, this->getWidth(), this->getHeight() }; 
      SDL_RenderCopy(this->renderer, messageTexture, NULL, &textLocation);
    }

  private:
    SDL_Renderer* renderer = NULL;
    TTF_Font* font = NULL;
    int scale;
    SDL_Color messageColor;
    SDL_Surface* messageSurface = NULL;
    SDL_Texture* messageTexture = NULL;
    SDL_Rect textLocation;
    int textureWidth;
    int textureHeight;
};
