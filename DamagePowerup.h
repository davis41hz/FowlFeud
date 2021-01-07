/**
 * @brief Class representing damage increasing powerups in the game.
 * Inherits from PowerupGameObject
 * @author David MacLean
 */
#ifndef DAMAGE_POWERUP_H
#define DAMAGE_POWERUP_H
#include "PowerupGameObject.h"
#include "PlayerGameObject.h"

class DamagePowerup: public PowerupGameObject {
private:
	/** Damage increase variable for powerup
    **/
    const int DAMAGEUP = 60;
public:
    /**
     * Constructor
     * @param x, y :: coordinates for powerup object
     */
     DamagePowerup(int x, int y);
     /**
      * Deconstructor
      */
     ~DamagePowerup();
     /**
      * @brief Applies Damage powerup to the PlayerGameObject colliding with it
      * @param player :: a pointer to a player
      */
     void pickedUp(PlayerGameObject* player);
};
#endif
