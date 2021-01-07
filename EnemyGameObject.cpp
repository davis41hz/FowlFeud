#include "EnemyGameObject.h"
#include "PowerupFactory.h"
#include <SDL2/SDL.h>

//EnemyGameObject inherits from GameObject
EnemyGameObject::EnemyGameObject(int x, int y, int h, int s, int d, float as, std::string textFile, PlayerGameObject* p):GameObject("enemy", x, y) {
    this->transform = (TransformComponent*) GameObject::getComponent(TransformComponent::getName());
    texture = new TextureComponent(textFile);
    GameObject::addComponent(TextureComponent::getName(), texture);
    this->collision = new CollisionComponent(transform->getRect());
    GameObject::addComponent(CollisionComponent::getName(), collision);
    this->audio = new AudioComponent();
    GameObject::addComponent(AudioComponent::getName(), audio);

    this->health = h;
    this->speed = s;
    this->damage = d;
    this->attackSpeed = as;
    this->direction = new PositionVector(0, 0);
    this->player = p;
    this->lastAttack = std::chrono::high_resolution_clock::now();;
}

EnemyGameObject::~EnemyGameObject() {
    delete direction;
}

int EnemyGameObject::getHealth() {
    return this->health;
}

void EnemyGameObject::takeDamage(int amount) {
  this->health -= amount;
  if (this->health <= 0) {
    this->health = 0;
    onDeath();
  }
}

void EnemyGameObject::findNewTarget() {
    for(GameObject* gameObject: currentGameObjects) {
        if(gameObject->getTag() == "player") {
            this->player = (PlayerGameObject*)gameObject;
            break;
        }
    }
}

void EnemyGameObject::setHealth(int h) {
    this->health = h;
}

void EnemyGameObject::onDeath() {
    audio->playSFX(deathSound);
    PowerupFactory::spawnPowerup(transform->getPosition()->getX(), transform->getPosition()->getY());
    this->exists = false;
}

void EnemyGameObject::updateObject() {
    if(player->getHealth() == NULL) { // when one player dies in a two player game
        findNewTarget();
    }

    // set the direction towards the player
    direction->setX(((TransformComponent*)player->getComponent("transform"))->getPosition()->getX() - transform->getPosition()->getX());
    direction->setY(((TransformComponent*)player->getComponent("transform"))->getPosition()->getY() - transform->getPosition()->getY());

    // make the direction components have a maximum magnitude of 1
    if(direction->getX() > 0) { direction->setX(1); }
    else if(direction->getX() < 0) { direction->setX(-1); }

    if(direction->getY() > 0) { direction->setY(1); }
    else if(direction->getY() < 0) { direction->setY(-1); }


    // adjust rotation based on direction
    if(direction->getX() == 1 && direction->getY() == -1) {
        transform->setRotation(45);
    } else if (direction->getX() == 1 && direction->getY() == 1) {
        transform->setRotation(135);
    } else if (direction->getX() == -1 && direction->getY() == 1) {
        transform->setRotation(225);
    } else if (direction->getX() == -1 && direction->getY() == -1) {
        transform->setRotation(315);
    } else if(direction->getX() == 1) {
        transform->setRotation(90);
    } else if(direction->getX() == -1) {
        transform->setRotation(270);
    } else if(direction->getY() == 1) {
        transform->setRotation(180);
    } else if(direction->getY() == -1) {
        transform->setRotation(0);
    }

    transform->getPosition()->add(direction); // move enemy

    // check collisions
    collision->setCollisionArea(transform->getRect());
    for(GameObject* gameObject: currentGameObjects) {
        if(gameObject == this) { continue; }

        TransformComponent* otherTransform = (TransformComponent*) gameObject->getComponent(TransformComponent::getName());
        if(gameObject->getTag() == "enemy" && collision->getCollision(otherTransform->getRect())) {
            transform->getPosition()->subtract(direction); // don't allow enemies to overlap with other enemies
        } else if(gameObject == player && collision->getCollision(otherTransform->getRect())) {
            transform->getPosition()->subtract(direction); // don't allow player and enemy to overlap
            attack();
        }
    }
}

void EnemyGameObject::attack(){
    std::chrono::duration<double, std::milli> timeElapsed = std::chrono::high_resolution_clock::now() - lastAttack;
    if(timeElapsed.count() > attackSpeed) {
        audio->playSFX(wingHitSound);
        player->addHealth(-1*damage);
        lastAttack = std::chrono::high_resolution_clock::now();
    }
}
