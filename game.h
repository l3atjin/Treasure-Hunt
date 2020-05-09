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
	map map;
	stack<Point> search_box;
	queue<Point> sail_box;
	Point currentPos;
	Point treasurePos;

};

