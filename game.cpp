// Project ID: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD

#include "game.h"

using namespace std;

// game constructor
game::game(options& mode_in, map& map_in)
	: order(mode_in.order), huntMap(map_in),
	treasurePos(map_in.treasurePos), 
	startPos(map_in.startPos), isCStack(mode_in.isCStack), 
	isFStack(!mode_in.isFQueue), isVerbose(mode_in.verbose),
	isStats(mode_in.stats), showMap(mode_in.showMap), showList(mode_in.showList)
{
	treasurePos.track = '$';
	sailPos = startPos;
	sailPos.track = '@';
	huntMap.at(sailPos.row, sailPos.col).track = '@';
}

// returns true if the teasure is found

void game::printStats()
{
	cout << "--- STATS ---" << "\n";
	cout << "Starting location: " << startPos.row << "," << startPos.col << "\n";
	cout << "Water locations investigated: " << waterCount << "\n";
	cout << "Land locations investigated: " << landCount << "\n";
	cout << "Went ashore: " << islandCount << "\n";
	if (!deadend)
	{
		path_helper();
		cout << "Path length: " << path.size() - 1 << "\n";
		cout << "Treasure location: " << treasurePos.row << "," << treasurePos.col << "\n";
	}
	cout << "--- STATS ---" << "\n";
}

void game::path_helper()
{
	Point currentPos = huntMap.at(treasurePos.row, treasurePos.col);
	int count = 0;
	path.push_back(currentPos);
	while (currentPos.type != '@')
	{
		//cout << path.at(count).type << "\n";
		if (currentPos.track == 'n')
		{
			if (count > 0 && (path.at(count - 1).track == 'w' || path.at(count - 1).track == 'e'))
			{
				huntMap.at(currentPos.row, currentPos.col).type = '+';
			}
			else
			{
				huntMap.at(currentPos.row, currentPos.col).type = '|';
			}
			currentPos = huntMap.at(currentPos.row + 1, currentPos.col);
		}
		else if (currentPos.track == 'e')
		{
			if (count > 0 && (path.at(count - 1).track == 'n' || path.at(count - 1).track == 's'))
			{
				huntMap.at(currentPos.row, currentPos.col).type = '+';
			}
			else
			{
				huntMap.at(currentPos.row, currentPos.col).type = '-';;
			}
			currentPos = huntMap.at(currentPos.row, currentPos.col - 1);
		}
		else if (currentPos.track == 's')
		{
			if (count > 0 && (path.at(count - 1).track == 'w' || path.at(count - 1).track == 'e'))
			{
				huntMap.at(currentPos.row, currentPos.col).type = '+';
			}
			else
			{
				huntMap.at(currentPos.row, currentPos.col).type = '|';
			}
			currentPos = huntMap.at(currentPos.row - 1, currentPos.col);
		}
		else if (currentPos.track == 'w')
		{
			if (count > 0 && (path.at(count - 1).track == 'n' || path.at(count - 1).track == 's'))
			{
				huntMap.at(currentPos.row, currentPos.col).type = '+';
			}
			else
			{
				huntMap.at(currentPos.row, currentPos.col).type = '-';
			}
			currentPos = huntMap.at(currentPos.row, currentPos.col + 1);
		}
		path.push_back(currentPos);
		count++;
	}
}

void game::print_path()
{
	if (!isStats)
	{
		path_helper();	
	}
	//cout << path.size() << "\n";
	if (showMap)
	{	
		huntMap.at(treasurePos.row, treasurePos.col).type = 'X';
		for (int i = 0; i < huntMap.size; i++)
		{
			for (int j = 0; j < huntMap.size; j++)
			{
				cout << huntMap.grid[i][j].type;
			}
			cout << "\n";
		}
	}
	if (showList)
	{
		cout << "Sail:" << "\n";
		for (size_t i = path.size() - 1; i > 0; i--)
		{
			if (path[i].type == '.' || path[i].type == '@')
			{
				cout << path[i].row << "," << path[i].col << "\n";
			}
		}
		// might wanna check
		cout << "Search:" << "\n";
		for (size_t i = path.size() - 1; i > 0; i--)
		{
			if (path[i].type == 'o' || path[i].type == '$')
			{
				cout << path[i].row << "," << path[i].col << "\n";
			}
		}
		cout << path[0].row << "," << path[0].col << "\n";
	}
}


void game::print_map()
{
	cout << "Printing map:" << "\n";
	for (int i = 0; i < huntMap.size; i++)
	{
		for (int j = 0; j < huntMap.size; j++)
		{
			cout << huntMap.grid[i][j].track << " ";
		}
		cout << "\n";
	}
}

