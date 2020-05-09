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
	int row, col;
	char type;
	bool isDiscovered = false;
};

class map
{
private:
	vector<vector <Point>> grid;
	char mapType;
	int size;
	

public:
	map();

	void read_in();

	void map_helper();

	void list_helper();

	void print_map();

};

