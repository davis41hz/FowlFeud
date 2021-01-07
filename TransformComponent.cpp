#include "TransformComponent.h"


TransformComponent::TransformComponent(PositionVector* position, int rotation, int scale) {
  this->position = position;
  this->rotation = rotation;
  this->objectWidth = 32;
  this->objectHeight = 32;
  this->scale = scale;
}

TransformComponent::~TransformComponent() {
    delete position;
}

PositionVector* TransformComponent::getPosition() {
  return this->position;
}

void TransformComponent::setPosition(PositionVector* newPosition) {
  this->position->setX(newPosition->getX());
  this->position->setY(newPosition->getY());
}

int TransformComponent::getRotation() {
  return this->rotation;
}

void TransformComponent::setRotation(int newRotation) {
  this->rotation = newRotation;
}

int TransformComponent::getScale() {
  return this->scale;
}

void TransformComponent::setScale(int newScale) {
  this->scale = newScale;
}

void TransformComponent::setRectSize(int w, int h) {
    objectWidth = w;
    objectHeight = h;
}


SDL_Rect* TransformComponent::getRect() {
  srect.x = this->position->getX();
  srect.y = this->position->getY();
  srect.h = objectHeight;
  srect.w = objectWidth;
  return &srect;
}
