#include "PowerupGameObject.h"
#include <SDL2/SDL.h>

//PowerupGameObject inherits from GameObject
PowerupGameObject::PowerupGameObject(int x, int y, std::string textFile, std::string nameTag):GameObject(nameTag, x, y)
{
    transform = (TransformComponent*)GameObject::getComponent(TransformComponent::getName());
    texture = new TextureComponent(textFile);
    GameObject::addComponent(TextureComponent::getName(), texture);
    collision = new CollisionComponent(transform->getRect());
    GameObject::addComponent(CollisionComponent::getName(), collision);
}


PowerupGameObject::~PowerupGameObject() {}

void PowerupGameObject::updateObject() {}

void PowerupGameObject::onDeath() {
    this->exists = false;
}
