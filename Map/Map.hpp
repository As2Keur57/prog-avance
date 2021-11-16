#ifndef MAP_H
#define MAP_H

#include "../GameObject.hpp"
#include <fstream>
#include <ctime>
#include <algorithm>

using namespace std;

class Map : public GameObject
{
	public:
		/*
		 * Constructor of Map with x column and y line 
		 * \param int x
		 * \param int y
		 */
		Map(int x, int y);

		/*
		 * Constructor of Map with x column and y line 
		 * \param Point* pos
		 */
		Map(Point* pos);

		/*
		 * Load textures form file
		 * \param string texturePath
		 */
		void loadTextures(string texturePath);

		/*
		 * Destructor of Map
		 */
		virtual ~Map();

		/*
		 * Generates a random map
		 */
		void generate();
		
		/*
		 * Generates a random correct map
		*/
		void generateEffective();

		/*
		 * Saves the current map in a file
		 * \param const string path
		 */
		void save(const string path);

		/*
		 * Extract the size of the map from a file as a Point
		 * \param const string path 
		 */
		static Point* getPointFromFile(const string path);

		/*
		 * Loads the map from a file
		 * \param string path : The path of the file
		 */
		static Map* load(const string path);

		/*
		 * Get map in a 2 dimensions table
		 */
		int** getMap();

		/*
		 * Get the number of lines
		 */
		int getY();

		/*
		 * Check if the map is correct
		 */
		bool isEffective();

		/*
		 * Get the number of columns
		 */
		int getX();

		/*
		 * Checks if there is a wall on the point (x,y)
		 * \param int x
		 * \param int y 
		 */
		bool isWall(int x, int y);

		/*
		 * Get the number of walls linearly to the point (x, y)
		 * \param int x
		 * \param int y 
		 */
		int countWallsAround(int x, int y);

		/*
		 * Return the value of Map on the point (x,y)
		 * \param int x
		 * \param int y 
		 * \return int 
		 */
		int getValue(int x, int y);

		/**
         * Replaces one int in the position "i,j"
         * \param int i : line number
         * \param int j : column number
         * \param int newInt
         */
		void setInt(int i, int j, int newInt);

		/*
		 * Remove the wall around a box if necessary
		 * \param int x
		 * \param int y 
		 */
		void deleteAround(int x, int y);

		/*
		 * Change all of the occurrences of an int to another int
		 * \param int before : old int
		 * \param int after : new int
		 */
		void changeInt(int before, int after);

		/*
		 * display the map on standard output
		 */
		void displayRaw();

		/*
		 * display the map on sfml window
		 * \param sf::RenderWindow* window
		 */
		void display(sf::RenderWindow* window);

	private:
		void loadTextures();
		int** table;
		sf::Sprite tile[2];
};

#endif