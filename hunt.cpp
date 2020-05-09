// Project ID: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD


#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <getopt.h>
#include "map.h"

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

options getMode(int argc, char * argv[]) {
	//bool modeSpecified = false;
	options gameOptions;
	gameOptions.order = { 'N','E','S','W' };
	gameOptions.isCStack = true;
	gameOptions.isFQueue = true;
	gameOptions.verbose = false;
	gameOptions.stats = false;
	gameOptions.showPath = false;

	// These are used with getopt_long()
	opterr = true; // Give us help with errors
	int choice;
	int option_index = 0;
	option long_options[] = {
		{ "help", no_argument, nullptr, 'h' },
		{ "captain", required_argument, nullptr, 'c' },
		{ "first-mate", required_argument, nullptr, 'f' },
		{ "hunt-order", no_argument, nullptr, 'o' },
		{ "verbose", no_argument, nullptr, 'v' },
		{ "stats", no_argument, nullptr, 's' },
		{ "show-path", required_argument, nullptr, 'p' },
		{ nullptr, 0,                 nullptr, '\0' }
	};

	while ((choice = getopt_long(argc, argv, "hc:f:o:vsp:", long_options, &option_index)) != -1) {
		string str = optarg;
		switch (choice) {
		case 'h':
			exit(0);
			break;
		case 'c':
			if (str == "queue")
			{
				gameOptions.isCStack = false;
			}
			break;
		case 'f':
			if (str == "stack")
			{
				gameOptions.isFQueue = false;
			}
			break;
		case 'o':
			gameOptions.order = {optarg[0], optarg[1], optarg[2], optarg[3]};
			break;
		case 'v':
			exit(1);
			break;
		case 's':
			exit(1);
			break;
		case 'p':
			exit(1);
			break;
		default:
			cerr << "Error: invalid option" << endl;
			exit(1);
		} // switch
	} // while

	return gameOptions;
} // getMode()


int main()
{
	std::ios_base::sync_with_stdio(false);

	

	map map;
	map.read_in();
	//map.print_map();

}