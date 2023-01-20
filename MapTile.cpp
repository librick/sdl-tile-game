#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Sprite.cpp"

class MapTile {
  private:
    int tileIndex;
    Sprite* tileSprite = NULL;
    int mapTileRandom(int min, int max) {
      static bool first = true;
      if (first) 
      {  
          srand( time(NULL) ); //seeding for the first time only!
          first = false;
      }
      return min + rand() % (( max + 1 ) - min);
    }

	public:
		MapTile(
      SDL_Renderer* renderer,
      SDL_Texture* spritesheetTexture,
      int posX,
      int posY,
      double normalizedHeight
    ) {
      this->tileIndex = 0;
      if(normalizedHeight < 0.3) { this->tileIndex = 0; }
      else if(normalizedHeight < 0.4) { this->tileIndex = 1; }
      else if(normalizedHeight < 0.55) { this->tileIndex = 2; }
      else if(normalizedHeight < 0.65) { this->tileIndex = 3; }
      else if(normalizedHeight < 0.75) { this->tileIndex = 4; }
      else if(normalizedHeight < 0.85) { this->tileIndex = 5; }
      else { this->tileIndex = 6; }

      int rand = this->mapTileRandom(0, 150);
      if(rand > 15 && rand < 20) { this->tileIndex = 7; }
      if(rand > 20 && rand < 25) { this->tileIndex = 8; }
      if(rand > 25 && rand < 30) { this->tileIndex = 9; }
      if(rand > 30 && rand < 35) { this->tileIndex = 10; }

      // if(normalizedHeight < 0.3) {
      //   this->tileIndex = (int)round(this->mapTileRandom(0, 3)) % 3;
      //   this->isWater = true;
      // } else if(normalizedHeight < 0.31) {
      //   this->tileIndex = 3;
      //   this->isSand = true;
      // } else if(normalizedHeight < 0.33) {
      //   this->tileIndex = 4;
      //   this->isSand = true;
      // } else if(normalizedHeight < 0.38) {
      //   this->tileIndex = 5;
      //   this->isSand = true;
      // } else if(normalizedHeight < 0.42) {
      //   this->tileIndex = 6;
      //   this->isGrass = true;
      // } else if(normalizedHeight < 0.56) {
      //   this->tileIndex = 7;
      //   this->isGrass = true;
      // } else if(normalizedHeight < 0.58) {
      //   this->tileIndex = 8;
      //   this->isGrass = true;
      // } else if(normalizedHeight < 0.6) {
      //   this->tileIndex = 9;
      //   this->isDirt = true;
      // } else if(normalizedHeight < 0.62) {
      //   this->tileIndex = 10;
      //   this->isDirt = true;
      // } else if(normalizedHeight < 0.66) {
      //   this->tileIndex = 11;
      //   this->isDirt = true;
      // } else if(normalizedHeight < 0.7) {
      //   this->tileIndex = 12;
      //   this->isMountain = true;
      // } else if(normalizedHeight < 0.72) {
      //   this->tileIndex = 13;
      //   this->isMountain = true;
      // } else if(normalizedHeight < 0.74) {
      //   this->tileIndex = 14;
      //   this->isMountain = true;
      // } else if(normalizedHeight < 0.76) {
      //   this->tileIndex = 15;
      //   this->isMountain = true;
      // } else if(normalizedHeight < 0.78) {
      //   this->tileIndex = 16;
      //   this->isMountain = true;
      // } else if(normalizedHeight < 0.8) {
      //   this->tileIndex = 17;
      //   this->isMountain = true;
      // } else if(normalizedHeight < 0.82) {
      //   this->tileIndex = 18;
      //   this->isMountain = true;
      // } else if(normalizedHeight < 0.84) {
      //   this->tileIndex = 19;
      //   this->isMountain = true;
      // } else {
      //   this->isMountain = true;
      //   this->tileIndex = 20;
      // }
			this->tileSprite = new Sprite(renderer, spritesheetTexture, 0, 0, 0, 32, 32);
			this->tileSprite->setPosX(posX);
			this->tileSprite->setPosY(posY);
      this->tileSprite->setOffset(this->tileIndex);
		}

    bool isWater;
    bool isSand;
    bool isGrass;
    bool isDirt;
    bool isMountain;

    void render() {
      this->tileSprite->render();
    }
};