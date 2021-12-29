#ifndef PLAYER_H
#define PLAYER_H

#include "../Sprite.hpp"
#include "Bullet.hpp"

class Bullet;

using namespace std;

class Player : public Sprite
{
	public:

		/**
             * Constructor of Player 
             * \param string playerUUID
             * \param Point* pos
             * \param int x
             * \param int y
             * \param int width
             * \param int height
             */
            Player(string playerUUID, Point* pos, int x, int y, int width, int height);

		/**
             * Destructor of the player 
             */
		virtual ~Player();

		/**
             * Levels up the player  
             */
		void levelUp();

            /**
             * Update the number of kills  
             */
            void updateKills();

            /**
             * Update the number of damages  
             */
            void updateDamages();

		/**
             * Updates the player life
             * \param int damages 
             */
		void updateLife(int damages);

		/**
             * Updates the player experience
             * \param int xp  
             */
		void updateExperience(int xp);

            /**
             * Set  the player experience
             * \param int xp  
             */
            void setExperience(int xp);

            /*
             * Display the Player on sfml window on position (x,y)
             * \param sf::RenderWindow* window
             * \param int x
             * \param int y
             */
            void display(sf::RenderWindow* window, int x, int y);

		/**
             * Returns true if the player is alive
             * \return bool if the player is alive
             */
		bool isAlive();

            /*
             * Return the player number kills
             * \return int
             */
            int getKills() const;

            /*
             * Return the player damages
             * \return int
             */
            int getDamages() const;

            /*
             * Return the player experience
             * \return int
             */
            int getExperience() const;

            void setLevel(int lvl);

		/**
             * Returns the player level 
             * \return int level
             */
		int getLevel() const;

            /**
             * Set the player life
             * \param int life  
             */
            void setLife(int life);

		/**
             * Returns the player level 
             * \return int life 
             */
		int getLife() const;

            /**
             * Returns the player uuid 
             * \return string uuid
             */
            string getUuid() const;

            /**
             * Set the uuid of the player
             * \param string uuid 
             */
            void setUuid(string uuid);

		/**
             * Returns the player level 
             * \return int defense
             */
		int getDefense() const;

		/**
             * Set the defense of the player  
             * \param int def 
             */
		void setDefense(int def);

            /**
             * Returns the player level 
             * \return int attack
             */
            int getAttack() const;

            /*
             * Allows the player to shoot
             */
            void shoot();

            /**
             * Returns the player bullet 
             * \return Bullet* bullet
             */
            Bullet* getBullet() const;


            /**
             * Walking animation
             */
            void animX();

            /**
             * Direction animation
             */
            void animY();

            /*
             * Return the player point level 
             * \return int 
             */
            int getPointLevel();

            /*
             * Set the player point level 
             * \param int nb
             */
            void setPointLevel(int nb);

            /*
             * Return the player point defense 
             * \return int 
             */
            int getPointDefense();

            /*
             * Set the player point defense 
             * \param int nb
             */
            void setPointDefense(int nb);

            /*
             * Return the player point attack 
             * \return int 
             */
            int getPointAttack();

            /*
             * Set the player point attack 
             * \param int nb
             */
            void setPointAttack(int nb);

<<<<<<< HEAD
            int getPointLife();
            void setPointLife(int nb);

=======
            /*
             * Return the player point life 
             * \return int 
             */
            int getPointLife();

            /*
             * Set the player point life 
             * \param int nb
             */
            void setPointLife(int nb);

            /*
             * Update the player life, defense and attack according to point life, point defense and point attack
             */
>>>>>>> 7e4874d20db622347b6835912c3b633d6c47e90c
            void updateStat();

            /**
             * Displays the Player in the console
             * \return string 
             */
            string toString();

	protected:
            string uuid;
            int level = PLAYER_LEVEL;
            int experience = PLAYER_EXPERIENCE;
            int life = PLAYER_LIFE;
            int defense = PLAYER_DEFENSE;
            Bullet* bullet;
            int nbKills = 0;
            int nbDamages = 0;
            int pointLevel = 0;
            int pointDefense = 0;
            int pointAttack = 0;
            int pointLife = 0;
};

#endif //PLAYER_H