/**
 * @brief AudioSystem
 * AudioSystem lends methods to AudioComponent
 * @author David MacLean
 */

#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#include <SDL2/SDL_mixer.h>
#include <string>

class AudioSystem {
public:
    /**
     * @brief Deconstructor.
     * Destroys AudioSystem.
     */
    ~AudioSystem();
    /**
     * @brief Getter for AudioSystem
     * Gets instance of AudioSystem
     * @return a reference of AudioSystem
     */
    static AudioSystem& getInstance();
    /**
     * @brief Method that plays background music
     * Plays the background music on loop
     * @param song :: a pointer to the music to be played
     * @param timesThrough :: the number of times to loop the song
     */
    void playMusic(Mix_Music* song, int timesThrough);
    /**
     * @brief Method that plays sound effects
     * Plays sound effects passed to it
     * @param fileName :: string with the file with the desired sound effect
     * @param timesThrough :: the number of times to play the sound effect
     */
    void playSoundEffect(std::string fileName, int timesThrough);
    /**
     * @brief Method that fades music
     * Allows for gradual closer of music
     * @param time :: the amount of time fade occurs over
     */
    void fadeOutMusic(int time);
private:
    /**
     * @brief Constructor
     * Creates the AudioSystem
     */
    AudioSystem();
    /**
     * @brief Constructor
     * Creates the AudioSystem with parameters attached
     * @param other :: a constant reference of AudioSystem
     */
    AudioSystem(const AudioSystem& other) {}
    /**
     * @brief maintains singleton integrity
     * Overloads operator to prevent copying
     * @param other :: a constant reference of AudioSystem
     * @return a reference to AudioSystem
     */
    AudioSystem& operator=(const AudioSystem& other) {}
    /** @brief pointer to AudioSystem */
    static AudioSystem* instance;
};
#endif
