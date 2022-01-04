#ifndef MULTI_GAME
#define MULTI_GAME

#include "../Game.hpp"
#include "../db/Mysql.hpp"

class MultiGame : public Game
{

public:
	MultiGame(string playerUUID, sf::RenderWindow* window);
	virtual ~MultiGame();
	void display();
	void handleCollision();
	Point* getFreePoint();
	void handleBulletMovement();
	int getRank();
	void waitingRoom();
	int getNbPlayers();
	static bool isActive();
	void updateOnlinePlayers();
	void initOnlinePlayers();
private:
	Mysql* database;
	Player** onlinePlayers = NULL;
	int nbPlayers;
};

#endif