void game::sail()
{
	while (isCaptain && !treasureFound) {
		sailInvestigate();
		if (!isCaptain)
		{
			return;
		}
		if (sail_box.empty())
		{
			if (isVerbose)
			{
				cout << "Treasure hunt failed" << "\n";
			}
			deadend = true;
			return;
		}
		if (isCStack)
		{
			waterCount++;
			sailPos = sail_box.back();
			sail_box.pop_back();
		}
		else
		{
			waterCount++;
			sailPos = sail_box.front();
			sail_box.pop_front();
		}
		//cout << "	Sail position: " << sailPos.row << "," << sailPos.col << "\n";
		//cout << "	Water tiles discovered: " << waterCount << "\n";
		
	} // while loop
}


void game::search()
{
	// declare deque here
	while (!isCaptain && !treasureFound)
	{
		if (treasureFound || (searchPos.row == treasurePos.row && searchPos.col == treasurePos.col))
		{
			if (isVerbose)
			{
				cout << "Searching island... party found treasure at " << treasurePos.row << "," << treasurePos.col << "." << "\n";
			}
			treasureFound = true;
			return;
		}
		searchInvestigate();
		if (search_box.empty())
		{
			isCaptain = true;
			if (isVerbose)
			{
				cout << "Searching island... party returned with no treasure." << "\n";
			}
			return;
		}
		if (isFStack)
		{
			landCount++;
			searchPos = search_box.back();
			search_box.pop_back();
		}
		else
		{
			landCount++;
			searchPos = search_box.front();
			search_box.pop_front();
		}
		if (treasureFound || (searchPos.row == treasurePos.row && searchPos.col == treasurePos.col))
		{
			if (isVerbose)
			{
				cout << "Searching island... party found treasure at " << treasurePos.row << "," << treasurePos.col << "." << "\n";
			}
			treasureFound = true;
			return;
		}
		
		//cout << "	Search position: " << searchPos.row << "," << searchPos.col << "\n";
		//cout << "	Land tiles discovered: " << landCount << "\n";
	}
}

void game::searchInvestigate()
{
	for (int i = 0; i < 4; i++)
	{
		if (order[i] == 'n' && searchPos.row != 0 && huntMap.checkSail(isCaptain, huntMap.at(searchPos.row - 1, searchPos.col)))
		{
			if (huntMap.at(searchPos.row - 1, searchPos.col).type == '$')
			{
				treasureFound = true;
				search_box.push_back(huntMap.at(searchPos.row - 1, searchPos.col));
				huntMap.at(searchPos.row - 1, searchPos.col).track = 'n';
				return;
			}
			search_box.push_back(huntMap.at(searchPos.row - 1, searchPos.col));
			huntMap.at(searchPos.row - 1, searchPos.col).track = 'n';
		}
		else if (order[i] == 'e' && searchPos.col != huntMap.size - 1 && huntMap.checkSail(isCaptain, huntMap.at(searchPos.row, searchPos.col + 1)))
		{
			if (huntMap.at(searchPos.row, searchPos.col + 1).type == '$')
			{
				treasureFound = true;
				search_box.push_back(huntMap.at(searchPos.row, searchPos.col + 1));
				huntMap.at(searchPos.row, searchPos.col + 1).track = 'e';
				return;
			}
			search_box.push_back(huntMap.at(searchPos.row, searchPos.col + 1));
			huntMap.at(searchPos.row, searchPos.col + 1).track = 'e';
		}
		else if (order[i] == 's' && searchPos.row != huntMap.size - 1 && huntMap.checkSail(isCaptain, huntMap.at(searchPos.row + 1, searchPos.col)))
		{
			if (huntMap.at(searchPos.row + 1, searchPos.col).type == '$')
			{
				treasureFound = true;
				search_box.push_back(huntMap.at(searchPos.row + 1, searchPos.col));
				huntMap.at(searchPos.row + 1, searchPos.col).track = 's';
				return;
			}
			search_box.push_back(huntMap.at(searchPos.row + 1, searchPos.col));
			huntMap.at(searchPos.row + 1, searchPos.col).track = 's';
			
		}
		else if (order[i] == 'w' && searchPos.col != 0 && huntMap.checkSail(isCaptain, huntMap.at(searchPos.row, searchPos.col - 1)))
		{
			if (huntMap.at(searchPos.row, searchPos.col - 1).type == '$')
			{
				treasureFound = true;
				search_box.push_back(huntMap.at(searchPos.row, searchPos.col - 1));
				huntMap.at(searchPos.row, searchPos.col - 1).track = 'w';
				return;
			}
			search_box.push_back(huntMap.at(searchPos.row, searchPos.col - 1));
			huntMap.at(searchPos.row, searchPos.col - 1).track = 'w';
			
		} // end of if statements
	} // for loop
}

