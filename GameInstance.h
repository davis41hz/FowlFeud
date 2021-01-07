/**
 *  @brief Handling of the game instance
 *  Starts game and handles input
 *  @author David MacLean
 */

#ifndef GAME_INSTANCE_H
#define GAME_INSTANCE_H
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "GameObject.h"
#include "PlayerGameObject.h"
#include "WallGameObject.h"
#include "EnemyGameObject.h"
#include "HealthPowerup.h"
#include "DamagePowerup.h"
#include "AudioSystem.h"

class GameInstance {
public:
    /**
     * @brief Constructor
     * Creates GameInstance
     * @param numPlayers :: integer of the number of players playing
     * @param gameType :: deciphers between regular game and hoarde mode
     */
    GameInstance(int numPlayers, int gameType);
    /**
     * @brief Destructor
     * Destroys GameInstance
     */
    ~GameInstance();
    /**
     * @brief Starts the game
     * Starts game by initiating AudioSystem, creates window, calls buildLevel() and initializes controllers
     */
    int startGame();
    /**
     * @brief Updates all objects in the game
     * Updates game objects
     * @return int :: returns 0 if successful
     */
    void updateGameObjects();
    /**
     * @brief Handles player input
     * Checks if player has closed window or if player is still alive
     */
    bool handleInput();
    /**
     * @brief Renders game objects
     * Renders the graphics of all objects in the game
     * @return bool :: returns true if successful
     */
    void renderGameObjects();
    /**
     * @brief Checks status of game
     * Returns the running status for the game
     * @return bool :: returns true if game is successfully running
     */
    bool getStatus();
    /**
     * @brief Displays end screen
     * Checks to see if player was victorious or not and displays end screen accordingly
     */
    void displayEndScreen();


private:
    /** Running status of the game */
    bool status;
    /**Number of players in the game*/
    int numPlayers;
    /** type of game you want to play 1 = normal 2 = horde **/
    int gameMode;
    /** how many hordes you have survived **/
    int hordeCount;
    /** are you victorious **/
    bool isVictorious;
    /** Game window from SDL */
    SDL_Window* window;
    /** Graphics renderer from SDL */
    SDL_Renderer* renderer;
    /** Constant for window size */
    const int dimension = 864;
    /** Constant for window name */
    const char* gameName = "Fowl Feud";
    /** Player controlled game object for user one*/
    PlayerGameObject* player;
    /** Player controlled game object for user two*/
    PlayerGameObject* player2;
    /** character pointer for image displayed when user is victorious */
    const char* WINSCREEN = "textures/winScreen.bmp";
    /** character pointer for image displayed when user looses */
    const char* LOSESCREEN = "textures/loseScreen.bmp";
    /** integer to keep track of the number of players who have been defeated by the geese */
    int playersDead;
    /** string containing file for background music */
    std::string backgroundMusicFile = "sounds/backgroundMusic.wav";
    /** string containing file containing soundeffect for when player is victorious */
    std::string winSound = "sounds/winSound.wav";
    /** string containing file containing soundeffect for when player looses */
    std::string loseSound = "sounds/loseSound.wav";
    /** pointer to background music */
    Mix_Music* backgroundMusic;
    /** integer that keeps track of currect level */
    int currentLevel;
    /** vector containing strings of file names for levels for player one mode */
    std::vector<std::string> onePlayerLevels{"levels/oneP1.lvl", "levels/twoP1.lvl","levels/bossP1.lvl"};
    /** vector containing strings of file names for levels for two player mode */
    std::vector<std::string> twoPlayerLevels{"levels/oneP2.lvl", "levels/twoP2.lvl","levels/bossP2.lvl"};
    /** pointer to controller one */
    SDL_GameController *controller;
    /** pointer to controller two */
    SDL_GameController* controller2;
    /**
     * @brief builds aspects of level
     * Builds players, enemies and obstables
     * @return bool
     */
    bool buildLevel();
    /**
     * @brief checks for next level
     * Deconstructs remenants of previous level and check for next level
     */
    void nextLevel();
};
#endif // GAME_INSTANCE_H
