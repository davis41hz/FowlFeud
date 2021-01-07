/**
 * @brief TextureComponent of an object.
 * Gives the SDL_Rect a SDL_Texture for rendering.
 * @author David MacLean
 */
#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H
#include <SDL2/SDL.h>
#include <string>
#include "Component.h"

class TextureComponent: public Component {
public:
    /**
     * @brief Constructor
     * Creates the TextureComponent.
     * @param path :: string of file.
     */
    TextureComponent(std::string path);
    /**
     * @brief Destructor.
     * Destroys the TextureComponent.
     */
    ~TextureComponent();
    /**
     * @brief Gets the texture of the component.
     * Returns the SDL_Texture* that belongs to this component.
     * @return the SDL_Texture* of the component's texture.
     */
    SDL_Texture* getTexture();
    /**
     * @brief sets the subtexture of the component.
     * Sets the position, width, and height of the texture and sets its status to subtexture.
     * @param x, y :: the new position.
     * @param w :: the new width.
     * @param h :: the new height.
     */
    void setSubTexture(int x, int y, int w, int h);
    /**
     * @brief gets the subtexture of the component.
     * Returns the SDL_Rect* of the subtexture component.
     * @return the SDL_Rect* of the component.
     */
    SDL_Rect* getSubTexture();
    /**
     * @brief gets the subtexture status of the component.
     * Returns whether or not the component is a subtexture.
     * @return the bool status of the component's subtexture status.
     */
    bool getSubTextureStatus();
    /**
     * @brief gets the name of this component.
     * Returns the type name of this component - "texture".
     * @return the string name of this class - "texture".
     */
    static std::string getName() { return std::string("texture"); }
private:
    /** path of the file. */
    std::string filePath;
    /** texture of the rect. */
    SDL_Texture* texture;
    /** surface of the rect. */
    SDL_Surface* surface;
    /** renderer for the object. */
    SDL_Renderer* renderer;
    /** sprite matrix. */
    int animations;
    /** sprite matrix. */
    int frames;
    /** dimension of object. */
    int dimension;
    /** SDL_Rect that is the frame. */
    SDL_Rect frame;
    /** SDL_Rect that is the subtexture. */
    SDL_Rect subTexture;
    /** status of the subtexture. */
    bool isSubTexture;
};
#endif