void game::sailInvestigate()
{
	bool landFound = false;
	for (int i = 0; i < 4; i++)
	{
		if (order[i] == 'n' && sailPos.row != 0 && huntMap.checkSail(isCaptain, huntMap.at(sailPos.row - 1, sailPos.col)))
		{
			if ((huntMap.at(sailPos.row - 1, sailPos.col).type == 'o' && !landFound) || (huntMap.at(sailPos.row - 1, sailPos.col).type == '$' && !landFound))
			{
				search_box.push_back(huntMap.at(sailPos.row - 1, sailPos.col));
				searchPos = huntMap.at(sailPos.row - 1, sailPos.col);
				huntMap.at(sailPos.row - 1, sailPos.col).track = 'n';
				landFound = true;
			}
			else if(huntMap.at(sailPos.row - 1, sailPos.col).type == '.')
			{
				sail_box.push_back(huntMap.at(sailPos.row - 1, sailPos.col));
				huntMap.at(sailPos.row - 1, sailPos.col).track = 'n';
			}
		}
		if (order[i] == 'e' && sailPos.col != huntMap.size - 1 && huntMap.checkSail(isCaptain, huntMap.at(sailPos.row, sailPos.col + 1)))
		{
			if ((huntMap.at(sailPos.row, sailPos.col + 1).type == 'o' && !landFound) || (huntMap.at(sailPos.row, sailPos.col + 1).type == '$' && !landFound))
			{
				search_box.push_back(huntMap.at(sailPos.row, sailPos.col + 1));
				searchPos = huntMap.at(sailPos.row, sailPos.col + 1);
				huntMap.at(sailPos.row, sailPos.col + 1).track = 'e';
				landFound = true;
			}
			else if(huntMap.at(sailPos.row, sailPos.col + 1).type == '.')
			{
				sail_box.push_back(huntMap.at(sailPos.row, sailPos.col + 1));
				huntMap.at(sailPos.row, sailPos.col + 1).track = 'e';
			}
		}
		if (order[i] == 's' && sailPos.row != huntMap.size - 1 && huntMap.checkSail(isCaptain, huntMap.at(sailPos.row + 1, sailPos.col)))
		{
			if ((huntMap.at(sailPos.row + 1, sailPos.col).type == 'o' && !landFound) || (huntMap.at(sailPos.row + 1, sailPos.col).type == '$' && !landFound))
			{
				search_box.push_back(huntMap.at(sailPos.row + 1, sailPos.col));
				searchPos = huntMap.at(sailPos.row + 1, sailPos.col);
				huntMap.at(sailPos.row + 1, sailPos.col).track = 's';
				landFound = true;
			}
			else if(huntMap.at(sailPos.row + 1, sailPos.col).type == '.')
			{
				sail_box.push_back(huntMap.at(sailPos.row + 1, sailPos.col));
				huntMap.at(sailPos.row + 1, sailPos.col).track = 's';
			}
		}
		if (order[i] == 'w' && sailPos.col != 0 && huntMap.checkSail(isCaptain, huntMap.at(sailPos.row, sailPos.col - 1)))
		{
			if ((huntMap.at(sailPos.row, sailPos.col - 1).type == 'o' && !landFound) || (huntMap.at(sailPos.row, sailPos.col - 1).type == '$' && !landFound))
			{
				search_box.push_back(huntMap.at(sailPos.row, sailPos.col - 1));
				searchPos = huntMap.at(sailPos.row, sailPos.col - 1);
				huntMap.at(sailPos.row, sailPos.col - 1).track = 'w';
				landFound = true;
			}
			else if(huntMap.at(sailPos.row, sailPos.col - 1).type == '.')
			{
				sail_box.push_back(huntMap.at(sailPos.row, sailPos.col - 1));
				huntMap.at(sailPos.row, sailPos.col - 1).track = 'w';
			}
			
		} // end of if statements
	} // for loop
	if (landFound)
	{
		islandCount++;
		isCaptain = false;
		if (isVerbose)
		{
			cout << "Went ashore at: " << search_box.back().row << "," << search_box.back().col << "\n";
		}
		if (isFStack)
		{
			landCount++;
			searchPos = search_box.back();
			search_box.pop_back();
		}
		else
		{
			landCount++;
			searchPos = search_box.front();
			search_box.pop_front();
		}
	}
}


