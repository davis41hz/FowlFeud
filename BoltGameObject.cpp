#include "EnemyGameObject.h"
#include "BoltGameObject.h"

BoltGameObject::BoltGameObject(int x, int y, int d, int s, int r): GameObject("bolt", x, y) {
    this->speed = s;
    this->damage = d;
    transform = (TransformComponent*)GameObject::getComponent(TransformComponent::getName());
    transform->setRotation(r);
    texture = new TextureComponent(textureFile);
    GameObject::addComponent(TextureComponent::getName(), texture);
    collision = new CollisionComponent(transform->getRect());
    GameObject::addComponent(CollisionComponent::getName(), collision);

    switch (r) { // set direction of arrow based on rotation
        case 0:
            direction = new PositionVector(0,-1);
            break;
        case 45:
            direction = new PositionVector(1,-1);
            break;
        case 90:
            direction = new PositionVector(1,0);
            break;
        case 135:
            direction = new PositionVector(1,1);
            break;
        case 180:
            direction = new PositionVector(0,1);
            break;
        case 225:
            direction = new PositionVector(-1,1);
            break;
        case 270:
            direction = new PositionVector(-1,0);
            break;
        case 315:
            direction = new PositionVector(-1,-1);
            break;
        default:
            direction = new PositionVector(0,-1);
            break;

    }
    direction->multiply(this->speed); // speed is constant so it can be applied here
}

BoltGameObject::~BoltGameObject() {
    delete direction;
}

void BoltGameObject::updateObject() {
    transform->getPosition()->add(direction); // move the bolt

    // check collisions
    collision->setCollisionArea(transform->getRect());
    for(GameObject* gameObject: currentGameObjects) {
        if(gameObject == this || gameObject->getTag() == "player") { continue; } // bolts will ignore players

        TransformComponent* otherTransform = (TransformComponent*) gameObject->getComponent(TransformComponent::getName());
        if(collision->getCollision(otherTransform->getRect())) {
            if(gameObject->getTag() == "enemy") {
                ((EnemyGameObject*)gameObject)->takeDamage(this->damage);
                onDeath();
            }
            if((gameObject->getTag() == "wall")){
                onDeath();
            }

        }
    }
}

void BoltGameObject::onDeath() {
    this->exists = false;
}
