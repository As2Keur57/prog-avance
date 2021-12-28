#include "SingleGame.hpp"

SingleGame::SingleGame(string playerUUID, sf::RenderWindow* window) : Game(window)
{
	this->ai = new Player*[NB_ENEMIES];
    for(int i = 0; i < NB_ENEMIES; i++)
    {
        this->ai[i] = NULL;
        this->ai[i] = new Player("", this->getFreePoint(), 288, 0, 96, 128);
    }

    Point* freePoint = this->getFreePoint();
    Player* playerFromFile = Parser::loadPlayer(playerUUID, freePoint);

    if(playerFromFile == NULL)  this->player = new Player(playerUUID, freePoint, 0, 0, 96, 128);
    else    this->player = playerFromFile;
}

SingleGame::SingleGame(Map* map, string playerUUID, sf::RenderWindow* window) : Game(map, window)
{
    this->ai = new Player*[NB_ENEMIES];
    for(int i = 0; i < NB_ENEMIES; i++)
    {
        this->ai[i] = NULL;
        this->ai[i] = new Player("", this->getFreePoint(), 288, 0, 96, 128);
    }

    Point* freePoint = this->getFreePoint();
    Player* playerFromFile = Parser::loadPlayer(playerUUID, freePoint);

    if(playerFromFile == NULL)  this->player = new Player(playerUUID, freePoint, 0, 0, 96, 128);
    else    this->player = playerFromFile;
}

SingleGame::~SingleGame()
{
    for(int i = 0; i < NB_ENEMIES; i++)
    {
        delete this->ai[i];
    }
    delete [] this->ai;
}

Player** SingleGame::getAi()
{
    return this->ai;
}

void SingleGame::handleBulletMovement()
{
    player->getBullet()->move();
    if(this->mapCollision(player->getBullet()))
        player->getBullet()->reinit();
    
    for(int i = 0; i < NB_ENEMIES; i++)
    {
        Player* ai = this->getAi()[i];
        ai->getBullet()->move();
        if(this->mapCollision(ai->getBullet()))
            ai->getBullet()->reinit();
    }
}

int SingleGame::getRank()
{
    int rank = NB_ENEMIES+1;
    for(int i = 0; i < NB_ENEMIES; i++)
    {
        if(!this->ai[i]->isVisible())
            rank--;
    }

    return rank;
}

Point* SingleGame::getFreePoint()
{
    srand(time(0));
    Point* freePoint;

    while(true)
    {
        freePoint = new Point((rand()%this->map->getX())*TEXTURE_SIZE, (rand()%this->map->getY())*TEXTURE_SIZE);

        //We test if the point isn't on a wall
        if(map->isWall((freePoint->getX()/TEXTURE_SIZE), (freePoint->getY()/TEXTURE_SIZE))) continue;


        //We test if the point isn't on the player
        if(this->player != NULL)
            if(player->getX() == freePoint->getX())
                if(player->getY() == freePoint->getY())
                    continue;

        //We test if the point isn't on the AIs
        if(this->ai != NULL)
        {
            bool isOnAi = false;
            for(int i = 0; i < NB_ENEMIES; i++)
            {
                if(ai[i] == NULL) break;

                if(ai[i]->getX() == freePoint->getX())
                    if(ai[i]->getY() == freePoint->getY())
                        isOnAi = true;
            }

            if(isOnAi) continue;
        }

        //if we went through all the test it's that the point is a free point, else we do again these operations
        return freePoint;
    }
    return NULL;
}

Player* SingleGame::nearestEnemy(int aiIndex)
{
    Player* ai;
    Player* res = NULL;

    for(int i = 0; i < NB_ENEMIES; i++)
    {
        ai = this->ai[i];
        if((i == aiIndex) || !ai->isVisible()) continue;

        if(res == NULL)
        	res = ai;

        if(res->getPosition()->distance(this->ai[aiIndex]->getPosition()) > ai->getPosition()->distance(this->ai[aiIndex]->getPosition())) 
        {
            res = ai;
        }
    }

    if(this->player->isVisible())
	    if(res == NULL || res->getPosition()->distance(this->ai[aiIndex]->getPosition()) > player->getPosition()->distance(this->ai[aiIndex]->getPosition()))
	    	res = player;

    return res;
}

