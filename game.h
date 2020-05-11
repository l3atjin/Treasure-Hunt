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
	bool showPath;
};

class game
{
private:
	vector<char> order;
	map huntMap;
	deque<Point> search_box;
	deque<Point> sail_box;
	vector<char> path = { '@' };
	Point sailPos;
	Point searchPos;
	Point treasurePos;
	Point startPos;
	int islandCount = 0;
	int waterCount = 0;
	int landCount = 0;
	bool isCStack;
	bool isFStack;
	bool isVerbose;
	bool isStats;
	bool isPath;

public:

	bool isCaptain = true;
	bool treasureFound = false;
	// game constructor
	game(options mode_in, map map_in);


	void sail();

	void search();

	void sailInvestigate();

	void searchInvestigate();

	void conTest();

	void printStats();
};

