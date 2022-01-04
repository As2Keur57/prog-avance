#ifndef PARSER_HPP
#define PARSER_HPP

#include "../GameObjects/Sprite/Player.hpp"
#include "../GameObjects/Map.hpp"
#include "../Constants.hpp"
#include <boost/filesystem.hpp>
#include <bits/stdc++.h> 
#include <iostream> 
#include <sys/stat.h> 
#include <sys/types.h> 

class Parser
{
	public:
		/*
		 * Return a Player load from file
		 * \param const string nameFile
		 * \param Point* position
		 * \return Player* 
		 */
		static Player* loadPlayer(const string nameFile, Point* position);

		/*
		 * Save Player in file
		 * \param Player* p 
		 */
		static void savePlayer(Player* p);

		/*
		 * Return a Map load from file
		 * \param const string nameFile
		 * \return Map* 
		 */
		static Map* loadMap(const string nameFile);

		/*
		 * Save Map in file  
		 * \param Map* m
		 * \param const string nameFile
		 */
		static void saveMap(Map* m, const string nameFile);

		/*
		 * Return Point like x = max collunm and y = max line in file
		 * \param const string path
		 * \return Point* 
		 */
		static Point* getPointFromFile(const string path);


		/*
		 * Return the first int in a string
		 * \param string chain
		 * \return int
		 */
		static int searchInt(string chain);

	private:
		/*
		 * Constructor of Parser
		 */
		Parser();

		/*
		 * Destructor of Parser
		 */
		~Parser();
	
};

#endif //PARSER_HPP