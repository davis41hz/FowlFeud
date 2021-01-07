/**
 * @brief Displays the HUD for a player
 * Object to display the HUD for a player.
 * @author David MacLean
 */

#ifndef HUD_GAME_OBJECT_H
#define HUD_GAME_OBJECT_H
#include "GameObject.h"
#include <SDL2/SDL.h>
#include <string>

class HUDGameObject : public GameObject {
private:
    /** Location of the texture file. */
    std::string textureFile = "./textures/hudSprite.bmp";
    /** Amount of health being displayed. */
    int health;
    /** X Relative coordinate of the health bar */
    int xPos = 0;
    /** Y Relative coordinate of the health bar. */
    int yPos = 0;
    /** Width of the health bar. */
    int healthBarWidth = 128;
    /** Height of the health bar. */
    int healthBarHeight = 12;
    /** Width of the powerup icon. */
    int powerupWidth = 24;
    /** X coordinate of the HUD. */
    int globalX;
    /** Maximum amount of health. */
    int maxHealth;
    /** Status indicating whether a powerup is active. */
    bool powerupState;
    /** Transform Component for a player */
    TransformComponent* transform;
    /** Texture Component for player. */
    TextureComponent* texture;

public:
    /**
     * @brief Constructor.
     * @param h :: representing the health of the player.
     * @param x, y :: representing the position of the HUD.
     */
    HUDGameObject(int h, int x, int y);
    /**
     * @brief Destructor
     * Destroys HUDGameObject
     */
    ~HUDGameObject();
    /**
     * @brief Updates objects
     * Updates objects, inherited virtual method.
     */
    void updateObject();
    /**
     * @brief Sets health 
     * Sets the health displayed in the HUD.
     * @param h :: representing the new health to be displayed.
     */
    void setHealth(int h);
    /**
     * @brief Updates HUD
     * Updates the HUD.
     */
    void updateHUD();
    /**
     * @brief Sets the status of powerup in the HUD.
     * Checks to see if player has a power up in the HUD
     * @param state :: representing the new state of powerup.
     */
    void hasPowerup(bool state);
};
#endif
