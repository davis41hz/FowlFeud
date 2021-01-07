/**
 * @brief Class representing a Game Object
 * Represents any Object in the game, and stores all current GameObjects in a GameObject Vector (currentGameObjects)
 * stores the componenets of each object in a map<type, Component>
 * @author David MacLean
 */
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <SDL2/SDL.h>
#include <string>
#include <map>
#include <typeinfo>
#include <typeindex>
#include "Component.h"
#include "CollisionComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "PositionVector.h"
#include "AudioComponent.h"
#include "Renderer.h"
#include <vector>

class GameObject {
    public:
        /**
         * Constructor for GameObject
         * @param nametag: name of the GameObject
         * @param x,y :: int coordinates of the object (starts top left)
         */
        GameObject(std::string nametag, int x, int y);

        /**
         * @brief Deconstructor
         * Destructor for GameObject
         */
        ~GameObject();

        /**
        * @brief Updates objects
        * Updates Object Pure Virtual method
        */
        virtual void updateObject() = 0;

        /**
        * @brief Renders the graphic for GameObject
        * Checks if graphic has texture and renders
        */
        void renderGraphics();

        /**
        * @brief Adds the given Component to the map of GameObject's Components
        * @param type :: type of the component to be added
        * @param component :: a pointer to the component to be added to the map
        */
        void addComponent(std::string type, Component* component);

        /**
        * @brief Gets component
        * Given the type(index) of the Component checks for the component in the map and returns Component if found
        * @param type :: type of component to be found.
        * @return Pointer for Component corresponding to the type given.
        */
        Component* getComponent(std::string type);

        /**
        * @brief Gets name of object 
        * Gets the name/tag of this GameObject
        * @return string name tag of this GameObject
        */
        std::string getTag();

        /**
        * @brief Gets game object
        * Gets the GameObjects currently in the game.
        * @return vector containing currentGameObjects
        */
        static std::vector<GameObject*> getGameObjects() { return currentGameObjects; }

        /**
        * @brief Cleans everything up
        * Cleans everything up while maintaining the gameObject list
        * @return GameObject :: pointer to game object
        */
        GameObject* clean();

        /**
         * @brief Checks if object exists
         * Check to see if object still exists
         * @return bool :: true if object exists
         */
        bool getExistence();

        /**
         * @brief Maintains GameObject list
         * Removes game object from list of Gameobjects
         */
        void removeFromList();

    protected:
        /** name of the GameObject */
        std::string tag;

        /** map containing the Components for each GameObject */
	      std::map<std::string, Component*> component_map;

        /** vector of all the current GameObjects in the game */
        static std::vector<GameObject*> currentGameObjects;

        /** renderer for the graphics */
        SDL_Renderer* renderer;

        /** boolean variable for if an object exists */
        bool exists;

};
#endif
