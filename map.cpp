// Project ID: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD

#include "map.h"
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;


map::map(){}

void map::read_in()
{
	string temp;
	while (getline(cin, temp)) {
		if (temp[0] == '#' && temp[1] == ' ')
		{
			continue;
		}
		if (temp[0] == 'M')
		{
			mapType = 'M';
			continue;
		}
		else if (temp[0] == 'L')
		{
			mapType = 'L';
			continue;
		}
		size = stoi(temp);
		break;
	}
	if (mapType == 'M')
	{
		map_helper();
	}
	else
	{
		list_helper();
	}
}

Point map::at(int row, int col)
{
	return grid[row][col];
}

void map::map_helper()
{
	string temp;
	while (getline(cin, temp))
	{
		int count = 0;
		vector <Point> col;
		for (unsigned int i = 0; i < temp.size(); i++)
		{
			Point in;
			in.row = count;
			in.col = i;
			in.type = temp[i];
			if (temp[i] == '@')
			{
				startPos = in;
			}
			else if (temp[i] == '$')
			{
				treasurePos = in;
			}
			col.push_back(in);
		}
		grid.push_back(col);
		count++;
	}
}

void map::list_helper()
{
	Point junk;
	junk.col = -1;
	junk.row = -1;
	junk.type = 'J';
	vector<Point> junkVec(size, junk);
	vector<vector <Point>> temp(size, junkVec);
	grid = temp;
	Point in;
	while (cin >> in.row >> in.col >> in.type)
	{
		if (in.type == '@')
		{
			startPos = in;
		}
		else if (in.type == '$')
		{
			treasurePos = in;
		}
		grid[in.row][in.col] = in;
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (grid[i][j].type == 'J')
			{
				grid[i][j].row = i;
				grid[i][j].col = j;
				grid[i][j].type = '.';
			}
		}
	}
}

bool map::checkSail(bool isCaptain, Point pos)
{
	if (!pos.isDiscovered && !pos.isInvestigated)
	{
		return false;
	}
	else if (pos.type != '#')
	{
		return false;
	}
	else if (!isCaptain && pos.type != 'o')
	{
		return false;
	}
	return true;
}




void map::print_map()
{
	cout << "Printing map:" << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << grid[i][j].type << " ";
		}
		cout << endl;
	}
}




