#include "PlayerGameObject.h"
#include "BoltGameObject.h"
#include "PowerupGameObject.h"
#include "GameInstance.h"
#include <algorithm>
#include <SDL2/SDL.h>
#include <iostream>
using namespace std;
PlayerGameObject::PlayerGameObject(int x, int y, int mHealth, int s, float aSpeed, std::string textureFile, int d, SDL_Keycode l, SDL_Keycode r, SDL_Keycode u, SDL_Keycode dwn, SDL_Keycode sht, int hudX, int hudY, int ctrlId): GameObject("player", x, y){
    this->maxHealth = mHealth;
    this->health = mHealth;
    this->speed = s;
    this->attackSpeed = aSpeed;
    this->score = 0;
    this->damage = d;
    this->baseDamage = d;
    this->hasDamageUp = false;
    this->left = l;
    this->right = r;
    this->up = u;
    this->down = dwn;
    this->shoot = sht;
    this->controllerId = ctrlId;
    this->lastAttack = std::chrono::high_resolution_clock::now();
    this->direction = new PositionVector(0,0);

    hud = new HUDGameObject(this->health,hudX,hudY);
    transform = (TransformComponent*)GameObject::getComponent(TransformComponent::getName());
    audio = new AudioComponent();
    GameObject::addComponent(AudioComponent::getName(), audio);
    texture = new TextureComponent(textureFile);
    GameObject::addComponent(TextureComponent::getName(), texture);
    collision = new CollisionComponent(transform->getRect());
    GameObject::addComponent(CollisionComponent::getName(), collision);
}

PlayerGameObject::~PlayerGameObject() {
    delete direction;
}

int PlayerGameObject::getMax() {
    return this->maxHealth;
}

int PlayerGameObject::getHealth() {
    return this->health;
}

void PlayerGameObject::addHealth(int amount) {
    int newHealth = this->health + amount;
    if (newHealth <= 0) {
        this->health = 0;
        onDeath();
    } else {
        if(newHealth > this->health) {
            audio->playSFX(healSound);
        }
        this->health = std::min(newHealth, this->maxHealth);
    }

    hud->setHealth(this->health);
}


void PlayerGameObject::setHealth(int newHealth) {
    this->health = newHealth;
    hud->setHealth(this->health);
}

void PlayerGameObject::onDeath(void) {
    this->exists = false;
}

void PlayerGameObject::setScore(int newScore) {
    this->score = newScore;
}

void PlayerGameObject::damagePowerup(int amount) {
    if(!hasDamageUp) {
        hasDamageUp = true;
        damage += amount;
        hud->hasPowerup(true);
    }
}

void PlayerGameObject::updateObject() {
    // rotate the player in the correct direction
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

    direction->multiply(this->speed); // apply speed to players movement
    transform->getPosition()->add(direction); // move player

    // check collsions
    collision->setCollisionArea(transform->getRect());
    for(GameObject* gameObject: currentGameObjects) {
        if(gameObject == this) { continue; }

        TransformComponent* otherTransform = (TransformComponent*) gameObject->getComponent(TransformComponent::getName());
        if(gameObject->getTag() == "wall" && collision->getCollision(otherTransform->getRect())) {
            transform->getPosition()->subtract(direction); // don't let player overlap walls
        } else if(gameObject->getTag() == "damagePowerup" && collision->getCollision(otherTransform->getRect()) && !this->hasDamageUp) {
            audio->playSFX(damageUpSound);
            ((PowerupGameObject*) gameObject)->pickedUp(this);
        } else if(gameObject->getTag() == "healthPowerup" && collision->getCollision(otherTransform->getRect())) {
            ((PowerupGameObject*) gameObject)->pickedUp(this);
        }
    }

    direction->divide(this->speed);
}

void PlayerGameObject::handleInput(SDL_Event keyEvent) {
    int keyStateModifier = 0; // holds the state of whether an input is intending motion or stopping motion

    // return if other player's control event
    if((keyEvent.type == SDL_CONTROLLERAXISMOTION && keyEvent.caxis.which != controllerId) || (keyEvent.type == SDL_CONTROLLERBUTTONDOWN && keyEvent.cbutton.which != controllerId)) { return; }

    // checks if motion is intended and defines the deadzones for controllers
    if(keyEvent.type == SDL_KEYDOWN || (keyEvent.type == SDL_CONTROLLERAXISMOTION && (keyEvent.caxis.value < -15000 || keyEvent.caxis.value > 15000))) { keyStateModifier = 1; }

    // input moving player left
    if (keyEvent.key.keysym.sym == left || (keyEvent.type == SDL_CONTROLLERAXISMOTION && keyEvent.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX && keyEvent.caxis.value <= 0)) {
        direction->setX(-1*keyStateModifier);
    }

    // input moving player down
    if (keyEvent.key.keysym.sym == down || (keyEvent.type == SDL_CONTROLLERAXISMOTION && keyEvent.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY && keyEvent.caxis.value >= 0)) {
        direction->setY(1*keyStateModifier);
    }

    // input moving player up
    if (keyEvent.key.keysym.sym == up || (keyEvent.type == SDL_CONTROLLERAXISMOTION && keyEvent.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY && keyEvent.caxis.value <= 0)) {
        direction->setY(-1*keyStateModifier);
    }

    // input moving player right
    if (keyEvent.key.keysym.sym == right || (keyEvent.type == SDL_CONTROLLERAXISMOTION && keyEvent.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX && keyEvent.caxis.value >= 0)) {
        direction->setX(1*keyStateModifier);
    }

    // check for shooting and if it is valid based on attackSpeed
    std::chrono::duration<double, std::milli> timeElapsed = std::chrono::high_resolution_clock::now() - lastAttack;
    if((((keyEvent.type == SDL_KEYDOWN && keyEvent.key.keysym.sym == shoot) || (keyEvent.type == SDL_CONTROLLERBUTTONDOWN && keyEvent.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) && timeElapsed.count() > attackSpeed)){
        audio->playSFX(bowShotSound);
        new BoltGameObject(transform->getPosition()->getX() + direction->getX(), transform->getPosition()->getY() + direction->getY(), damage, speed+1, transform->getRotation());
        if (hasDamageUp) {
            hasDamageUp = false;
            this->damage = this->baseDamage;
            hud->hasPowerup(false); // remove damage powerup if you shoot your arrow
        }
        lastAttack = std::chrono::high_resolution_clock::now(); // reset the last time you attacked
    }
}
