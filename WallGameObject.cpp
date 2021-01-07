#include "WallGameObject.h"

WallGameObject::WallGameObject(int x,int y): GameObject("wall", x, y){
    GameObject::addComponent(TextureComponent::getName(), new TextureComponent(textureFile));
}
WallGameObject::~WallGameObject(){}
void WallGameObject::updateObject(){}
