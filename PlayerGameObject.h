/**
 * @brief Player object in the game
 * Represents the player object in the game.
 * @author David MacLean
 */
#ifndef PLAYER_GAME_OBJECT_H
#define PLAYER_GAME_OBJECT_H
#include <SDL2/SDL.h>
#include "GameObject.h"
#include "HUDGameObject.h"
#include <chrono>
//#include "HUDGameObject.h"

class  PlayerGameObject : public GameObject {
private:
    /** maximum player health*/
    int maxHealth;
    /** current player health*/
    int health;
    /** speed of player*/
    int speed;
    /** attack speed of player*/
    float attackSpeed;
    /** score player has accumulated */
    int score;
    /** amount of damage inflicted on player */
    int damage;
    /** base damage on player */
    int baseDamage;
    /** time of last attack */
    std::chrono::high_resolution_clock::time_point lastAttack;
    /** checks to see if has powerDamageUp */
    bool hasDamageUp;
    /** keyboard control for left */
    SDL_Keycode left;
    /** keyboard control for right */
    SDL_Keycode right;
    /** keyboard control for up */
    SDL_Keycode up;
    /** keyboard control for down */
    SDL_Keycode down;
    /** keyboard control for shooting */
    SDL_Keycode shoot;

    // HUD hud;
    /**
     * @brief when player dies
     * when the player dies, to be determined
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
    /** Pointer to HUD GameObject */
    HUDGameObject* hud;
    /** Pointer to AudioComponent */
    AudioComponent* audio;
    /** String for file containing bow shot sound */
    std::string bowShotSound = "sounds/bow.wav";
    /** String for file containing damage up sound */
    std::string damageUpSound = "sounds/damageUp.wav";
    /** String for file containing health sound */
    std::string healSound = "sounds/heal.wav";
    /** Controller ID */
    int controllerId;


public:
    /**
     * @brief Constructor
     * Creates PlayerGameObject
     * @param x,y :: coordinates for player object
     * @param maxHealth :: maximum health the player can attain
     * @param s :: the speed in which the player can travel
     * @param aSpeed :: the speed in which the player can attack
     * @param textureFile :: location of the textureFile
     * @param d :: damage
     * @param l :: left key
     * @param r :: right key
     * @param u :: up key
     * @param dwn :: down key
     * @param sht :: shoot key
     * @param hudX :: x coordinate for HUD
     * @param hudY :: y coordinate for HUD
     * @param ctrlID :: Controller ID for player one or player two
     */
    PlayerGameObject(int x, int y, int maxHealth, int s, float aSpeed, std::string textureFile, int d,SDL_Keycode l, SDL_Keycode r, SDL_Keycode u, SDL_Keycode dwn, SDL_Keycode sht, int hudX, int hudY, int ctrlID);
    /**
     * @brief Destructor
     * Destroys PlayerGameObject
     */
    ~PlayerGameObject();
    /**
     * @brief Gets maximum health of player
     * Gets the max health of the PlayerGameObject
     * @return health :: int of max health.
     */
    int getMax();
    /**
     * @brief Gets the health of player
     * Gets the current health of the PlayerGameObject
     * @return health :: int of current health
     */
    int getHealth();
    /**
     * @brief Sets health
     * Sets the health of the playerGameObject
     * @param newHealth :: the int new health of the playerGameObject
     */
    void setHealth(int newHealth);
    /**
     * @brief Increases player health
     * Increases the players health by given amount
     * @param amount :: the amount to increase the players health by
     */
    void addHealth(int amount);
    /**
     * @brief sets score
     * Sets the score of the player
     * @param newScore :: the new score to be set for the player
     */
    void setScore(int newScore);
    /**
     * @brief Updates objects
     * Updates the objects entities
     */
    void updateObject();
    /**
     * @brief Handles player input
     * Handles the input from the keyboard to control the player
     * @param keyDown :: an SDL_event when they key is pressed down
     */
    void handleInput(SDL_Event keyDown);
    /**
     * @brief Gives amount of damage inflicted
     * Check for DamagePowerup the applies it to damage
     * @param amount :: int for amount of damage inflicted
     */
    void damagePowerup(int amount);
};
#endif
