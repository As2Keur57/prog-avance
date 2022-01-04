#include "MultiGame.hpp"

MultiGame::MultiGame(string playerUUID, sf::RenderWindow* window) : Game(window)
{
	Point* t = new Point(0, 0);
	player = Parser::loadPlayer(playerUUID, t);

	if(player == NULL)
	{
		player = new Player(playerUUID, t,0,0, TEXTURE_SIZE, TEXTURE_SIZE);
	}



	database = new Mysql(HOST, LOGIN, PASSWORD, DBNAME);
	database->query("INSERT INTO players VALUES(?, 0, 0, 0, 0, ?, ?, ?)", true);
	database->set(1, playerUUID);
	database->set(2, player->getLife());
	database->set(3, player->getDefense());
	database->set(4, player->getAttack());
	database->execute();

	nbPlayers = NB_PLAYERS;

	onlinePlayers = new Player*[NB_PLAYERS];
	for(int i = 0; i < NB_PLAYERS; i++)
	{
		onlinePlayers[i] = NULL;
	}
	initOnlinePlayers();
}

MultiGame::~MultiGame()
{
	database->query("DELETE FROM players WHERE uuid = ?", true);
	database->set(1, player->getUuid());
	database->execute();

	for(int i = 0; i < NB_PLAYERS; i++)
	{
		if(onlinePlayers[i] != NULL)
			delete onlinePlayers[i];
	}
	delete [] onlinePlayers;
	delete(database);
}

void MultiGame::waitingRoom()
{
	int xWindow = (map->getX()*TEXTURE_SIZE);
    int yWindow = (map->getY()*TEXTURE_SIZE);
    sf::Sprite background;
	sf::RectangleShape rectangle(sf::Vector2f(xWindow, yWindow));
    rectangle.setFillColor(sf::Color(0, 0, 0, 150));
    map->display(window);
    window->draw(rectangle);
    sf::Texture mapScreen;
    mapScreen.create(map->getX()*TEXTURE_SIZE, map->getY()*TEXTURE_SIZE);
    mapScreen.update(*window);
    background.setTexture(mapScreen);
    std::stringstream content;

    sf::Font font;
    sf::Text cpt;
    sf::Text waiting;

    font.loadFromFile(FONT);

    cpt.setFont(font);
    waiting.setFont(font);

    waiting.setString("Waiting for players");

    cpt.setPosition(xWindow/2 + 10, yWindow/2 - 10);
    waiting.setPosition(xWindow/2 - 160, yWindow/4);

    cpt.setCharacterSize(TITLE_CHAR_SIZE);
    waiting.setCharacterSize(TITLE_CHAR_SIZE);

    while(getNbPlayers() != NB_PLAYERS && window->isOpen())
    {
    	while(window->pollEvent(event))
    	{
    		switch(event.type)
        	{
            	case sf::Event::Closed:
            		window->close();
                	break;
        	}
    	}
        window->clear();
        content << getNbPlayers() << "/" << NB_PLAYERS;
    	cpt.setString(content.str());
    	content.str(std::string());
    	initOnlinePlayers();
        window->draw(background);
        window->draw(waiting);
        window->draw(cpt);
        window->display();
    }

    this->player;
}

void MultiGame::initOnlinePlayers()
{
	database->query("SELECT * FROM players WHERE uuid != ?", true);
	database->set(1, player->getUuid());
	database->execute();

	int index = 0;

	for(int i = 0; i < NB_PLAYERS; i++)
	{
		if(onlinePlayers[i] != NULL)
			delete onlinePlayers[i];
	}

	while(database->next())
	{
		onlinePlayers[index] = new Player(database->getColumn("uuid"), new Point(atoi(database->getColumn("x").c_str()), atoi(database->getColumn("y").c_str())), 288, 0, 96, 128);
		index++;
	}
}

int MultiGame::getNbPlayers()
{
	int players = 1;

	for(int i = 0; i < NB_PLAYERS; i++)
	{
		if(onlinePlayers[i] != NULL)
			players++;
	}

	return players;
}

void MultiGame::updateOnlinePlayers()
{
	for(int i = 0; i < NB_PLAYERS; i++)
	{
		Player* onlinePlayer = onlinePlayers[i];

		if(onlinePlayer == NULL)
			continue;

		database->query("SELECT * FROM players WHERE uuid=" + onlinePlayer->getUuid());
		database->next();

		onlinePlayer->getPosition()->setX(atoi(database->getColumn("x").c_str()));
		onlinePlayer->getPosition()->setY(atoi(database->getColumn("y").c_str()));
		onlinePlayer->getBullet()->getPosition()->setX(atoi(database->getColumn("x_bullet").c_str()));
		onlinePlayer->getBullet()->getPosition()->setY(atoi(database->getColumn("y_bullet").c_str()));
		onlinePlayer->setLife(atoi(database->getColumn("life").c_str()));
	}

	database->query("UPDATE FROM players VALUES(uuid, ?, ?, ?, ?, ?, defense, attack)", true);
	database->set(1, player->getX());
	database->set(2, player->getY());
	database->set(3, player->getBullet()->getX());
	database->set(4, player->getBullet()->getY());
	database->set(5, player->getLife());
	database->execute();
}

bool MultiGame::isActive()
{
	Mysql db(HOST, LOGIN, PASSWORD, DBNAME);
	db.query("SELECT x,y FROM players");
	db.next();
	if(db.getColumn("x") == 0 && db.getColumn("y") == 0)
	{
		return false;
	}
	return true;
}

void MultiGame::display()
{
	window->clear();
    map->display(window);
    player->display(window, player->getAnimX(),player->getAnimY());
    player->getBullet()->display(window, 174, 192);
    for(int i = 0; i < NB_PLAYERS; i++)
    {
    	if(onlinePlayers[i] != NULL)
    	{
    		onlinePlayers[i]->getBullet()->display(window, 174, 192);
        	onlinePlayers[i]->display(window, onlinePlayers[i]->getAnimX(),onlinePlayers[i]->getAnimY());
    	}
    }
    window->display();
}

Point* MultiGame::getFreePoint()
{
    /*srand(time(0));
    Point* freePoint = new Point(0, 0);

    while(true)
    {
    	delete(freePoint);
        freePoint = new Point((rand()%this->map->getX())*TEXTURE_SIZE, (rand()%this->map->getY())*TEXTURE_SIZE);

        //We test if the point isn't on a wall
        if(map->isWall((freePoint->getX()/TEXTURE_SIZE), (freePoint->getY()/TEXTURE_SIZE))) continue;

        //We test if the point isn't on the AIs
        if(this->onlinePlayers != NULL)
        {
            bool isOnPlayer = false;
            for(int i = 0; i < NB_PLAYERS; i++)
            {
                if(onlinePlayers[i] == NULL) continue;

                if(onlinePlayers[i]->getX() == freePoint->getX())
                    if(onlinePlayers[i]->getY() == freePoint->getY())
                        isOnAi = true;
            }

            if(isOnPlayer) continue;
        }

        //if we went through all the test it's that the point is a free point, else we do again these operations
        return freePoint;
    }
    return NULL;*/
}

void MultiGame::handleCollision()
{
    for(int i = 0; i < NB_ENEMIES; i++)
    {
        Player* onlinePlayer = this->onlinePlayers[i];
        Bullet* bullet = onlinePlayer->getBullet();
        if(this->isCollision(bullet, player))
        {
            deathHandler(bullet, player);
        }
    }
}

void MultiGame::handleBulletMovement()
{

}

int MultiGame::getRank()
{
	return 1;
}
