#ifndef CONSTANTES_HPP
#define CONSTANTES_HPP

//SPRITE//

#define MAP_SIZE 30
#define TEXTURE_SIZE 32

//PLAYER//

#define PLAYER_SIZE 32

#define PLAYER_LIFE 100
#define PLAYER_EXPERIENCE 0
#define PLAYER_LEVEL 1
#define PLAYER_DEFENSE 10
#define PLAYER_MOVEMENT 8

#define UPTDATE_LIFE 10

//BULLET//

#define BULLET_SIZE 5

#define BULLET_RANGE 5
#define BULLET_ATTACK 10
#define BULLET_MOVEMENT 10

//ENEMIES//

#define NB_ENEMIES 5
#define SPEED_ENEMIES 50

//RESOURCES//

#define TEXTURE_PLAYER "Resources/Actor1.png"
#define TEXTURE_MAP "Resources/pavage.bmp"
#define TEXTURE_BULLET "Resources/Bullet.png"
#define FONT "Resources/font.ttf"

//TEXTS//

#define TITLE_CHAR_SIZE 50
#define TEXT_CHAR_SIZE 32
#define SMALL_TEXT_CHAR_SIZE 20

//GAME//

#define WAIT 3

//MULTIPLAYER//

#define NB_PLAYERS 2
#define HOST "45.87.80.1"
#define DBNAME "u177450303_members"
#define LOGIN "u177450303_iiztpmat"
#define PASSWORD "sF[9#mFxW"

//MENU CHOICES//

enum type{NOCHOICE, SINGLE, MULTI, QUIT};

#endif