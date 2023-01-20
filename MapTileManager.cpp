#include "SimplexNoise.h"
#include "MapTile.cpp"

class MapTileManager {
  private:
    SDL_Renderer* renderer;
    SDL_Texture* spritesheetTexture;
    int tileWidth;
    int tileHeight;
    int windowWidth;
    int windowHeight;
    std::vector<MapTile*> mapTiles;
  public:
    MapTileManager(
      SDL_Renderer* renderer,
      SDL_Texture* spritesheetTexture,
      int tileWidth,
      int tileHeight,
      int windowWidth,
      int windowHeight
    ) {
      this->renderer = renderer;
      this->spritesheetTexture = spritesheetTexture;
      this->tileWidth = tileWidth;
      this->tileHeight = tileHeight;
      this->windowWidth = windowWidth;
      this->windowHeight = windowHeight;
    }

    std::vector<MapTile*> copyTiles() {
      std::vector<MapTile*> copy;
      for (int i = 0; i < this->mapTiles.size(); i++) {
        copy.push_back(this->mapTiles[i]); 
      }
      return copy;
    }
    
    void generate(int seed) {
      SimplexNoise* noise = new SimplexNoise(0.6f, 1.0f, 2.0f, 0.5f);
      int maxNumTilesX = ceil(this->windowWidth / this->tileWidth) - 1;
      int maxNumTilesY = ceil(this->windowHeight / this->tileHeight * 2);
      for(int y = 0; y < maxNumTilesY; y++) {
        for(int x = 0; x < maxNumTilesX; x++) {
          int posX = x * tileWidth;
          int posY = y * tileHeight / 2;
          if(y % 2 == 0) { posX += tileWidth / 2; }
          float normalizedPosX = (float)x / (float)maxNumTilesX;
          float normalizedPosY = (float)y / (float)maxNumTilesY;
          float perlinVal = noise->fractal(4.0f, normalizedPosX + seed, normalizedPosY);
          float perlinValNorm = (perlinVal + 1) / 2;
          MapTile* tile = new MapTile(renderer, spritesheetTexture, posX, posY, perlinValNorm);
          mapTiles.push_back(tile);
        }
      }

      // int maxNumTilesX = ceil(this->windowWidth / this->tileWidth);
      // int maxNumTilesY = ceil(this->windowHeight / this->tileHeight * 2) + 1;
      // int totalNumTiles = 0;
      // SimplexNoise* noise = new SimplexNoise(0.3f, 1.0f, 2.0f, 0.5f);
      // for(int x = 0; x < maxNumTilesX; x++) {
      //     for(int y = 0; y < maxNumTilesY; y++) {
      //     int posX = x * tileWidth;
      //     int posY = y * tileHeight / 2;
      //     if((posY / tileHeight) % 2 == 1) { posX += tileWidth / 2; }
      //     float normalizedPosX = (float)x / (float)maxNumTilesX;
      //     float normalizedPosY = (float)y / (float)maxNumTilesY;
      //     float perlinVal = noise->fractal(4.0f, normalizedPosX + seed, normalizedPosY);
      //     float normalizedPerlinVal = (perlinVal + 1) / 2;
      //     MapTile* tile = new MapTile(renderer, spritesheetTexture, posX, posY, normalizedPerlinVal);
      //     mapTiles.push_back(tile);
      //   }
      // }
    }
    
    void render() {
      for (size_t i = 0; i < this->mapTiles.size(); ++i) {
        this->mapTiles[i]->render();
      }
    }
};
