#include "TextureComponent.h"
#include "Renderer.h"

TextureComponent::TextureComponent(std::string path) {
    renderer = Renderer::getRenderer();
    filePath = path;
    surface = SDL_LoadBMP(filePath.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    isSubTexture = false;
}

TextureComponent::~TextureComponent() {
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

SDL_Texture* TextureComponent::getTexture() {
    return texture;
}

void TextureComponent::setSubTexture(int x, int y, int w, int h) {
    isSubTexture = true;
    subTexture.x = x;
    subTexture.y = y;
    subTexture.h = h;
    subTexture.w = w;
}

SDL_Rect* TextureComponent::getSubTexture() {
    return &subTexture;
}

bool TextureComponent::getSubTextureStatus() { return isSubTexture; }
