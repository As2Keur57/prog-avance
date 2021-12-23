#ifndef GAME_H
#define GAME_H

#include "GameObjects/Map.hpp"
#include "GameObjects/Sprite/Player.hpp"
#include "GameObjects/Sprite/Bullet.hpp"

#include <sstream>
#include "Utils/Parser.hpp"

class Game
{
public:
	/**
	 * Constructor of Game 
	 * \param sf::RenderWindow* window
	 */
	Game(sf::RenderWindow* window);

	/**
	 * Constructor of Game 
	 * \param sf::RenderWindow* window
	 */
	Game(Map* map, sf::RenderWindow* window);

	/**
	 * Destructor of Game 
	 */
	~Game();

	/**
	 * Detect the colision between the wall map and Player
	 */
	bool mapCollision();

	/**
	 * Return the player 
	 * \return Player*
	 */
	Player* getPlayer();

	/**
	 * Return the map 
	 * \return Map*
	 */
	Map* getMap();

	/**
	 * Return the ai table 
	 * \return Player**
	 */
	Player** getAi();

	/**
	 * Detect the collision between the wall map and Sprite
	 * \param Sprite* 
	 * \return bool
	 */
	bool mapCollision(Sprite* s);

	/**
	 * Detect the collision between two Sprites
	 * \param Sprite* s1
	 * \param Sprite* s2
	 * \return bool
	 */
	bool isCollision(Sprite* s1, Sprite* s2);

	/**
	 * Return the sfml window 
	 * \return sf::RenderWindow*
	 */
	sf::RenderWindow* getWindow();

	/**
	 * Manages the death of players
	 * \param Bullet* weapon
	 * \param Player* collider
	 */
	void deathHandler(Bullet* weapon, Player* collider);

	/**
	 * Displaye the end of the game, the player number kills, total damages, rank and experience 
	 */
	void displayEnd();

	/**
	 * Manages the mouse & keyboard event
	 */
	void handleEvents();

	/** 
	 * Display the game on sfml window
	 */
	virtual void display() = 0;

	/**
	 * Manages the collision 
	 */
	virtual void handleCollision() = 0;

	/**
	 * Search a free point to initialize the first player position
	 * \return Point* 
	 */
	virtual Point* getFreePoint() = 0;

	/**
	 * Manage the bullet movement
	 */
	virtual void handleBulletMovement() = 0;

	/**
	 * Return the number of Sprite in life 
	 * \return int
	 */
	virtual int getRank() = 0;

protected:
	Map* map = NULL;
	Player* player = NULL;
	sf::RenderWindow* window;
	sf::Event event;
};

#endif