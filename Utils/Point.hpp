#ifndef POINT_H
#define POINT_H

#include <cstdlib>
#include <cstdio>
#include <string>
#include <math.h>

using namespace std;

class Point

{
    public:
        /**
         * Constructor of Point 
         */
        Point();

        Point(Point* p);

        /**
         * Constructor of Point 
         * \param int x
         * \param int y
         */
        Point(int x, int y);

        /**
         * Destructor of the Point 
         */
        virtual ~Point();

        /**
         * Returns x
         * \return int x
         */
        int getX();

        /**
         * Returns y
         * \return int y
         */
        int getY();

        /**
         * Set x
         * \param int newX
         */
        void setX(int newX);

        /**
         * Set y
         * \param int newY
         */
        void setY(int newY);

        /**
         * Move the point, add changeX and changeY to x and y
         */
        void move(int changeX, int changeY);

        /**
         * Returns distance between two Point
         * \return int distance between two Point
         */
        int distance(Point* p);

        /**
         * Displays the point in the consol
         * \return string 
         */
        string toString();

        bool operator==(Point* b);

    private:
        int x;
        int y;
    
};

#endif //POINT_H