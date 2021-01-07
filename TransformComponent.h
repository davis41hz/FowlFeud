/**
* @brief TransformComponent of an object.
* Allows the manipulation of the position and scale of an object that this is a component to.
* @author David Liu, David MacLean
*/
#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H
#include "Component.h"
#include "PositionVector.h"
#include <SDL2/SDL.h>

class TransformComponent : public Component {
private:
  /** PositionVector to be manipulated. */
  PositionVector* position;
  /** Amount to rotate. */
  int rotation;
  /** Scale (size). */
  int scale;
  /** rectangle from SDL, has int x,y,w,h. */
  SDL_Rect srect;
  /** height of object. */
  int objectHeight = 32;
  /** width of object. */
  int objectWidth;
public:
  /**
   * @brief Constructor.
   * Creates the TransformComponent.
   * @param position :: pointer to PositionVector to be manipulated.
   * @param rotation :: amount of rotation.
   * @param scale :: size of the object.
   */
  TransformComponent(PositionVector* position, int rotation, int scale);
  /**
   * @brief Destructor.
   * Destroys the TransformComponent.
   */
  ~TransformComponent();
  /**
   * @brief Gets the position vector for this component.
   * Gets the position of this component in the form of a *PositionVector.
   * @return the PositionVector* belonging to this component.
   */
  PositionVector* getPosition();
  /**
   * @brief sets the positionVector for this component.
   * Sets the position of this component to the given *PositionVector.
   * @param newPosition :: the PositionVector* this component is to be set to.
   */
  void setPosition(PositionVector* newPosition);
 /**
  * @brief Gets the rotation value for this component.
  * Gets the rotation of this component in the form of an int.
  * @return int value of rotation.
  */
  int getRotation();
 /**
  * @brief sets the rotation value for this component.
  * Sets the rotation of this component to the given int.
  * @param newRotation :: the int rotation to be set.
  */
  void setRotation(int newRotation);
  /**
   * @brief gets the rotation value for this component.
   * Gets the scale of this component in the form of an int.
   * @return int value of scale.
   */
  int getScale();
  /**
   * @brief sets the rotation value for this component.
   * Sets the scale of this component to the given int.
   * @param newScale :: the new scale value for this component.
   */
  void setScale(int newScale);
  /**
   * @brief gets the SDL_Rect belonging to this component.
   * Returns the SDL_Rect* that belongs to this component.
   * @return the SDL_Rect* belonging to this component.
   */
  SDL_Rect* getRect();
  /**
   * @brief gets the dimensions of the object.
   * Gets the side length of this square object - OBJECTWIDTH.
   * @return constant int OBJECTWIDTH.
   */
  int getDimension() { return objectWidth; }
  /**
   * @brief gets the name of this component.
   * Returns the name of this component - "transform".
   * @return the string name of this class - "transform".
   */
  static std::string getName() { return std::string("transform"); }
  /**
   * @brief sets the size of the component.
   * Sets the width and height of the component to the given values.
   * @param w :: the new width.
   * @param h :: the new height.
   */
  void setRectSize(int w, int h);
};
#endif
