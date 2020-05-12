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
	gameOptions.order = { 'S','W','E','N' };
	gameOptions.isCStack = true;
	gameOptions.isFQueue = false;
	gameOptions.verbose = false;
	gameOptions.stats = false;
	gameOptions.showMap = true;
	gameOptions.showList = true;
	string str;
	int count = 0;
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
			cout << "Allowed options: " << "\n";
			exit(1);
		case 'c':
			str = optarg;
			if (str != "queue" || str != "stack")
			{
				exit(1);
			}
			else if (optarg[0] == 'q')
			{
				gameOptions.isCStack = false;
			}
			break;
		case 'f':
			str = optarg;
			if (str != "queue" || str != "stack")
			{
				exit(1);
			}
			else if (optarg[0] == 's')
			{
				gameOptions.isFQueue = false;
			}
			break;
		case 'o':
			str = optarg;
			if (str.length() != 4)
			{
				exit(1);
			}
			/*else if(str.find('N') == string::npos || str.find('E') == string::npos || str.find('S') == string::npos || str.find('W') == -string::npos)
			{
				exit(1);
			}*/
			gameOptions.order = {optarg[0], optarg[1], optarg[2], optarg[3]};
			break;
		case 'v':
			gameOptions.verbose = true;
			break;
		case 's':
			gameOptions.stats = true;
			break;
		case 'p':
			if (count > 0)
			{
				exit(1);
			}
			str = optarg;
			if (str != "M" || str != "L")
			{
				exit(1);
			}
			if (str == "M")
			{
				gameOptions.showMap = true;
			}
			else
			{
				gameOptions.showList = true;
			}
			count++;
			break;
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
	cout << mode.order[0] << mode.order[1] << mode.order[2] << mode.order[3] << endl;
	game hunt(mode, map);


	if (mode.verbose)
	{
		cout << "Treasure hunt started at: " << map.startPos.row << "," << map.startPos.col << "\n";
	}
	
	// The main while loop
	while (!hunt.treasureFound)
	{
		
		hunt.sail();
		if (!hunt.isCaptain)
		{
			hunt.search();
		}
	}
	//hunt.conTest();
	if (mode.stats)
	{
		hunt.printStats();
	}
	if (mode.showMap || mode.showList)
	{
		hunt.print_path();
	}
	if (hunt.treasureFound)
	{
		cout << "Treasure found at " << map.treasurePos.row << "," << map.treasurePos.col << " with path length " << hunt.path.size() - 1 << "." << "\n";
	}
	else {
		cout << "No treasure found after investigating " << hunt.waterCount + hunt.landCount << " locations." << "\n";
	}

	//cout << "\n";

	hunt.print_map(); 
	//hunt.print_path();
	return 0;
}