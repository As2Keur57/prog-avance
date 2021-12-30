#include "Menu.hpp"

Menu::Menu(Point* pos)
{
    window = new sf::RenderWindow(sf::VideoMode(pos->getX()*TEXTURE_SIZE, pos->getX()*TEXTURE_SIZE), "BRUni");

    Map* map = new Map(pos);
    map->generateEffective();

    int xWindow = (map->getX()*TEXTURE_SIZE);
    int yWindow = (map->getY()*TEXTURE_SIZE);

    sf::RectangleShape rectangle(sf::Vector2f(xWindow, yWindow));
    rectangle.setFillColor(sf::Color(0, 0, 0, 150));

    map->display(window);
    window->draw(rectangle);

    mapScreen = sf::Texture();

    mapScreen.create(map->getX()*TEXTURE_SIZE, map->getY()*TEXTURE_SIZE);

    mapScreen.update(*window);



    background.setTexture(mapScreen);

    delete map;

}


Menu::~Menu()
{
    delete window;
}

void Menu::choiceGame()
{
    int choice = NOCHOICE;
    int endOfGame = 2;
    string* pseudo = new string();

    while(choice != QUIT)
    {
        choice = handleMenu(pseudo);
        endOfGame = 2;

        if(choice != QUIT) choice = loadGame(choice);
        
        switch(choice)
        {
            case SINGLE:
            {
                SingleGame* gameSingle = new SingleGame(*pseudo, window);
                sf::Thread moveAi(&SingleGame::moveAi, gameSingle);

                while(gameSingle->getWindow()->isOpen() && !gameSingle->isEnd())
                {
                    gameSingle->handleEvents();
                    moveAi.launch();
                    gameSingle->handleBulletMovement();
                    gameSingle->handleCollision();
                    gameSingle->display();
                }

                moveAi.terminate();
                delete gameSingle;
            }
            break;

            case MULTI:
                break;
        }
    }

    delete pseudo;    
}

int Menu::loadGame(int choice)
{
    sf::Font font;
    sf::Text cpt;
    sf::CircleShape circle(TITLE_CHAR_SIZE);

    int counter = WAIT;

    int xWindow = (window->getSize().x);
    int yWindow = (window->getSize().y);


    if(!font.loadFromFile(FONT)) window->close();

    cpt.setFont(font);
    cpt.setString(to_string(counter));
    cpt.setPosition(xWindow/2 + 10, yWindow/2 - 10);
    cpt.setCharacterSize(TITLE_CHAR_SIZE);

    circle.setOutlineThickness(5);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(sf::Color(255, 255, 255));
    circle.setPosition(xWindow/2 - 25, yWindow/2 - 25);

    this->display();

    sf::Event event;

        while(counter >= 0)
        {
            switch (event.type)
            {
                // window closed
                case sf::Event::Closed:
                    //choice = QUIT;
                    break;
            }
            window->clear();
            this->display();
            window->draw(cpt);
            window->draw(circle);
            window->display();

            sf::sleep(sf::milliseconds(1000));

            counter--;

            cpt.setString(to_string(counter));

            
        }

        return choice;
}

