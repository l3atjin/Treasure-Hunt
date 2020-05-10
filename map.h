// Project ID: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD

#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class Point
{
public:
	int row, col;
	char type;
	bool isDiscovered = false;
	bool isInvestigated = false;

	Point& operator=(const Point &rhs) {
		row = rhs.row;
		col = rhs.col;
		isDiscovered = rhs.isDiscovered;
		isInvestigated = rhs.isInvestigated;
		return *this;
	}
};

class map
{
private:
	vector<vector <Point>> grid;
	char mapType;
	

public:
	Point startPos;
	Point treasurePos;
	int size;

	//constructor
	map();

	//read map into grid
	void read_in();

	//helper for Map type
	void map_helper();

	//helper for List type
	void list_helper();

	//for testing only: print the grid on cout
	void print_map();

	Point* at(int row, int col);

	bool checkSail(bool isCaptain, Point* pos);

};

