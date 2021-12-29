#ifndef SPRITE_H
#define SPRITE_H

#include "../GameObject.hpp"

using namespace std;

class Sprite : public GameObject
{
	public:

		/**
		 * Constructor of Sprite
		 * \param int height
		 * \param int width
		 * \param int movement
		 * \param bool visible
		 * \param Point* pos
		 * \param string path 
		 */
		Sprite(int height, int width, int movement, bool visible, Point* pos, string path);

		/**
		 * Constructor of Sprite
		 * \param int height
		 * \param int width
		 * \param int movement
		 * \param bool visible
		 * \param Point* pos
		 * \param string path 
		 * \param int x 
		 * \param int y 
		 * \param int w 
		 * \param int h 
		 */
		Sprite(int height, int width, int movement, bool visible, Point* pos, string path, int x, int y, int w, int h);

		/**
		 * Destructor of Sprite
		 */
		virtual ~Sprite();

		/**
		 * Returns height
		 * \return int
		 */
		int getHeight() const;

		/**
		 * Returns width
		 * \return int
		 */
		int getWidth() const;

		/**
		 * Returns movement
		 * \return int
		 */
		int getMovement() const;

		/**
		 * Returns visible
		 * \return bool
		 */
		bool isVisible() const;

		/**
		 * Set width
		 * \param int w
		 */
		void setWidth(int w);

		/**
		 * Set height
		 * \param int h
		 */
		void setHeight(int h);

		/**
		 * Set visible
		 * \param bool v
		 */
		void setVisible(bool v);

		/**
		 * Set movement
		 * \param int movement
		 */
		void setMovement(int m);

		/**
		 * Move the sprite
		 */
		void move();

		/**
		 * Return the way of sprite
		 * \return char way
		 */
		char getWay() const;

		/**
		 * Set the way of sprite
		 * \param char way
		 */
		void setWay(char newWay);

		/**
		 * Displays the Sprite on SFML window
		 */
		void display(sf::RenderWindow* window, int x, int y);

		/*
		 * Return the player abscissa ? 
		 * return int
		 */
		int getX() const;

		/*
		 * Return ordinate of the player
		 * \return int
		 */
		int getY() const;

		/*
		 * Return the sfml sprite
		 * \return sh::Sprite
		 */
		sf::Sprite getSprite() const;

		/*
		 * Return anmX
		 * \return anmX
		 */
		int getAnimX();

		/*
		 * Return anmY
		 * \return anmY
		 */
		int getAnimY();

		/*
		 * Set anmX
		 * \param int nb
		 */
		void setAnimX(int nb);

		/*
		 * Set anmY
		 * \param int nb
		 */
		void setAnimY(int nb);

		/*
		 * Sprite animation on sfml window
		 */
		virtual void animX();

		/*
		 * Sprite animation on sfml window
		 */
		virtual void animY();

		/**
		 * Displays the Sprite in the consol
		 * \return string 
		 */
		virtual string toString()=0;


	protected:
		int height;
		int width;
		int movement;
		bool visible;
		char way;
		sf::Sprite sprite;

		int anmX;
		int anmY;

};

#endif //SPRITE_H