int Menu::handleMenu(string* pseudo)
{
    int choice = NOCHOICE;

    while(window->isOpen() && choice == NOCHOICE)
    {

        sf::Font font;
        sf::Text title;
        sf::Text singlePlayer;
        sf::Text multiPlayer;
        sf::Text update;
        sf::Text quit;
        sf::Text uuid;

        int xWindow = (window->getSize().x);
        int yWindow = (window->getSize().y);

        Point* mousePosition = new Point();

        if(!font.loadFromFile(FONT)) window->close();
        
        singlePlayer.setFont(font);
        multiPlayer.setFont(font);
        update.setFont(font);
        quit.setFont(font);
        title.setFont(font);
        uuid.setFont(font);

        singlePlayer.setString("Single Player");
        multiPlayer.setString("Multi Player");
        update.setString("Update");
        quit.setString("Quit ->");
        title.setString("BRUni");
        uuid.setString("Enter your pseudo !!!");

        singlePlayer.setPosition(xWindow/2 - (xWindow*0.1042), yWindow/3);
        multiPlayer.setPosition(xWindow/2 - (xWindow*0.1042), yWindow/2);
        update.setPosition(xWindow-440 - (xWindow*0.1042), yWindow/1.5);
        quit.setPosition(xWindow-125, yWindow-50);
        title.setPosition(xWindow/2 - (xWindow*0.0781), 0);
        uuid.setPosition(xWindow/2 - (xWindow*0.1042), yWindow/6);

        singlePlayer.setCharacterSize(TEXT_CHAR_SIZE);
        multiPlayer.setCharacterSize(TEXT_CHAR_SIZE);
        update.setCharacterSize(TEXT_CHAR_SIZE);
        quit.setCharacterSize(TEXT_CHAR_SIZE);
        title.setCharacterSize(TITLE_CHAR_SIZE);
        uuid.setCharacterSize(SMALL_TEXT_CHAR_SIZE);

        this->display();
        window->draw(singlePlayer);
        window->draw(multiPlayer);
        window->draw(update);
        window->draw(quit);
        window->draw(title);
        window->draw(uuid);

        sf::Event event;

        while(choice == NOCHOICE && window->pollEvent(event))
        {
            switch (event.type)
            {
                // window closed
                case sf::Event::Closed:
                    choice = QUIT;
                    break;
                // key pressed
                case sf::Event::TextEntered:
                    if(event.text.unicode != 8)
                    {
                        *pseudo = *pseudo + (char) event.text.unicode;
                    } else {
                        if(pseudo->size() > 0)
                            pseudo->pop_back();
                    }
                    break;
            }

            mousePosition->setX(sf::Mouse::getPosition(*window).x);
            mousePosition->setY(sf::Mouse::getPosition(*window).y);

            if(event.type == sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    bool uuidIsEmpty = *pseudo == "";

                    //SinglePlayer
                    if(mousePosition->getX() >= (xWindow * 0.3958) && mousePosition->getX() <=  (xWindow * 0.3958) + 200 && mousePosition->getY() >= (yWindow * 0.3438) && mousePosition->getY() <= (yWindow * 0.3438) + 40)
                    {
                        if(uuidIsEmpty)
                            uuid.setFillColor(sf::Color::Red);
                        else
                          choice = SINGLE;
                    }
                    //MultiPlayer
                    if(mousePosition->getX() >= (xWindow * 0.3958) && mousePosition->getX() <=  (xWindow * 0.3958) + 200 && mousePosition->getY() >= (yWindow * 0.5) && mousePosition->getY() <= (yWindow * 0.5) + 40)
                    {
                        if(uuidIsEmpty)
                            uuid.setFillColor(sf::Color::Red);
                        else
                          choice = MULTI;
                    }
                    if(mousePosition->getX() >= (xWindow * 0.44) && mousePosition->getX() <=  (xWindow * 0.44) + 100 && mousePosition->getY() >= (yWindow * 0.67) && mousePosition->getY() <= (yWindow * 0.67) + 40)
                    {
                        if(uuidIsEmpty)
                            uuid.setFillColor(sf::Color::Red);
                        else
                          pointMenu(*pseudo);
                    }

                    if(mousePosition->getX() >= xWindow-125 && mousePosition->getY() >= yWindow-50)
                    {
                        choice = QUIT;
                    }                
                }
            }

            //SinglePlayer
            if(mousePosition->getX() >= (xWindow * 0.3958) && mousePosition->getX() <=  (xWindow * 0.3958) + 200 && mousePosition->getY() >= (yWindow * 0.3438) && mousePosition->getY() <= (yWindow * 0.3438) + 40)
            {
                singlePlayer.setFillColor(sf::Color(0, 0, 0, 255));
            }
            //MultiPlayer
            if(mousePosition->getX() >= (xWindow * 0.3958) && mousePosition->getX() <=  (xWindow * 0.3958) + 200 && mousePosition->getY() >= (yWindow * 0.5) && mousePosition->getY() <= (yWindow * 0.5) + 40)
            {
                multiPlayer.setFillColor(sf::Color(0, 0, 0, 255));
            }
            //Uptdate
            if(mousePosition->getX() >= (xWindow * 0.44) && mousePosition->getX() <=  (xWindow * 0.44) + 100 && mousePosition->getY() >= (yWindow * 0.67) && mousePosition->getY() <= (yWindow * 0.67) + 40)
            {
                update.setFillColor(sf::Color(0, 0, 0, 255));
            }
            //Quit
            if(mousePosition->getX() >= xWindow-125 && mousePosition->getY() >= yWindow-50)
            {
                quit.setFillColor(sf::Color(0, 0, 0, 255));
            }   

            window->clear();
            if(*pseudo != "")
                uuid.setString("Pseudo : " + *pseudo);
            this->display();
            window->draw(singlePlayer);
            window->draw(multiPlayer);
            window->draw(update);
            window->draw(quit);
            window->draw(title);
            window->draw(uuid);
            window->display();
        }

        delete mousePosition;

    }

    return choice;
}

