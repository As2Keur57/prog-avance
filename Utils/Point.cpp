#include "Point.hpp"

Point::Point()
{
    x = 0;
    y = 0;
}

Point::Point(Point* p)
{
    this->x = p->getX();
    this->y = p->getY();
}

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

Point::~Point()
{

}

//Getter
int Point::getX()
{
    return x;
}

int Point::getY()
{
    return y;
}

//Setter
void Point::setX(int newX)
{
    x = newX;
}

void Point::setY(int newY)
{
    y = newY;
}

//Method
void Point::move(int changeX, int changeY)
{
    x += changeX;
    y += changeY;
}

int Point::distance(Point* p)
{
    return sqrt((p->getX() - x) * (p->getX() - x) + (p->getY() - y) * (p->getY() - y));
}

string Point::toString()
{
    string s = "Point : X = " + to_string(x) + " Y = " + to_string(y) + "";

    return s;
}

bool Point::operator==(Point* b)
{
    return ((this->getX() == b->getX()) && (this->getY() == b->getY()));
}
