#include "DamagePowerup.h"
#include <SDL2/SDL.h>

DamagePowerup::DamagePowerup(int x, int y): PowerupGameObject(x, y, "textures/damagePowerupSprite.bmp", "damagePowerup") {}

DamagePowerup::~DamagePowerup() {}

void DamagePowerup::pickedUp(PlayerGameObject* player) {
    player->damagePowerup(DAMAGEUP);
    onDeath();
}
