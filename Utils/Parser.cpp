#include "Parser.hpp"

Player* Parser::loadPlayer(const string nameFile, Point* position)
{
    int level;
    int exp;
    int pointLevel;
    int pointDef;
    int pointAtk;
    int pointLife;

    string line;

    ifstream file("data/" + nameFile);

    if(file.fail()) return NULL;

    getline(file, line);
    getline(file, line);

    level = searchInt(line);

    getline(file, line);

    exp = searchInt(line);

    getline(file, line);

    pointLevel = searchInt(line);

    getline(file, line);

    pointDef = searchInt(line);

    getline(file, line);

    pointAtk = searchInt(line);

    getline(file, line);

    pointLife = searchInt(line);

    file.close();

    Player* playerFromFile = new Player(nameFile, position, 0, 0, 96, 128);
    playerFromFile->setExperience(exp);
    playerFromFile->setLevel(level);
    playerFromFile->setPointLevel(pointLevel);
    playerFromFile->setPointDefense(pointDef);
    playerFromFile->setPointAttack(pointAtk);
    playerFromFile->setPointLife(pointLife);

    playerFromFile->updateStat();


    return playerFromFile;
}

void Parser::savePlayer(Player* p)
{
    if(mkdir("data", 0777));
    ofstream file("data/" + p->getUuid());
 
    if(file)
    {
        file << "{" << endl;
        file << "level : " << p->getLevel() << endl;
        file << "experience : " << p->getExperience() << endl;
        file << "pointLevel : " << p->getPointLevel() << endl;
<<<<<<< HEAD
        file << "pointDef : " << p->getPointDefense() << endl;
        file << "pointAtk : " << p->getPointAttack() << endl;
=======
        file << "pointDefense : " << p->getPointDefense() << endl;
        file << "pointAttack : " << p->getPointAttack() << endl;
>>>>>>> 7e4874d20db622347b6835912c3b633d6c47e90c
        file << "pointLife : " << p->getPointLife() << endl;
        file << "}" << endl;
    }
    file.close();
}

Map* Parser::loadMap(const string nameFile)
{
    Map* loadMap = new Map(getPointFromFile(nameFile));
    ifstream file(nameFile);

    if(file.fail()) return NULL;

    if(file)
    {
        char c;
        int i = 0;
        int j = 0;
        string line;

        while(getline(file, line))
        {
            while(i < loadMap->getX())
            {
                loadMap->setInt(i, j, line[i]-'0');
                i++;
            }

            i = 0;
            j++;
        }
    }
    else
    {
        throw string("An error occured during the file opening");
    }
    file.close();

    return loadMap;
}

void Parser::saveMap(Map* m, const string nameFile)
{
    if(mkdir("data", 0777));
    ofstream file("data/" + nameFile);
 
    if(file)
    {
        for(int j = 0; j < m->getY(); j++)
        {
            for(int i = 0; i < m->getX(); i++)
            {
                file << m->getMap()[i][j];
            }
            file << endl;
        }
    }
    file.close();
}

Point* Parser::getPointFromFile(const string path)
{
    ifstream file(path);
    int x = 0;
    int tmp;
    int y = 0;

    string line;
    while(getline(file, line))
    {
        tmp = line.size();

        if(x > tmp || x == 0)
        {
            x = tmp;
        }
        y++;
    }
    file.close();

    return new Point(x, y);
}

int Parser::searchInt(string chaine)
{
    int i = 0;
    int deb;
    int fin;
    bool find = false;
    string subString;

    while(i < chaine.size() && !find)
    {
        if(chaine[i] >= '0' && chaine[i] <= '9')
        {
            i++;
        } else {
            deb = i;
            i++;
            while(chaine[i] >= '0' && chaine[i] <= '9')
            {
                i++;
            }
            fin = --i;
            break;
        }
    }

    subString = chaine.substr(deb, fin);

    return atoi(subString.c_str());
}