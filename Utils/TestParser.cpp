#include "Parser.hpp"

#include "../GameObjects/Sprite/Player.hpp"
#include "../GameObjects/Map.hpp"

int main() 
{
	Player* p = new Player(100, 4, 2, 0, new Point(0,0), "Resources/Actor1.png", "Resources/Bullet.png", 0, 0, 96, 128);

	Parser::savePlayer(p);

	delete p;
	return 1;
}