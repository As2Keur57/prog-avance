#include "Player.hpp"

Player::Player(string playerUUID, Point* pos, int x, int y, int width, int height) : Sprite(PLAYER_SIZE, PLAYER_SIZE, PLAYER_MOVEMENT, true, pos, TEXTURE_PLAYER, x, y, width, height)
{
   this->life = PLAYER_LIFE;
   this->experience = PLAYER_EXPERIENCE;
   this->level = PLAYER_LEVEL;
   this->defense = PLAYER_DEFENSE;
   this->bullet = new Bullet(BULLET_RANGE, BULLET_ATTACK, this, TEXTURE_BULLET);
   this->uuid = playerUUID;
}

Player::~Player()
{
   delete this->bullet;
}

void Player::setLife(int life)
{
   this->life = life;
}

void Player::levelUp()
{
   level++;
   pointLevel++;
}

void Player::setLevel(int lvl)
{
   this->level = lvl;
}


void Player::updateLife(int damages)
{
   life -= damages;
}

void Player::display(sf::RenderWindow* window, int x, int y)
{
   if(visible)
   {
      sf::RectangleShape rectangle(sf::Vector2f((int)(this->getLife()*0.32), 3));
      rectangle.setPosition(this->getX(), this->getY()-5);
      rectangle.setFillColor(sf::Color(255, 0, 0));
      rectangle.setOutlineThickness(1);
      rectangle.setOutlineColor(sf::Color(0, 0, 0));

      sprite.setTextureRect(sf::IntRect(x, y, width,height));
      window->draw(sprite);
      window->draw(rectangle);
   }
}

void Player::updateExperience(int xp)
{
   experience += xp;
}

bool Player::isAlive()
{
   return life > 0;
}


int Player::getLevel() const
{
   return level;
}

int Player::getKills() const
{
   return this->nbKills;
}

int Player::getDamages() const
{
   return this->nbDamages;
}

int Player::getLife() const
{
   return life;
}

int Player::getDefense() const
{
   return defense;
}

int Player::getExperience() const
{
   return experience;
}

string Player::getUuid() const
{
   return uuid;
}

void Player::updateKills()
{
   this->nbKills++;
}

void Player::updateDamages()
{
   this->nbDamages += this->bullet->getAttack();
}

void Player::setUuid(string uuid)
{
   this->uuid = uuid;
}

void Player::setDefense(int def)
{
   defense = def;
}

void Player::setExperience(int xp)
{
   this->experience = xp;
}

int Player::getAttack() const
{
   return this->bullet->getAttack();
}

void Player::shoot()
{
   if(bullet->isVisible())
      return;

   bullet->setVisible(true);
   bullet->setWay(this->getWay());
}

Bullet* Player::getBullet() const
{
   return this->bullet;
}

void Player::animX()
{
   if(getAnimX() < 2*TEXTURE_SIZE)
   {
      setAnimX(getAnimX() + TEXTURE_SIZE);
   } else {
      setAnimX(0);
   }
}

void Player::animY()
{
   switch(this->getWay())
   {
      case 'S':
         setAnimY(0);
         break;
      case 'D':
         setAnimY(2 * TEXTURE_SIZE);
         break;
      case 'Q':
         setAnimY(1 * TEXTURE_SIZE);
         break;
      case 'Z':
         setAnimY(3 * TEXTURE_SIZE);
         break;
   }
}

int Player::getPointLevel()
{
   return pointLevel;
}

void Player::setPointLevel(int nb)
{
   pointLevel = nb;
}

int Player::getPointDefense()
{
   return pointDefense;
}

void Player::setPointDefense(int nb)
{
   pointDefense = nb;
}

int Player::getPointAttack()
{ 
   return pointAttack;
}

void Player::setPointAttack(int nb)
{
   pointAttack = nb;
}

int Player::getPointLife()
{ 
   return pointLife;
}

void Player::setPointLife(int nb)
{
   pointLife = nb;
}
void Player::updateStat()
{
   defense = PLAYER_DEFENSE + pointDefense;
   bullet->setAttack(bullet->getAttack() + pointAttack);
   life = PLAYER_LIFE + UPTDATE_LIFE*pointLife;
<<<<<<< HEAD
=======
   cout<<life<<endl;
>>>>>>> 7e4874d20db622347b6835912c3b633d6c47e90c
}

string Player::toString()
{
   return NULL;
}
