#include "GameObject.h"

std::vector<GameObject*> GameObject::currentGameObjects; // simulating static inline for pre c++17

GameObject::GameObject(std::string nametag, int x, int y){
    currentGameObjects.push_back(this);
    renderer = Renderer::getRenderer();
    this->tag = nametag;
    PositionVector* position = new PositionVector(x, y);
    TransformComponent* transform = new TransformComponent(position, 0, 1);
    addComponent(TransformComponent::getName(), transform);
    exists = true;
}

GameObject::~GameObject() {}


void GameObject::renderGraphics(){
    if(component_map.count(TextureComponent::getName()) <= 0) { return; } // don't render gameobjects without texture components

    TextureComponent* texture  = (TextureComponent*) getComponent(TextureComponent::getName());
    TransformComponent* position = (TransformComponent*) getComponent(TransformComponent::getName());
    if(!texture->getSubTextureStatus()) { // when the gameobject uses a subsection of the texture at one time.
        SDL_RenderCopyEx(renderer, texture->getTexture(), NULL, position->getRect(), position->getRotation(), NULL, SDL_FLIP_NONE);
    } else {
        SDL_RenderCopyEx(renderer, texture->getTexture(), texture->getSubTexture(), position->getRect(), position->getRotation(), NULL, SDL_FLIP_NONE);
    }

}


void GameObject::addComponent(std::string type, Component* component){
    if(component_map.count(type) > 0) { return; }
    component_map.insert(std::pair<std::string, Component*>(type, component));
}

Component* GameObject::getComponent(std::string type){
    if(component_map.count(type) <= 0) { return NULL; }
    return component_map[type];
}

std::string GameObject::getTag(){
    return tag;
}

GameObject* GameObject::clean(){
    std::map<std::string, Component*>::iterator next;
    // clean up all the components
    for (next = component_map.begin(); next != component_map.end(); next++) {
        delete next->second;
    }
    removeFromList(); // maintain the gameobject list
    return this;
}

void GameObject::removeFromList() {
    for(int i = 0; i < currentGameObjects.size(); i++){
        if(currentGameObjects[i] == this) {
            currentGameObjects.erase(currentGameObjects.begin() + i);
            break;
        }
    }
}

bool GameObject::getExistence(){ return exists; }
