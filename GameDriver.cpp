#include "GameInstance.h"
#include <SDL2/SDL.h>
#include <iostream>
int main(int argc,char *argv[]) {
    const int FRAME_RATE = 15; // frame rate cap, isn't a minimum

    GameInstance* game = new GameInstance(atoi(argv[1]), atoi(argv[2]));

    if(game->startGame() < 0) {
        delete game;
        return -1;
    }

    Uint32 nextFrame = FRAME_RATE + SDL_GetTicks();
    Uint32 currentTicks;

    while(game->getStatus() == true) { // main game loop
        game->handleInput();
        game->updateGameObjects();
        game->renderGameObjects();

        // ensure all frames loaded faster than 1/60 of a second are delayed
        currentTicks = SDL_GetTicks();
        if(nextFrame > currentTicks) {
            SDL_Delay(nextFrame - currentTicks);
        }
        nextFrame = FRAME_RATE + SDL_GetTicks();
    }

    game->displayEndScreen();
    while(game->handleInput()); // waits for player to x window



    delete game;
    SDL_Quit();
    return 0;
}
