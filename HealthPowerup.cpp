#include "HealthPowerup.h"
#include <SDL2/SDL.h>

//HealthPowerup inherits from GameObject
HealthPowerup::HealthPowerup(int x, int y):PowerupGameObject(x,y, "textures/healthPowerupSprite.bmp", "healthPowerup") {}


HealthPowerup::~HealthPowerup() {}

void HealthPowerup::pickedUp(PlayerGameObject* player) {
    player->addHealth(HEAL);
    onDeath();
}
