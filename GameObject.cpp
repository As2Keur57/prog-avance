#include "GameObject.hpp"

GameObject::GameObject(Point* p, string path)
{
	this->position = p;
	this->texture.loadFromFile(path);
}

GameObject::GameObject(Point* p, string path, int x, int y, int width, int height)
{
	this->position = p;
	this->texture.loadFromFile(path, sf::IntRect(x, y, width, height));
}

GameObject::~GameObject()
{
	delete position;
}


Point* GameObject::getPosition()
{
	return position;
}

void GameObject::setPosition(Point* p)
{
	if(position != NULL)
		delete position;

	position = p;
}

string GameObject::toString()
{
	return position->toString();
}