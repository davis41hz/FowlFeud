/**
 * @brief Class for health power ups
 * Represents health restoring powerups in the game.
 * @author David MacLean
 */
#ifndef HEALTH_POWERUP_H
#define HEALTH_POWERUP_H
#include "PowerupGameObject.h"
#include <SDL2/SDL.h>
#include "PlayerGameObject.h"

class HealthPowerup: public PowerupGameObject {
private:
    /** Amount healed. */
    const int HEAL = 50;
public:
    /**
     * @brief Constructor
     * Creates HealthPowerup
     * @param x, y :: coordinates for powerup objects
     */
     HealthPowerup(int x, int y);
     /**
      * @brief Destructor
      * Destroys HealthPowerup
      */
     ~HealthPowerup();
     /**
      * @brief Restores health to player
      * Inherited virtual method that restores health to the player.
      * @param player :: a pointer to the player game object.
      */
     void pickedUp(PlayerGameObject* player);

};
#endif
