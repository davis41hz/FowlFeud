/**
 * @brief Renderer class for rendering graphics.
 * Uses an SDL_renderer to render graphics.
 * @author David MacLean
 */
#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL.h>

class Renderer {
public:
    /** @brief Destructor.
     * Destroys the Renderer.
     */
    ~Renderer();
    /**
     * @brief Gets the instance.
     * Static method that gets the instance of the class renderer (SINGLETON PATTERN).
     * @param window :: the sdl_window to render things to.
     * @return the SDL_Renderer instance.
     */
    static Renderer& getInstance(SDL_Window* window);
    /**
     * @brief gets the SDL_Renderer.
     * Static method that gets the SDL_Renderer.
     * @return the associated SDL_Renderer*.
     */
    static SDL_Renderer* getRenderer();

private:
    /**
     * @brief Constructor.
     * Constructor that creates a Renderer.
     * @param window :: an SDL_window to render to.
     */
    Renderer(SDL_Window* window);
    /**
     * @brief Constructor.
     * Copy constructor that creates a Renderer (SINGLETON PATTERN).
     * @param other :: the renderer to be used.
     */
    Renderer(const Renderer& other) {}
    /**
     * @brief Constructor.
     * Copy constructor overload that creates a Renderer (SINGLETON PATTERN).
     * @param other :: the renderer to be used.
     */
    Renderer& operator=(const Renderer& other) {};
    /** the instance of the Renderer (SINGLETON PATTERN). */
    static Renderer* instance;
    /** the SDL_renderer to be used. */
    static SDL_Renderer* renderer;
};
#endif
