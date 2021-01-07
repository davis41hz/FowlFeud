/**
* @brief Uses SDL_point to represent the position of Objects in the game
* Contains a group of methods for manipulating these points.
* @author David MacLean
*/
#ifndef POSITION_VECTOR_H
#define POSITION_VECTOR_H
#include <SDL2/SDL.h>
class PositionVector {
public:
    /**
    * @brief Constructor.
    * Creates the PositionVector object.
    * @param x,y :: the x, y coordinates to create the SDL_Point.
    */
    PositionVector(int x, int y);
    /**
     * @brief Destructor.
     * Destroys the PositionVector object.
     */
    ~PositionVector();
    /**
    * @brief Adds two PositionVectors together.
    * Adds the given PositionVector to this PositionVector.
    * @param pvect :: is the PositionVector* to be added to this PostionVector.
    */
    void add(PositionVector* pvect);
    /**
     * @brief Subtracts a PositionVector.
     * Subtracts the given PositionVector from this PositionVector.
     * @param pvect :: is the PositionVector* to be subtracted from this PostionVector.
     */
    void subtract(PositionVector* pvect);
    /**
     * @brief Divides two PositionVectors.
     * Divides the given PositionVector from this PositionVector.
     * @param pvect :: is the PositionVector* that will be divided by this PositionVector.
     */
    void divide(PositionVector* pvect);
    /**
     * @brief Divides by scalar int.
     * Divides this PositionVector by the given scalar int.
     * @param x :: int to be denominator.
     */
    void divide(int x);
    /**
     * @brief Multiplies two PositionVectors together.
     * Multiplies this PositionVector by the given PositionVector.
     * @param pvect :: is the PositionVector* to be multiplied to this PostionVector
     */
    void multiply(PositionVector* pvect);
    /**
     * @brief Multiplies by scalar int.
     * Multiplies this PositionVector by the given scalar int.
     * @param x :: int to be multiplied by this PositionVector.
     */
    void multiply(int x);
    /**
     * @brief Gets the x value.
     * Gets the x-coordinate value of this object.
     * @return int value of x-axis.
     */
    int getX();
    /**
     * @brief Gets the y value.
     * Gets the y-coordinate value of this object.
     * @return int value of y-axis.
     */
    int getY();
    /**
     * @brief Sets the x value.
     * Sets the x-coordinate value of this object to the given int.
     * @param x :: int value of x-axis.
     */
    void setX(int x);
    /**
     * @brief Sets the y value.
     * Sets the y-coordinate value of this object to the given int.
     * @return int :: value of Y-axis.
     */
    void setY(int y);

private:
    /** SDL_point has two var's: position.x and position.y */
    SDL_Point position;
};
#endif
