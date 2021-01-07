/**
 * @brief Represents a wall in the game.
 * Subclass of GameObject that is used to create boundaries and prevent player pathing.
 * @author David MacLean
 */
#include <SDL2/SDL.h>
#include "GameObject.h"

class WallGameObject : public GameObject {
public:
    /**
     * @brief Constructor.
     * Creates the WallGameObject.
     * @param x,y :: coordinates of object.
     */
	WallGameObject(int x, int y);
    /**
     * @brief Destructor.
     * Destroys the WallGameObject.
     */
	~WallGameObject();
    /**
     * @brief Updates the objects information.
     * Inherited virtual method from GameObject.
     */
	void updateObject();

private:
	/** Location of the texture file */
	std::string textureFile = "textures/wall.bmp";
};
