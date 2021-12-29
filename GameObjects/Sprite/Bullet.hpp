#ifndef BULLET_HPP
#define BULLET_HPP

#include "../Sprite.hpp"
#include "Player.hpp"

class Player;

class Bullet : public Sprite
{
	public:
        /*
         * Constructor of Bullet
         * \param int range
         * \param int attack
         * \param Player* player
         * \param string path
         */
		Bullet(int range, int attack, Player* player, string path);

        /*
         * Destructor of the Bullet
         */
		~Bullet();

        /**
         * Returns the Bullet attack 
         * \return int attack
         */
        int getAttack();

    	/**
         * Set the attack of the Bullet  
         * \param int atk 
         */
    	void setAttack(int atk);

        void reinit();

        /*
         * Returns the Bullet range 
         * \return int attack
         */
        int getRange();

        void move();

    	/**
         * Set the range of the Bullet  
         * \param int atk 
         */
    	void setRange(int range);

    	/**
         * Displays the Bullet in the console
         * \return string 
         */
        string toString();

        /**
         * Return the bullet player
         * \return Player* 
         */
        Player* getPlayer();

	private:
    	int range;
    	int attack;
        int rangeMax;
        Player* player;
};

#endif //BULLET_HPP