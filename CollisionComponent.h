 /**
  * @brief Class that handles collisions
  * Class the represents Collisions and inherits from Component
  * @author David MacLean
  */
#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H
#include <SDL2/SDL.h>
#include<vector>
#include "Component.h"

class CollisionComponent: public Component {
public:
	/**
	 * @brief Constructor
	 * Creates CollisionComponent
	 * @param area :: pointer to a SDL rectangle which represents the collision area of an object
	 */
	CollisionComponent(SDL_Rect* area);

	/**
	 * @brief Checks for collision
	 * Checks if the collisionArea of the calling object interects with the collision area of another object
	 * @param otherCollisionArea :: a pointer to a SDL rectangle representing the collision area of another object
	 * @return true if the two objects intersect
	 * @return false otherwise
	 */
	bool getCollision(SDL_Rect * otherCollisionArea);

	/**
	 * @brief Sets collision area
	 * Sets the collsionArea of the calling object
	 * @param area :: a pointer to an SDL rectangle representing the new collsionArea
	 */
	void setCollisionArea(SDL_Rect * area);

	/**
	 * @brief Returns tag name
	 * Returns the tag name collision
	 * @return "collision"
	 */
	static std::string getName() { return std::string("collision"); }
private:
	/** Collision area of game object */
	SDL_Rect* collisionArea;
};
#endif
