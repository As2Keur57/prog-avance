#include "Game.hpp"

Game::Game(sf::RenderWindow* window)
{
    this->window = window;
	this->map = new Map(MAP_SIZE,MAP_SIZE);
    this->map->generateEffective();
}

Game::Game(Map* m, sf::RenderWindow* window)
{
    this->window = window;
    this->map = m;
}

Game::~Game()
{
	delete(this->map);
	delete(this->player);
}

void Game::handleEvents()
{
    while(window->pollEvent(event))
    {
        switch (event.type)
        {
            // window closed
            case sf::Event::Closed:
                window->close();
                break;
            // key pressed
            case sf::Event::KeyPressed:
                int movement = player->getMovement();
                int x = player->getX();
                int y = player->getY();
                switch(event.key.code)
                {
                    case sf::Keyboard::Q:
                        player->setWay('Q');
                        break;
                    case sf::Keyboard::D:    
                        player->setWay('D');
                        break;
                    case sf::Keyboard::Z:
                        player->setWay('Z');
                        break;
                    case sf::Keyboard::S:                            
                        player->setWay('S');
                        break;
                    default:
                        player->setWay('\n');
                }

                if(!this->mapCollision(player))
                {
                    player->move();
                }
                break;
        }

        if(event.type == sf::Event::MouseButtonPressed)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
                if(player->isVisible())
                    player->shoot();
        }
    }
}

Player* Game::getPlayer()
{
	return this->player;
}

Map* Game::getMap()
{
	return this->map;
}

sf::RenderWindow* Game::getWindow()
{
    return this->window;
}

bool Game::mapCollision(Sprite* s)
{
	int x = s->getX();
    int y = s->getY();
    int width = s->getWidth();
    int height = s->getHeight();

    switch(s->getWay())
    {
        case 'Q':
        x -= s->getMovement();
        break;
        case 'D':
        x += s->getMovement();
        break;
        case 'Z':
        y -= s->getMovement();
        break;
        case 'S':
        y += s->getMovement();
        break;
    }

    int column = x / TEXTURE_SIZE;
    int row = y / TEXTURE_SIZE;

    if(getMap()->isWall(column, row))
        return true;

    column = (x + width - 1) / TEXTURE_SIZE;

    if(getMap()->isWall(column, row))
        return true;

    row = (y + height - 1) / TEXTURE_SIZE;

    if(getMap()->isWall(column, row))
        return true;

    column = x / TEXTURE_SIZE;

    if(getMap()->isWall(column, row))
        return true;

    return false;
}

void Game::displayEnd()
{
    sf::Font font;   
    sf::Text position;
    sf::Text kills;
    sf::Text damages;
    sf::Text experience;
    sf::Text level;
    sf::Text nextLevel;
    sf::Text keyToContinue;
    std::stringstream content;

    int nbExperience = (int)((4 * pow(player->getLevel(), 3) / 5) + 1);
    int xWindow = (map->getX()*TEXTURE_SIZE);
    int yWindow = (map->getY()*TEXTURE_SIZE);
    int experienceWon = (player->getKills() * player->getDamages()) + (NB_ENEMIES+2)-this->getRank();

    if(!font.loadFromFile(FONT)) window->close();

    sf::RectangleShape background(sf::Vector2f(xWindow, yWindow));
    sf::RectangleShape experienceBar(sf::Vector2f(((player->getExperience()*xWindow)/nbExperience+1)+1, 50));

    background.setFillColor(sf::Color(0, 0, 0, 150));
    background.setPosition(0,0);
    experienceBar.setFillColor(sf::Color(255, 0, 0));
    experienceBar.setPosition(0, 3*(yWindow/4));

    position.setFont(font);
    kills.setFont(font);
    damages.setFont(font);
    experience.setFont(font);
    level.setFont(font);
    nextLevel.setFont(font);
    keyToContinue.setFont(font);

    content << "#" << this->getRank();
    position.setString(content.str());
    content.str(std::string());

    content << "Ennemies killed : " << player->getKills();
    kills.setString(content.str());
    content.str(std::string());

    content << "Damages thrown : " << player->getDamages();
    damages.setString(content.str());
    content.str(std::string());

    content << "Level " << player->getLevel();
    level.setString(content.str());
    content.str(std::string());

    content << "Level " << player->getLevel()+1;
    nextLevel.setString(content.str());
    content.str(std::string());

    position.setPosition(xWindow/2-32, yWindow/4);
    kills.setPosition(xWindow/3,yWindow/3);
    damages.setPosition(xWindow/3, yWindow/3 - 26);
    level.setPosition(15, (3*yWindow/4)-102);
    nextLevel.setPosition(xWindow - 9*24, (3*yWindow/4)-102);

    position.setCharacterSize(32);
    kills.setCharacterSize(24);
    damages.setCharacterSize(24);
    level.setCharacterSize(50);
    nextLevel.setCharacterSize(50);

    bool keyPressed = false;

    window->draw(background);
    window->draw(position);
    window->draw(kills);
    window->draw(damages);
    window->display();

    sf::Texture texScreen = sf::Texture();
    texScreen.create(xWindow, yWindow);
    texScreen.update(*window);
    sf::Sprite screen = sf::Sprite(texScreen);

    while(!keyPressed)
    {
        window->clear();
        window->draw(screen);

        content << "Level " << player->getLevel();
        level.setString(content.str());
        content.str(std::string());

        content << "Level " << player->getLevel()+1;
        nextLevel.setString(content.str());
        content.str(std::string());

        window->draw(level);
        window->draw(nextLevel);

        if(experienceWon-- > 0)
        {
            player->updateExperience(1);
            experienceBar.setSize(sf::Vector2f(((player->getExperience()*xWindow)/nbExperience+1)+1, 100));
            sf::sleep(sf::milliseconds(100));
            if(player->getExperience() >= nbExperience)
            {
                player->setExperience(player->getExperience() % nbExperience);
                player->levelUp();
                nbExperience = (int)((4 * pow(player->getLevel(), 3) / 5) + 1);
            }
        }

        window->draw(experienceBar);
        window->display();

        while(experienceWon <= 0 && window->pollEvent(event))
        {
            switch (event.type)
            {
                // window closed
                case sf::Event::Closed:
                    window->close();
                    break;
                // key pressed
                case sf::Event::KeyPressed:
                    keyPressed = true;
                    break;
            }
        }
    }

    Parser::savePlayer(this->player);
}

bool Game::isCollision(Sprite* s1, Sprite* s2)
{
	if(s1->isVisible() && s2->isVisible())
		if(s1->getX() >= s2->getX())
	        if(s1->getY() >= s2->getY())
	            if((s1->getX()+s1->getWidth()) <= (s2->getX()+s2->getWidth()))
	                if((s1->getY()+s1->getHeight()) <= (s2->getY()+s2->getHeight()))
	                    return true;

    return false;
}

void Game::deathHandler(Bullet* weapon, Player* collider)
{
    weapon->reinit();
    collider->updateLife(weapon->getAttack());
    weapon->getPlayer()->updateDamages();
    if(collider->getLife() <= 0)
    {
        weapon->getPlayer()->updateKills();
        collider->setVisible(false);
        collider->getBullet()->setVisible(false);

        if(collider == this->player || this->getRank() == 1)
        {
            this->displayEnd();
        }
    }
}