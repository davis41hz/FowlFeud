/**
 * @brief Class representing the projectile which players shoot.
 * 	Inherits from GameObject
 *
 * @author David MacLean
 */

#ifndef BOLT_GAME_OBJECT_H
#define BOLT_GAME_OBJECT_H
#include <SDL2/SDL.h>
#include <string>
#include "GameObject.h"
//#include "HUDGameObject.h"

class  BoltGameObject : public GameObject {
private:
	/** Texture of bolt game obbject */
    std::string textureFile = "./textures/boltSprite.bmp";

    /** Damage of bolt */
    int damage;

    /** Speed of bolt */
    int speed;

    /**
     * @brief private function which destroys the bolt
     */
    void onDeath();

    /** Transformer component for player*/
    TransformComponent* transform;

    /** Texture Component for player*/
    TextureComponent* texture;

    /** Collision Component for player */
    CollisionComponent* collision;

    /** Position Vector for player */
    PositionVector* direction;
public:
    /**
     * @brief Constructor
     * Creates BoltGameObject
     * @param x,y :: Coordinates
     * @param d :: Damage of bolt
     * @param s :: Speed of bolt
     * @param r :: Rotation of bolt
     */
    BoltGameObject(int x, int y, int d, int s, int r);
    /**
     * @brief Destructor
     * Destroys BoltGameObject
     */
    ~BoltGameObject();

    /**
     * @brief Updates BoltGameObject
     * Updates the BoltGameObject every frame
     */
    void updateObject();
};
#endif
