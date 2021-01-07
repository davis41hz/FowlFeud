/**
 * @brief  AudioComponent for GameObjects
 * Class representing the Audio Component of Game Objects. Inherits from AudioSystem
 * @author David MacLean
 */

#ifndef AUDIO_COMPONENT_H
#define AUDIO_COMPNOENT_H
#include <SDL2/SDL.h>
#include <string>
#include "Component.h"
#include "AudioSystem.h"

class AudioComponent: public Component {
public:

	/**
	 * @brief Constructor
	 * Creates AudioComponent
	 */
    AudioComponent();
    /**
     * @brief Deconstructor
     * Destroys AudioComponent
     */
    ~AudioComponent();

    /**
     * @brief Returns tag name
     * Returns the tag name audio
     * @return the word "audio"
     */
    static std::string getName() { return std::string("audio"); }
    /**
     * @brief Plays sound effect
     * Plays the sound effect of a given file
     * @param fileName :: the file given to play certain sound effects
     */
    void playSFX(std::string fileName);
private:
    /**end sound of the game*/
    Mix_Chunk* lastSound;
};
#endif
