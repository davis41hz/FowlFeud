/**
 * @brief Powerups.
 * GameObjects representing powerups.
 * @author David MacLean
 */

#ifndef POWERUP_GAMEOBJECT_H
#define POWERUP_GAMEOBJECT_H
#include "GameObject.h"
#include <SDL2/SDL.h>
#include "PlayerGameObject.h"

class PowerupGameObject: public GameObject {
protected:
    /** Texture component for powerup. */
    TextureComponent* texture;
    /** Collision component for powerup. */
    TransformComponent* transform;
    /** Collision component for powerup. */
    CollisionComponent* collision;
    /**
     * @brief When the object is destroyed.
     * Function for when the powerup is destroyed.
     */
    void onDeath();
public:
    /**
     * @brief Constructor.
     * Constructor that creates the PowerupGameObject.
     * @param x, y :: coordinates for powerup object.
     * @param textFile :: the location of the textureFile.
     * @param nameTag :: the string name of the powerup object.
     */
     PowerupGameObject(int x, int y, std::string textFile, std::string nameTag);
     /**
      * @brief Destructor.
      * Destroys the PowerupGameObject.
      */
     ~PowerupGameObject();
     /**
      * @brief updates the object.
      * Inherited virtual method from GameObject.
      */
     void updateObject();
     /**
      * @brief Virtual method of the powerup being picked up.
      * Pure virtual member that adds effects when powerup is picked up.
      * @param player :: a pointer to the player object.
      */
     virtual void pickedUp(PlayerGameObject* player) = 0;

};
#endif
