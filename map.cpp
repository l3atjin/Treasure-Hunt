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


map::map() {}

void map::read_in()
{
	string temp;
	while (getline(cin, temp)) {
		if (temp[0] == '#')
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

Point& map::at(int row, int col)
{
	return grid[row][col];
}

void map::map_helper()
{
	grid.reserve(size + 1);
	string temp;
	int count = 0;
	while (getline(cin, temp))
	{
		vector <Point> col;
		col.reserve(size + 1);
		for (unsigned int i = 0; i < temp.size(); i++)
		{
			Point in;
			in.type = temp[i];
			in.track = 'M';
			if (temp[i] == '@')
			{
				startPos.row = count;
				startPos.col = i;
			}
			else if (temp[i] == '$')
			{
				treasurePos.row = count;
				treasurePos.col = i;
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
	junk.type = 'J';
	vector<Point> junkVec(size, junk);
	junkVec.reserve(size + 1);
	vector<vector <Point>> temp(size, junkVec);
	temp.reserve(size + 1);
	grid = temp;
	Point in;
	int rowTemp, colTemp;
	while (cin >> rowTemp >> colTemp >> in.type)
	{
		if (in.type == '@')
		{
			startPos.row = rowTemp;
			startPos.col = colTemp;
		}
		else if (in.type == '$')
		{
			treasurePos.row = rowTemp;
			treasurePos.col = colTemp;
		}
		grid[rowTemp][colTemp] = in;
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (grid[i][j].type == 'J')
			{
				grid[i][j].type = '.';
			}
		}
	}
}






/*void map::print_map()
{
	cout << "Printing map:" << "\n";
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << grid[i][j].row << grid[i][j].col << grid[i][j].type << " ";
		}
		cout << "\n";
	}
}*/




