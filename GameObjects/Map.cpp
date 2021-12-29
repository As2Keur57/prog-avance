#include "Map.hpp"

Map::Map(int x, int y) : GameObject(new Point(x, y), TEXTURE_MAP)
{
	this->table = new int*[x];

	for(int i = 0; i < x; i++)
	{
		this->table[i] = new int[y];
	}
	this->loadTextures(TEXTURE_MAP);
}

Map::Map(Point* pos) : GameObject(pos, TEXTURE_MAP)
{
	this->table = new int*[pos->getX()];

	for(int i = 0; i < pos->getX(); i++)
	{
		this->table[i] = new int[pos->getY()];
	}
	this->loadTextures(TEXTURE_MAP);
}

void Map::loadTextures(string texturePath)
{
	this->texture.loadFromFile(texturePath);
	tile[0].setTexture(this->texture);
	tile[0].setTextureRect(sf::IntRect(0, 0, TEXTURE_SIZE, TEXTURE_SIZE));

	tile[1].setTexture(this->texture);
	tile[1].setTextureRect(sf::IntRect(288, 0, TEXTURE_SIZE, TEXTURE_SIZE));
}

Map::~Map()
{
	for(int i = 0; i < this->getX(); i++)
	{
		delete [] this->table[i];
	}
	delete [] this->table;
}

void Map::generateEffective()
{
	do
	{
		this->generate();
	}while(!this->isEffective());
}

int Map::getValue(int x, int y)
{
	return this->table[x][y];
}

void Map::generate()
{
	srand(time(0));

	for(int i = 0; i < this->getX(); i++)
	{
		for(int j = 0; j < this->getY(); j++)
		{
			this->table[i][j] = 0;

			if(i==0||i==this->getX()-1||j == 0||j==this->getY()-1)this->table[i][j]=1;
		}
	}

	for(int i = 2; i < this->getX()-2; i++)
	{
		for(int j = 2; j < this->getY()-2; j++)
		{
			int last = -1;
			int currentX = i;
			int currentY = j;
			while((this->countWallsAround(currentX, currentY) < 2))
			{
				int r = rand()%4;

				while(r%2 == last-1 || (rand()%2 == 1 && r%2 == last)) r = rand()%4;

				switch(rand() % 4)
				{
					case 0:
						currentX++;
						break;
					case 1:
						currentX--;
						break;
					case 2:
						currentY++;
						break;
					case 3:
						currentY--;
						break;
				}

				if((currentX < this->getX()-1) && (currentY < this->getY()-1) && currentX > 0 && currentY > 0)	this->table[currentX][currentY] = 1;
				else break;

				last = r%2;
			}
		}
	}

	for(int i = 1; i < this->getX()-1; i++)
	{
		for(int j = this->getY()-2; j > 0; j--)
		{
			if(this->isWall(i, j)) deleteAround(i, j);
		}
	}
}

bool Map::isEffective()
{
	for(int i = 1; i < this->getX()-1; i++)
	{
		bool isEffective = false;

		for(int j = 0; j < this->getY(); j++)
		{
			if(this->table[i][j] == 0) isEffective = true;
		}

		if(!isEffective) return false;
	}

	for(int j = 1; j < this->getY()-1; j++)
	{
		bool isEffective = false;
		for(int i = 0; i < this->getX(); i++)
		{
			if(this->table[i][j] == 0) isEffective = true;
		}

		if(!isEffective) return false;
	}

	return true;
}

bool Map::isWall(int x, int y)
{
	if(x < 0 || x >= this->getX() || y < 0 || y >= this->getY()) return true;

	return (this->table[x][y] == 1);
}

int Map::countWallsAround(int x, int y)
{
	int nbOfWallsAround = 0;

	if(this->isWall(x+1, y)) nbOfWallsAround++;
	if(this->isWall(x-1, y)) nbOfWallsAround++;
	if(this->isWall(x, y+1)) nbOfWallsAround++;
	if(this->isWall(x, y-1)) nbOfWallsAround++;

	return nbOfWallsAround;
}

void Map::deleteAround(int x, int y)
{
	if(this->isWall(x+1, y+1) && (x+1) < (this->getX()-1) && (y+1) < (this->getY()-1)) this->table[x+1][y+1] = 0;
	if(this->isWall(x-1, y+1) && (x-1) > 0 && (y+1) < (this->getY()-1)) this->table[x-1][y+1] = 0;
	if(this->isWall(x+1, y-1) && (x+1) < (this->getX()-1) && (y-1) > 0) this->table[x+1][y-1] = 0;
	if(this->isWall(x-1, y-1) && (x-1) > 0 && (y-1) > 0) this->table[x+1][y+1] = 0;
}

void Map::save(const string path)
{
	ofstream file(path);
 
    if(file)
    {
    	for(int i = 0; i < this->getX(); i++)
    	{
    		for(int j = 0; j < this->getY(); j++)
    		{
    			file << this->table[i][j];
    		}
    		file << endl;
    	}
    }
    file.close();
}

Point* Map::getPointFromFile(const string path)
{
	ifstream file(path);
	int x = 0;
	int y = 1;
	int line = 0;
	char c;
	while(file.get(c))
    {
    	if(c == '\n')
    	{
    		if(x >= line || x == 0)	x = line;
    		line = 0;
    		y++;
    		continue;
    	}
    	line++;
    }
    file.close();

    return new Point(x, y);
}

Map* Map::load(const string path)
{
	Map* loadMap = new Map(getPointFromFile(path));
	ifstream file(path);
	cout << loadMap->getPosition()->toString() << endl;
	if(file)
    {
    	char c;
    	int i = 0;
    	int j = 0;
    	while(file.get(c))
    	{
    		cout << j << endl;
    		if(c == '\n' || i >= loadMap->getX())
    		{
    			i = 0;
    			j++;
    			continue;
    		}

    		if(j >= loadMap->getY()) break;

    		loadMap->setInt(i, j, c-'0');
    		i++;
    	}
    }
    else
    {
        throw string("An error occured during the file opening");
    }
	file.close();

	return loadMap;
}

int** Map::getMap()
{
	return this->table;
}

int Map::getX()
{
	return this->position->getX();
}

int Map::getY()
{
	return this->position->getY();
}

void Map::setInt(int i, int j, int newInt)
{
	if(i < 0 || i >= this->getX())
		throw string("i is out of border");
	if(j < 0 || j >= this->getY())
		throw string("j is out of border");

	this->table[i][j] = newInt;
}

void Map::changeInt(int before, int after)
{
	for(int i = 0; i < this->getX(); i++)
	{
		for(int j = 0; j < this->getY(); j++)
		{
			if(this->table[i][j] == before)
				this->table[i][j] = after;
		}
	}
}

void Map::displayRaw()
{
	for(int j = 0; j < this->getY(); j++)
	{
		for(int i = 0; i < this->getX(); i++)
		{
			cout << this->table[i][j];
		}
		cout << endl;
	}

	cout << endl << endl;
}

void Map::display(sf::RenderWindow* window)
{
	for(int i = 0; i < this->getX(); i++)
	{
		for(int j = 0; j < this->getY(); j++)
		{
			if(this->isWall(i, j))
			{
				tile[1].setPosition(i*TEXTURE_SIZE, j*TEXTURE_SIZE);
				window->draw(tile[1]);
			} else {
				tile[0].setPosition(i*TEXTURE_SIZE, j*TEXTURE_SIZE);
				window->draw(tile[0]);
			}
		}
	}
}