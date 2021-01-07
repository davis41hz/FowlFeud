#include "Renderer.h"

Renderer* Renderer::instance = NULL;
SDL_Renderer* Renderer::renderer = NULL;

Renderer& Renderer::getInstance(SDL_Window* window) {
    if(instance == NULL) {
        instance = new Renderer(window);
    }
    return *instance;
}

SDL_Renderer* Renderer::getRenderer() {
    if (instance == NULL) {
        return NULL;
    }
    return renderer;
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
}

Renderer::Renderer(SDL_Window* window) {
    renderer = SDL_CreateRenderer(window, -1, 0);
}
