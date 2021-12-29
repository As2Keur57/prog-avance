#include "Sprite.hpp"

Sprite::Sprite(int height, int width, int movement, bool visible, Point* pos, string path) : GameObject(pos, path)
{
	this->height = height;
	this->width = width;
	this->movement = movement;
	this->visible = visible;
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(pos->getX(), pos->getY());
	this->way = 'Z';
	this->anmX = 0;
	this->anmY = 0;
}

Sprite::Sprite(int height, int width, int movement, bool visible, Point* pos, string path, int x, int y, int w, int h) : GameObject(pos, path, x, y, w, h)
{
	this->height = height;
	this->width = width;
	this->movement = movement;
	this->visible = visible;
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(pos->getX(), pos->getY());
	this->way = 'Z';
	this->anmX = 0;
	this->anmY = 0;
}

Sprite::~Sprite()
{
	
}

//Getter
int Sprite::getWidth() const
{
	return width;
}

int Sprite::getHeight() const
{
	return height;
}

int Sprite::getMovement() const
{
	return movement;
}

bool Sprite::isVisible() const
{
	return visible;
}

void Sprite::setWidth(int w)
{
	width = w;
}

void Sprite::setHeight(int h)
{
	height = h;
}

void Sprite::setVisible(bool v)
{
	visible = v;
}

void Sprite::setMovement(int m)
{
	movement = m;
}

int Sprite::getX() const
{
	return this->position->getX();
}

int Sprite::getY() const
{
	return this->position->getY();
}

char Sprite::getWay() const
{
	return way;
}

void Sprite::setWay(char newWay)
{
	this->way = newWay;
}

int Sprite::getAnimX()
{
	return anmX;
}

void Sprite::setAnimX(int nb)
{
	this->anmX = nb;
}

void Sprite::setAnimY(int nb)
{
	this->anmY = nb;
}

int Sprite::getAnimY()
{
	return anmY;
}

void Sprite::animX() {}
void Sprite::animY() {}

void Sprite::move()
{
	if(this->way == '\n') return;
	
	switch(this->way)
	{
		case 'Q':
		case 'q':
			this->getPosition()->move(-movement, 0);
		    break;
       	case 'D':
       	case 'd':
       		this->getPosition()->move(movement, 0);
       		break;
       	case 'Z':
       	case 'z':
       		this->getPosition()->move(0, -movement);
       		break;
       	case 'S':
       	case 's':     
       		this->getPosition()->move(0, movement);	
       		break;
	}
	this->animX();
    this->animY();
	sprite.setPosition(this->getPosition()->getX(), this->getPosition()->getY());
}

void Sprite::display(sf::RenderWindow* window, int x, int y)
{
	if(visible)
	{
		sprite.setTextureRect(sf::IntRect(x, y, width,height));
		window->draw(sprite);
	}
}

//Methods
string Sprite::toString()
{
	return NULL;
}

sf::Sprite Sprite::getSprite() const
{
	return sprite;
}