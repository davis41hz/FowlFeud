#include "HUDGameObject.h"
#include <math.h>

HUDGameObject::HUDGameObject(int h, int x, int y):GameObject("hud", x, y){
    this->health = h;
    this->maxHealth = h;
    this->globalX = x;
    this->powerupState = false;
    transform = (TransformComponent*)GameObject::getComponent(TransformComponent::getName());
    texture = new TextureComponent(textureFile);
    GameObject::addComponent(TextureComponent::getName(), texture);
    updateHUD();
}

HUDGameObject::~HUDGameObject(){
    this->exists = false;
}

void HUDGameObject::updateObject(){}

void HUDGameObject::hasPowerup(bool state) {
    this->powerupState = state;
    updateHUD();
}

void HUDGameObject::setHealth(int h){
    this->health = h;
    updateHUD();
}

void HUDGameObject::updateHUD() {
    float healthRatio = (float)this->health/(float)this->maxHealth;
    if(this->powerupState) {
        texture->setSubTexture(xPos, yPos, ceil(healthBarWidth*healthRatio) + powerupWidth, healthBarHeight);
        transform->getPosition()->setX(globalX); // the whole hud moves over as the width of the texture increases so that it appears to not move
        transform->setRectSize(ceil(healthBarWidth*healthRatio) + powerupWidth, healthBarHeight);
    } else {
        texture->setSubTexture(xPos+powerupWidth, yPos, ceil(healthBarWidth*healthRatio), healthBarHeight);
        transform->getPosition()->setX(globalX + powerupWidth); // the whole hud moves over as the width of the texture increases so that it appears to not move
        transform->setRectSize(ceil(healthBarWidth*healthRatio), healthBarHeight);
    }

}
