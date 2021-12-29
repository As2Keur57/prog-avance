#include <cstdlib>
#include <iostream>

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "../Sprite.hpp"
#include "../../GameObject.hpp"

using namespace  std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::Texture texture;

    texture.loadFromFile("Resources/Actor1.png", sf::IntRect(288, 0, 96, 128));

    Player* s = new Player(100, 5000, 600,100000, 1000000, "string imagePath", new Point(50,50));
    
	sf::Event event;

    while (window.isOpen())
    {

        while (window.pollEvent(event))
        {
            switch (event.type)
		    {
		        // window closed
		        case sf::Event::Closed:
		            window.close();
		            break;

		        // key pressed
		        case sf::Event::KeyPressed:
		        	switch(event.key.code)
		            {
		            	case sf::Keyboard::Q:
		            		s->move('Q');
		            		break;
		            	case sf::Keyboard::D:
		            		s->move('D');
		            		break;
		            	case sf::Keyboard::Z:
		            		s->move('Z');
		            		break;
		            	case sf::Keyboard::S:
		            		s->move('S');
		            		break;
		            }
		            break;

		        // we don't process other types of events
		        default:
		            break;
		    }
        }

        window.clear();
        s->display(&window, &texture, 0,0);
        window.display();
    }

    delete s;
    return 0;
}