void SingleGame::moveAi()
{
	sf::sleep(sf::milliseconds(SPEED_ENEMIES));
	char dir;
    Map* map = this->getMap();
    Player* ai;
    Player* near;
    Point goal;
    Point posAi;

    for(int i = 0; i < NB_ENEMIES; i++)
    {
        ai = this->ai[i];

        if(!ai->isVisible()) continue;
        
        near = nearestEnemy(i);

        if(near == NULL) break;
        
        goal = Point(near->getX()/TEXTURE_SIZE, near->getY()/TEXTURE_SIZE);
        posAi = Point(ai->getX()/TEXTURE_SIZE, ai->getY()/TEXTURE_SIZE);

        list<Point> goalWay = makeWay(AStar::way(map->getMap(), map->getY(), map->getX(), posAi, goal));

        if(goalWay.size() > 0 && ai->getX() % TEXTURE_SIZE == 0 && ai->getY() % TEXTURE_SIZE == 0)
        {
            goalWay.pop_front();
            goal = goalWay.front();
	        if(goal.getX() == posAi.getX() && goal.getY() == posAi.getY() - 1)		dir = 'Z';
	        if(goal.getX() == posAi.getX() && goal.getY() == posAi.getY() + 1)		dir = 'S';
	        if(goal.getX() == posAi.getX() - 1 && goal.getY() == posAi.getY())		dir = 'Q';
	        if(goal.getX() == posAi.getX() + 1 && goal.getY() == posAi.getY())		dir = 'D';
	        ai->setWay(dir);
        }

        if(goalWay.size() > 0 || ai->getX() % TEXTURE_SIZE != 0 || ai->getY() % TEXTURE_SIZE != 0)	ai->move();
        else
        {
            ai->setWay(dirEnemy(ai, near->getPosition()));
            ai->animY();
            ai->shoot();
        }

    }
}


list<Point> SingleGame::makeWay(list<Point> way)
{

    if(way.size() <= BULLET_RANGE)
    {
        bool sameX = true;
        bool sameY = true;
        list<Point>::reverse_iterator it = way.rend();

        Point goal = way.back();

        for(list<Point>::reverse_iterator it = way.rbegin(); it != way.rend(); it++)
        {
            Point curr = *it;

            if(curr.getX() != goal.getX())
            {
                sameX = false;
            }
            if(curr.getY() != goal.getY())
            {
                sameY = false;
            }
        }

        if(sameY || sameX)
            way.clear();
        
    }

    return way;

}

char SingleGame::dirEnemy(Player* player, Point* goal)
{
    char res = player->getWay();
    Point* posPlayer = player->getPosition();

    if(posPlayer->getX() == goal->getX())
    {
        if(posPlayer->getY() < goal->getY())
            res = 'S';
        else 
            res = 'Z';
    } else  if(posPlayer->getY() == goal->getY()){
        if(posPlayer->getX() < goal->getX())
            res = 'D';
        else 
            res = 'Q';
    }

    return res;
}

void SingleGame::display()
{
    window->clear();
    map->display(window);
    player->display(window, player->getAnimX(),player->getAnimY());
    player->getBullet()->display(window, 174, 192);
    for(int i = 0; i < NB_ENEMIES; i++)
    {
        ai[i]->getBullet()->display(window, 174, 192);
        ai[i]->display(window, ai[i]->getAnimX(),ai[i]->getAnimY());
    }
    window->display();
}

void SingleGame::handleCollision()
{
    Player* mainPlayer = this->player;

    for(int i = 0; i < NB_ENEMIES; i++)
    {
        Player* ai = this->ai[i];
        if(ai->isVisible())
        {
            Bullet* bullet = ai->getBullet();
            if(bullet->isVisible())
            {
                for(int j = 0; j < NB_ENEMIES; j++)
                {
                    if(this->isCollision(bullet, player))
                    {
                        deathHandler(bullet, player);
                    }
                    if(i == j) continue;
                    Player* collider = this->ai[j];
                    if(this->isCollision(bullet, collider))
                    {
                        deathHandler(bullet, collider);
                    }
                }
            }
        }
    }

    Bullet* playerBullet = player->getBullet();

    if(playerBullet->isVisible())
    {
        for(int i = 0; i < NB_ENEMIES; i++)
        {
            if(ai[i]->isVisible())
            {
                Player* collider = this->ai[i];
                if(this->isCollision(playerBullet, collider))
                {
                    deathHandler(playerBullet, collider);
                }
            }
        }
    }
}

bool SingleGame::isEnd()
{
    bool res = false;
    int inLife = 0;

    for(int i = 0; i < NB_ENEMIES; i++)
    {
        if(ai[i]->isVisible()) inLife++;
    }

    if(player->isVisible()) inLife++;

    return inLife <= 1 || !player->isVisible();
}
