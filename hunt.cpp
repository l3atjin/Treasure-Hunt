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
//#include "map.h"
#include "game.h"

using namespace std; 


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
		{ "hunt-order", required_argument, nullptr, 'o' },
		{ "verbose", no_argument, nullptr, 'v' },
		{ "stats", no_argument, nullptr, 's' },
		{ "show-path", required_argument, nullptr, 'p' },
		{ nullptr, 0,                 nullptr, '\0' }
	};

	while ((choice = getopt_long(argc, argv, "hc:f:o:vsp:", long_options, &option_index)) != -1) {
		switch (choice) {
		case 'h':
			exit(0);
			break;
		case 'c':
			if (optarg[0] == 'q')
			{
				gameOptions.isCStack = false;
			}
			break;
		case 'f':
			if (optarg[0] == 's')
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


int main(int argc, char* argv[])
{
	std::ios_base::sync_with_stdio(false);

	// store options in a struct and initiliaze classes with given options
	options mode = getMode(argc, argv);
	map map;
	map.read_in();
	game hunt(mode, map);

	// The main while loop
	while (!hunt.treasureFound)
	{
		hunt.sail();
		if (!hunt.isCaptain)
		{
			hunt.search();
		}
	}

	
	// map.print_map();
	return 0;
}