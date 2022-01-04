#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <cstring>
#include <list>
#include "Point.hpp"

class Node
{
	public:
		/**
         * Constructor of Node 
         */
		Node();

		/**
         * Constructor of Node
         * \param Point* p
         * \param int x
         * \param int y
         */
		Node(Point* p, int c, int h);

		/**
         * Copy constructor of Node 
         * \param Node* n
         */		
		Node(Node* n);

		 /**
         * Destructor of the Point 
         */
		virtual ~Node();

		/**
         * Returns pos
         * \return Point* pos
         */
		Point getPosition();

		/**
         * Returns cost
         * \return int cost
         */
		int getCost();

		/**
         * Returns heuristic
         * \return int heuristic
         */
		int getHeuristic();

		/**
         * Returns x of position
         * \return int x
         */
		int getX();

		/**
         * Returns y of position
         * \return int y
         */
		int getY();

		/**
         * Set the position
         * \param Point* p
         */
		void setPosition(Point* p); 

		/**
         * Set cost
         * \param int cost
         */
		void setCost(int newCost);

		/**
         * Set heuristic
         * \param int heuristic
         */
		void setHeuristic(int newHeuristic);

	private:
		Point pos;
		int cost;
		int heuristic;

	
};

namespace AStar
{
	/**
     * AStar alogorithm
     * \return list<Point> way
     */
	list<Point> way(int** mat, int nbCol, int nbRow, Point start, Point goal);

	/**
     * returns the point with the smallest heuristic around the current point
     * \return Node n
     */
	Node bestAdj(Node n1, list<Node> l);

	/**
	 * Go up the agorithm to find the shortest path
	 * \return list<Poin> way
	 */
	list<Point> way(list<Node> l);
}

#endif //NODE_HPP