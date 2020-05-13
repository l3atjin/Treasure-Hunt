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

struct Point
{
	char type;
	char track = 'M';
};

struct Position
{
	int row, col;
};

class map
{
private:
	char mapType;


public:
	vector<vector <Point>> grid;
	Position startPos;
	Position treasurePos;
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
	//void print_map();

	Point& at(int row, int col);

	bool checkSail(bool isCaptain, Point pos);

};

