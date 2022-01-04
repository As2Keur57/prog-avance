#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>
#include "Utils/Point.hpp"
#include "Constants.hpp"

using namespace std;

class GameObject
{
	public:
		/**
         * Constructor of GameObject
         * \param Point* p  
         * \param string path 
         */
		GameObject(Point* p, string path);

		/**
         * Constructor of GameObject
         * \param Point* p  
         * \param string path
         * \param int x
         * \param int y
         * \param int width
         * \param int height
         */
		GameObject(Point* p, string path, int x, int y, int width, int height);

		/**
         * Destructor of the GameObject
         */
		virtual ~GameObject();

		/**
         * Graphical display
         */
		//virtual void display();

		/**
         * Returns the position
         * \return Point the position
         */
		Point* getPosition();

		/**
		 * Set the position 
		 */
		void setPosition(Point* p);

		/**
		 * Displays the GameObject in the console
		 * \return string 
		 */
		string toString();

	protected:
		Point* position = NULL;
		sf::Texture texture;

};

#endif //GAMEOBJECTS_H