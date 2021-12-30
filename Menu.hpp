#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include "Utils/Point.hpp"
#include "GameObjects/Map.hpp"
#include "Constants.hpp"
#include "Games/SingleGame.hpp"

class Menu
{
	public:
		/** 
		 * Constructor of menu 
		 * \param Point* pos
		 */
		Menu(Point* pos);

		/** 
		 * destructor of menu 
		 */
		~Menu();


		/**
		 * Mange the different menu and choice on it
		 */
		void choiceGame();

		/**
		 * Countdown menu befor start game 
		 */
		int loadGame(int choice);

		/**
		 * Display the principal menu
		 */
		int handleMenu(string* pseudo);

		/**
		 * Display the update statistic menu
		 */
		int pointMenu(string pseudo);

		/**
		 * Display background of all menu
		 */
		void display();


	private:
		sf::Sprite background;
		sf::Texture mapScreen;
		sf::RenderWindow* window;

};

#endif //MENU_HPP