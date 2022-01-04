#include <cstdlib>
#include <cstdio>
#include <list>
#include <iostream>
#include <cstring>
#include "Node.hpp"
#include "Point.hpp"

using namespace std;

int main()
{
	int** table = new int*[10];

	for(int i = 0; i < 10; i++)
	{
		table[i] = new int[10];
	}

	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			if(i == 0 || j == 0 || i == 9 || j == 9)
			{
				table[i][j] = 1;
			} else {
				table[i][j] = 0;
			}
		}
	}

	for(int i = 0; i < 10; i++)
	{
		table[2][i] = 1;
		table[3][i] = 1;
		table[4][i] = 1;
		table[5][i] = 1;
		table[6][i] = 1;
	}
	table[2][1] = 0;
	table[2][4] = 0;

	table[3][1] = 0;
	table[3][3] = 0;
	table[3][4] = 0;
	table[3][5] = 0;
	table[3][6] = 0;
	table[3][7] = 0;

	table[4][1] = 0;
	table[4][4] = 0;

	table[5][1] = 0;
	table[5][3] = 0;
	table[5][4] = 0;
	table[5][5] = 0;
	table[5][6] = 0;

	table[6][1] = 0;

	
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			cout << table[i][j] << " ";
		}
		cout << endl;
	}


	list<Point> l = AStar::way(table, 10, 10, Point(5,6), Point(7,4));

	cout << endl;

    for(Point p : l)
    {
        table[p.getX()][p.getY()] = 2;
    }

    for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			cout << table[i][j] << " ";
		}
		cout << endl;
	}

	int** table1 = new int*[10];

	for(int i = 0; i < 10; i++)
	{
		table[i] = new int[15];
	}

	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 15; j++)
		{
			if(i == 0 || j == 0 || i == 9 || j == 9)
			{
				table[i][j] = 1;
			} else {
				table[i][j] = 0;
			}
		}
	}

	cout << 'r' << endl;
	list<Point> k = AStar::way(table1, 15, 10, Point(1,1), Point(11,11));
	cout << 'r' << endl;


	return 1;
}



