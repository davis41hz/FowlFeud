/**
 * @brief Powerup creator.
 * Class that uses the factory method to create powerups.
 * @author David MacLean
 */

#ifndef POWERUP_FACTORY_H
#define POWERUP_FACTORY_H
#include "DamagePowerup.h"
#include "HealthPowerup.h"
#include <stdlib.h>

class PowerupFactory {
private:
    /**
     * @brief Contructor.
     * Creates the PowerupFactory object.
     */
    PowerupFactory();
    /**
     * @brief Destructor.
     * Destroys the PowerupFactory object.
     */
    ~PowerupFactory();
public:
    /**
     * @brief creating a powerup.
     * Static method that either randomly creates a health or damage powerup, or does nothing.
     * @param x, y :: representing the position of the powerup.
     */
    static void spawnPowerup(int x, int y) {
        srand(std::time(NULL));
        int chance = rand() % 3;
        switch (chance) {
            case 0:
                new DamagePowerup(x, y);
                break;
            case 1:
                new HealthPowerup(x, y);
                break;
            default:
                // do not spawn anything
                break;
        }
    }
};
#endif
