#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "SimplexNoise.h"
#include "MapTileManager.cpp"
#include "Text.cpp"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define FPS 60

void limitMaxFPS(Uint32 startingTick) {
  // Limit the maximum frames per second.
  if((1000 / FPS) > SDL_GetTicks() - startingTick) {
    SDL_Delay((1000 / FPS) - (SDL_GetTicks() - startingTick));
  }
}

void clearScreen(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
  SDL_RenderClear(renderer);
}

int random(int min, int max) {
   static bool first = true;
   if (first) 
   {  
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}


int main(int argc, char *argv[])
{
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_RenderClear(renderer);
  std::cout << "Starting application." << std::endl;

  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "Failed to initialize SDL." << std::endl << SDL_GetError() << std::endl;
  }

  if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS, &window, &renderer)) {
    std::cerr << "Failed to initialize window." << std::endl << SDL_GetError() << std::endl;
  }

  Uint32 mapSeed = random(0, 131072);
  std::cout << "Using seed " << mapSeed << std::endl;
  std::stringstream sstream;
  sstream << "0x" << std::hex << mapSeed;
  std::string mapSeedString = sstream.str();

  SDL_Texture* mapTileSpritesheetTexture = IMG_LoadTexture(renderer, "/home/user/game/images/tiles2.png");
  SDL_Texture* cursorTexture = IMG_LoadTexture(renderer, "/home/user/game/images/cursor.png");
  SDL_Texture* spotlightTexture = IMG_LoadTexture(renderer, "/home/user/game/images/cursor2.png");
  Sprite* cursorSprite = new Sprite(renderer, cursorTexture, 32, 32, 0, 32, 32);
  Sprite* spotlightSprite = new Sprite(renderer, spotlightTexture, 32, 96, 0, 32, 96);
  Text* loamText = new Text(renderer, "Map Generation Test", 64, 1);

  SDL_SetWindowBordered(window, SDL_FALSE);
  SDL_SetWindowResizable(window, SDL_FALSE);
  SDL_RenderPresent(renderer);
  SDL_ShowCursor(SDL_DISABLE);


  MapTileManager* mapTileManager = new MapTileManager(
    renderer, mapTileSpritesheetTexture, 32, 32, WINDOW_WIDTH, WINDOW_HEIGHT);
  mapTileManager->generate(mapSeed);


  //SDL_Surface *screen = SDL_GetWindowSurface(window);
  //Uint32 white = SDL_MapRGB(screen->format, 255, 255, 255);

  SDL_Event event;
  Uint32 startingTick;
  bool isRunning = true;

  float timeOfDay = 0.0f;
  float timeOfDayMax = 24.0f;
  float timeOfDaySpeed = 0.05f;

  std::cout << "Starting main event loop." << std::endl;
  while(isRunning) {
    startingTick = SDL_GetTicks(); // Number of milliseconds since SDL initialized.
    int mouseX, mouseY;
    clearScreen(renderer);
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        isRunning = false;
        break;
      }
      if(event.type == SDL_KEYDOWN) {
        mapSeed = random(0, 131072);
      }
      if(event.type == SDL_MOUSEMOTION) {
        mouseX = event.motion.x;
        mouseY = event.motion.y;
      }
    }

    float tempTimeOfDay = timeOfDay + timeOfDaySpeed;
    if(tempTimeOfDay > timeOfDayMax) { tempTimeOfDay = 0.0f; }
    timeOfDay = tempTimeOfDay;

    float timeOfDayZeroToOne = timeOfDay / 24;
    float brightness = timeOfDayZeroToOne * 255;


    //mapTileManager->generate(mapSeed);
    mapTileManager->render();


    loamText->render(32, 16);

    cursorSprite->setPosX(mouseX);
    cursorSprite->setPosY(mouseY);
    std::cout << mouseY << std::endl;
    //cursorSprite->render();

    spotlightSprite->setPosX(floor(mouseX / 32) * 32);
    spotlightSprite->setPosY(floor(mouseY / 32) * 32 + 4);
    spotlightSprite->render();

    SDL_RenderPresent(renderer);
    limitMaxFPS(startingTick);
  }

  std::cout << "~ Performing teardown." << std::endl;


  if(renderer) { SDL_DestroyRenderer(renderer); }
  if(window) { SDL_DestroyWindow(window); }
  SDL_Quit();
  std::cout << "~ Exiting." << std::endl;
}