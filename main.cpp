#include "Menu.hpp"
#include "Games/MultiGame.hpp"

using namespace std;

int main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(30*TEXTURE_SIZE, 30*TEXTURE_SIZE), "BRUni");
	/*sf::RenderWindow* window;
    MultiGame* game = new MultiGame("iiztp", window);
    game->waitingRoom();

    while(window->isOpen())
    {
    	game->handleEvents();
    	game->display();
    }

    delete game;*/

	Menu* menu = new Menu(new Point(MAP_SIZE,MAP_SIZE));

	menu->choiceGame();

	delete menu;

    return 0;
}