#include "Bullet.hpp"

Bullet::Bullet(int range, int attack, Player* player, string path) : Sprite(BULLET_SIZE, BULLET_SIZE, BULLET_MOVEMENT, false, new Point(player->getX()-(player->getHeight()/2), player->getY()-(player->getWidth()/2)), path)
{
	this->rangeMax = range;
	this->range = range*TEXTURE_SIZE;
	this->attack = attack;
	this->player = player;
}

Bullet::~Bullet()
{

}

void Bullet::reinit()
{
	this->setVisible(false);
	delete(this->position);
	this->position = new Point(player->getX()+(player->getHeight()/2), player->getY()+(player->getWidth()/2));
	this->range = rangeMax*TEXTURE_SIZE;
}

void Bullet::move()
{
	if(this->isVisible())
	{
		this->range -= BULLET_MOVEMENT;
		if(this->range <= 0)
		{
			this->reinit();
		}
		this->Sprite::move();
	}
	else
	{
		this->position->setX(player->getX()+(player->getWidth()/2));
		this->position->setY(player->getY()+(player->getHeight()/2));
		this->setWay(player->getWay());
	}
	this->getSprite().setPosition(this->getPosition()->getX(), this->getPosition()->getY());
}

int Bullet::getAttack()
{
	return attack;
}

void Bullet::setAttack(int atk)
{
	this->attack = attack;
}

int Bullet::getRange()
{
	return range;
}

void Bullet::setRange(int range)
{
	this->range = range;
}

Player* Bullet::getPlayer()
{
	return this->player;
}

string Bullet::toString()
{
	return "Bullet : attack = " + to_string(attack) + " & range = " + to_string(range);
}