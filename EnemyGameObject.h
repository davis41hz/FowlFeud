/**
 * @brief Represents enemy objects in the game.
 * Inherits from GameObject
 * @author David MacLean
 */
#ifndef TEAM1_ENEMYGAMEOBJECT_H
#define TEAM1_ENEMYGAMEOBJECT_H
#include "GameObject.h"
#include <SDL2/SDL.h>
#include <chrono>
#include "PlayerGameObject.h"

class EnemyGameObject: public GameObject
{
protected:
    /** current enemy health*/
    int health;

    /** speed of enemy*/
    int speed;

    /** damage of enemy*/
    int damage;

    /** attack speed of enemy*/
    float attackSpeed;

    /** Time of last attack */
    std::chrono::high_resolution_clock::time_point lastAttack;
    /**
     * When the enemy dies, to be determined
     */
    void onDeath();

    /**
     * @brief Decreases health of player when enemy collides with it
     */
    void attack();

    /**
     * @brief Targets a player
     */
    void findNewTarget();

    /** Transformer component for enemy*/
    TransformComponent* transform;

    /** Texture component for enemy*/
    TextureComponent* texture;

    /** Position vector for enemy*/
    PositionVector* direction;

    /** Player game object*/
    PlayerGameObject* player;

    /** Collision area for enemy */
    CollisionComponent* collision;

    /** Audio component for enemy */
    AudioComponent* audio;

    /** Audio Sounds for enemy wing */
    std::string wingHitSound = "sounds/wingHit.wav";
    
    /** Audio sound for when enemy dies */
    std::string deathSound = "sounds/eliminated.wav";
public:
    /**
     * Constructor
     * @param x,y coordinates for enemy object
     * @param h :: the current health of enemy
     * @param s :: the speed in which the enemy can travel
     * @param d :: the damage of the enmy's attack
     * @param as :: the speed in which the enemy can attack
     * @param textFile :: location of the textureFile.
     * @param p :: a pointer to the player object
     */
    EnemyGameObject(int x, int y, int h, int s, int d, float as, std::string textFile, PlayerGameObject* p);
    /**
     * Deconstructor
     */
    ~EnemyGameObject();
    /**
     * @brief Gets the health of the enemyGameObject
     * @return health int of current health.
     */
    int getHealth();
    /**
     * @brief Increases the players health by given amount
     * @param h :: the amount to increase the players health boy
     */
    void setHealth(int h);

    /**
     * @brief Inflicts damage on player
     * @param amount :: an integer amount of damage to be inflicted by the enemy
     */
    void takeDamage(int amount);
    /**
     * @brief Updates the objects entities
     */
    void updateObject();

};
#endif //TEAM1_ENEMYGAMEOBJECT_H
