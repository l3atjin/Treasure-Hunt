// Project ID: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD

#include <vector>
#include "map.h"
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

struct options
{
	vector<char> order;
	bool isCStack;
	bool isFQueue;
	bool verbose;
	bool stats;
	bool showMap;
	bool showList;
};



class game
{
private:
	vector<char> order;
	vector<vector <Point>> grid;
	deque<Position> search_box;
	deque<Position> sail_box;
	Position sailPos;
	Position searchPos;
	Position treasurePos;
	Position startPos;
	bool isCStack;
	bool isFStack;
	bool isVerbose;
	bool isStats;
	bool showMap;
	bool showList;
	int size;

public:
	vector<Point> path;
	vector<Position> pathPos;
	int islandCount = 0;
	int waterCount = 1;
	int landCount = 0;
	bool isCaptain = true;
	bool treasureFound = false;
	bool deadend = false;
	// game constructor
	game(options& mode_in, vector<vector <Point>>& grid_in, Position startPos_in, Position treasurePos_in, int size_in);

	void print_map();

	void sail();

	void search();

	void sailInvestigate();

	void searchInvestigate();

	void print_path();

	void printStats();

	void path_helper();

	bool checkSail(bool isCaptain, Point pos);
};

