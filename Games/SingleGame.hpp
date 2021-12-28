#ifndef SINGLE_GAME
#define SINGLE_GAME

#include "../Game.hpp"

#include "../Utils/Node.hpp"

class SingleGame : public Game
{
	public:
		/**
		 * Costructor of single game
		 * \param string playerUUID
		 * \param sf::RenderWindow* window
		 */
		SingleGame(string playerUUID, sf::RenderWindow* window);

		/**
		 * Costructor of single game
		 * \param Map* map
		 * \param string playerUUID
		 * \param sf::RenderWindow* window
		 */
		SingleGame(Map* map, string playerUUID, sf::RenderWindow* window);

		/**
		 * Destructor of single game
		 */
		virtual ~SingleGame();

		/**
		 * Search the nearest enemy around the current Player
		 * \param int aiIndex
		 * \return Player*
		 */
		Player* nearestEnemy(int aiIndex);

		/**
		 * build the path the ai must follow
		 * \param list<Point> way
		 * \return list<Point>
		 */
		list<Point> makeWay(list<Point> way);

		/**
		 * Move ai
		 */
		void moveAi();

		/**
		 * Ruturn the nearest enemy direction
		 * \return char 
		 */
		char dirEnemy(Player* player, Point* goal);

		/**
		 * Display the game on sfml window 
		 */
		void display();

		/**
		 * Manage the collision
		 */
		void handleCollision();

		/**
		 * Search a free point to initialize the first player position
		 * \return Point* 
		 */
		Point* getFreePoint();

		/**
		 * Manage the bullet movement
		 */
		void handleBulletMovement();

		/**
		 * Return the number of ai in life 
		 * \return int
		 */
		int getRank();

		/**
		 * Return the table of ai  
		 * \return Player**
		 */
		Player** getAi();

		/**
		 * Detect the end of the game
		 * \return bool
		 */
		bool isEnd();
		
	private:
		Player** ai = NULL;
};

#endif