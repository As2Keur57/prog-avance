#include "Map.hpp"
#include <time.h>
#include <stdio.h>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
	cout << "hi" << endl;
	Map* test = Map::load("test.map", "../Resources/pavage.bmp");
	cout << "ff" << endl;

	sf::RenderWindow window(sf::VideoMode(test->getX()*32, test->getY()*32), "SFML works!");
    
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

		        // we don't process other types of events
		        default:
		            break;
		    }
        }

        window.clear();
        test->display(&window);
        window.display();
    }

	delete(test);
}