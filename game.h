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

class game
{
private:
	vector<char> order;
	map treasureMap;
	deque<Point> search_box;
	deque<Point> sail_box;
	Point currentPos;
	Point sailPos;
	Point searchPos;
	Point treasurePos;
	bool isCStack = true;
	bool isFStack = false;

public:
	game(map map_in);

	game(map map_in, vector<char> order_in);

	// return true if the treasure is found
	bool treasureFound();

	void sailInvestigate();

	void searchInvestigate();

	void sailDiscover();

	void searchDiscover();


};