int Menu::pointMenu(string pseudo)
{
    int choice = NOCHOICE;

    Player* player = Parser::loadPlayer(pseudo, new Point());

    int* pointA = new int();
    int* pointD = new int();
    int* pointL = new int();
    int* pointAv = new int();

    if(player != NULL)
    {
        *pointA = player->getPointAttack();
        *pointD = player->getPointDefense();
        *pointL = player->getPointLife();
        *pointAv = player->getPointLevel();
    }

    while(window->isOpen() && choice == NOCHOICE && player != NULL)
    {
        sf::Font font;
        sf::Text defense;
        sf::Text attack;
        sf::Text life;
        sf::Text back;
        sf::Text updefense;
        sf::Text downdefense;
        sf::Text upattack;
        sf::Text downlife;
        sf::Text uplife;
        sf::Text downattack;

        sf::Text pointAvailable;
        sf::Text defencePoint;
        sf::Text attackPoint;
        sf::Text lifePoint;

        int xWindow = (window->getSize().x);
        int yWindow = (window->getSize().y);

        Point* mousePosition = new Point();

        if(!font.loadFromFile(FONT)) window->close();
        
        //defense
        defense.setFont(font);
        updefense.setFont(font);
        downdefense.setFont(font);
        //attack
        attack.setFont(font);
        upattack.setFont(font);
        downattack.setFont(font);
        //life
        life.setFont(font);
        uplife.setFont(font);
        downlife.setFont(font);

        back.setFont(font);
        //point
        pointAvailable.setFont(font);
        defencePoint.setFont(font);
        attackPoint.setFont(font);
        lifePoint.setFont(font);

   
        //defense string
        defense.setString("Defense");
        updefense.setString(" + ");
        downdefense.setString(" - ");
        //attack string
        attack.setString("Attack");
        upattack.setString(" + ");
        downattack.setString(" - ");
        //life string
        life.setString("Life");
        uplife.setString(" + ");
        downlife.setString(" - ");

        back.setString("Back ->");
        //Point string
        pointAvailable.setString("Point disponible : [" + to_string(*pointAv) + "]");
        defencePoint.setString("[" + to_string(*pointD) + "]");
        attackPoint.setString("[" + to_string(*pointA) + "]");
        lifePoint.setString("[" + to_string(*pointL) + "]");

 

        //defense position
        defense.setPosition(xWindow/2 - 60, yWindow/3);
        updefense.setPosition(xWindow/2 + 85, yWindow/3);
        downdefense.setPosition(xWindow/2 -  110, yWindow/3);
        //attack position
        attack.setPosition(xWindow/2 - 50, yWindow/2);
        upattack.setPosition(xWindow/2 + 85, yWindow/2);
        downattack.setPosition(xWindow/2 - 110, yWindow/2);
        //life position
        life.setPosition(xWindow/2 - 20, yWindow/1.5);
        uplife.setPosition(xWindow/2 + 85, yWindow/1.5);
        downlife.setPosition(xWindow/2 - 110, yWindow/1.5);

        back.setPosition(xWindow-125, yWindow-50);
        //point position
        pointAvailable.setPosition(xWindow/2 - 130, 0);
        defencePoint.setPosition(xWindow/2 + 130, yWindow/3);
        attackPoint.setPosition(xWindow/2 + 130, yWindow/2);
        lifePoint.setPosition(xWindow/2 + 130, yWindow/1.5);

        //defense character size
        defense.setCharacterSize(TEXT_CHAR_SIZE);
        updefense.setCharacterSize(TEXT_CHAR_SIZE);
        downdefense.setCharacterSize(TEXT_CHAR_SIZE);
        //attack character size
        attack.setCharacterSize(TEXT_CHAR_SIZE);
        upattack.setCharacterSize(TEXT_CHAR_SIZE);
        downattack.setCharacterSize(TEXT_CHAR_SIZE);
        //life character size
        life.setCharacterSize(TEXTURE_SIZE);
        uplife.setCharacterSize(TEXT_CHAR_SIZE);
        downlife.setCharacterSize(TEXT_CHAR_SIZE);

        back.setCharacterSize(TEXT_CHAR_SIZE);
        //point character size
        pointAvailable.setCharacterSize(TEXT_CHAR_SIZE);
        defencePoint.setCharacterSize(TEXT_CHAR_SIZE);
        attackPoint.setCharacterSize(TEXT_CHAR_SIZE);
        lifePoint.setCharacterSize(TEXTURE_SIZE);
        

        sf::Event event;

        while(choice == NOCHOICE && window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                choice = QUIT;
            }

            mousePosition->setX(sf::Mouse::getPosition(*window).x);
            mousePosition->setY(sf::Mouse::getPosition(*window).y);

            if(event.type == sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    //updefence
                    if(mousePosition->getX() >= xWindow/2 + 85 && mousePosition->getX() <=  xWindow/2 + 85 + 20 && mousePosition->getY() >= yWindow/3 && mousePosition->getY() <= yWindow/3 + 30)
                    {
                        if(*pointAv > 0)
                        {
                            *pointAv -= 1;
                            *pointD +=1;
                        }
                    }
                    //downdefence
                    if(mousePosition->getX() >= xWindow/2 -  110 && mousePosition->getX() <=  xWindow/2 -  110 + 30 && mousePosition->getY() >= yWindow/3 && mousePosition->getY() <= yWindow/3 + 30)
                    {
                        if(*pointD > 0)
                        {
                            *pointAv +=1;
                            *pointD -= 1;
                        }
                        
                    }
                    //upattack
                    if(mousePosition->getX() >= xWindow/2 + 85 && mousePosition->getX() <=  xWindow/2 + 85 + 30 && mousePosition->getY() >= yWindow/2 && mousePosition->getY() <= yWindow/2 + 30)
                    {
                        if(*pointAv > 0)
                        {
                            *pointAv -= 1;
                            *pointA +=1;
                        }
                    }
                    //downattck
                    if(mousePosition->getX() >= xWindow/2 - 110 && mousePosition->getX() <=  xWindow/2 - 110 + 30 && mousePosition->getY() >= yWindow/2 && mousePosition->getY() <= yWindow/2 + 30)
                    {
                        if(*pointA > 0)
                        {
                            *pointAv +=1;
                            *pointA -= 1;
                        }
                    }
                    //uplife
                    if(mousePosition->getX() >= xWindow/2 + 85 && mousePosition->getX() <=  xWindow/2 + 85 + 30 && mousePosition->getY() >= yWindow/1.5 && mousePosition->getY() <= yWindow/1.5 + 30)
                    {
                        if(*pointAv > 0)
                        {
                            *pointAv -= 1;
                            *pointL +=1;
                        }
                    }
                    //downlife
                    if(mousePosition->getX() >= xWindow/2 - 110 && mousePosition->getX() <=  xWindow/2 - 110 + 30 && mousePosition->getY() >= yWindow/1.5 && mousePosition->getY() <= yWindow/1.5 + 30)
                    {
                        if(*pointL > 0)
                        {
                            *pointAv +=1;
                            *pointL -= 1;
                        }
                    }
                    //back
                    if(mousePosition->getX() >= xWindow-125 && mousePosition->getY() >= yWindow-50)
                    {
                        choice = QUIT;
                    }                
                }
            }
            //updefense
            if(mousePosition->getX() >= xWindow/2 + 85 && mousePosition->getX() <=  xWindow/2 + 85 + 30 && mousePosition->getY() >= yWindow/3 && mousePosition->getY() <= yWindow/3 + 30)
            {
                updefense.setFillColor(sf::Color(0, 0, 0, 255));
            } 
            //downdefense
            if(mousePosition->getX() >= xWindow/2 -  110 && mousePosition->getX() <=  xWindow/2 -  110 + 30 && mousePosition->getY() >= yWindow/3 && mousePosition->getY() <= yWindow/3 + 30)
            {
                downdefense.setFillColor(sf::Color(0, 0, 0, 255));
            }
            //upattack
            if(mousePosition->getX() >= xWindow/2 + 85 && mousePosition->getX() <=  xWindow/2 + 85 + 30 && mousePosition->getY() >= yWindow/2 && mousePosition->getY() <= yWindow/2 + 30)
            {
                upattack.setFillColor(sf::Color(0, 0, 0, 255));
            }
            //downattack
            if(mousePosition->getX() >= xWindow/2 - 110 && mousePosition->getX() <=  xWindow/2 - 110 + 30 && mousePosition->getY() >= yWindow/2 && mousePosition->getY() <= yWindow/2 + 30)
            {
                downattack.setFillColor(sf::Color(0, 0, 0, 255));
            }
            //uplife 
            if(mousePosition->getX() >= xWindow/2 + 85 && mousePosition->getX() <=  xWindow/2 + 85 + 30 && mousePosition->getY() >= yWindow/1.5 && mousePosition->getY() <= yWindow/1.5 + 30)
            {
                uplife.setFillColor(sf::Color(0, 0, 0, 255));
            }
            //downlife
            if(mousePosition->getX() >= xWindow/2 - 110 && mousePosition->getX() <=  xWindow/2 - 110 + 30 && mousePosition->getY() >= yWindow/1.5 && mousePosition->getY() <= yWindow/1.5 + 30)
            {
                downlife.setFillColor(sf::Color(0, 0, 0, 255));
            }
            //back
            if(mousePosition->getX() >= xWindow-125 && mousePosition->getY() >= yWindow-50)
            {
                back.setFillColor(sf::Color(0, 0, 0, 255));
            }   

            pointAvailable.setString("Point disponible : [" + to_string(*pointAv) + "]");
            defencePoint.setString("[" + to_string(*pointD) + "]");
            attackPoint.setString("[" + to_string(*pointA) + "]");
            lifePoint.setString("[" + to_string(*pointL) + "]");

            window->clear();

            this->display();
            //defense draw
            window->draw(defense);
            window->draw(updefense);
            window->draw(downdefense);
            //attack draw
            window->draw(attack);
            window->draw(upattack);
            window->draw(downattack);
            //life draw
            window->draw(life);
            window->draw(uplife);
            window->draw(downlife);

            window->draw(back);
            //point draw
            window->draw(defencePoint);
            window->draw(attackPoint);
            window->draw(lifePoint);
            window->draw(pointAvailable);
            window->display();
        
        }
        delete mousePosition;
    }

    if(player != NULL)
    {
        player->setPointLevel(*pointAv);
        player->setPointDefense(*pointD);
        player->setPointAttack(*pointA);
        player->setPointLife(*pointL);
        Parser::savePlayer(player);
    }

    delete pointAv;
    delete pointA;
    delete pointD;
    delete pointL;

    delete player;

    return choice;
}

void Menu::display()
{
    background.setPosition(0, 0);
    window->draw(background);
}