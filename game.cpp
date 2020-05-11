// Project ID: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD

#include "game.h"

using namespace std;

// game constructor
game::game(options mode_in, map& map_in)
	: order(mode_in.order), huntMap(map_in),
	treasurePos(map_in.treasurePos), 
	startPos(map_in.startPos), isCStack(mode_in.isCStack), 
	isFStack(!mode_in.isFQueue), isVerbose(mode_in.verbose),
	isStats(mode_in.stats), isPath(mode_in.showPath)
{
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
	cout << "Path length: " << "\n";
	cout << "Treasure location: " << treasurePos.row << "," << treasurePos.col << "\n";
	cout << "--- STATS ---" << "\n";
}

void game::conTest()
{
	
}

void game::print_map()
{
	cout << "Printing map:" << "\n";
	for (int i = 0; i < huntMap.size; i++)
	{
		for (int j = 0; j < huntMap.size; j++)
		{
			cout << huntMap.grid[i][j].row << huntMap.grid[i][j].col << huntMap.grid[i][j].track << " ";
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
			cout << "Treasure hund failed" << "\n";
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
		cout << "	Sail position: " << sailPos.row << "," << sailPos.col << "\n";
		cout << "	Water tiles discovered: " << waterCount << "\n";
		
	} // while loop
}

void game::search()
{
	int count = 0;
	while (!isCaptain && !treasureFound)
	{
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
			num++;
		}
		else
		{
			landCount++;
			searchPos = search_box.front();
			search_box.pop_front();
		}
		if (treasureFound)
		{
			if (count == 0)
			{
				landCount++;
			}
			cout << "	Total land tiles discovered: " << landCount << "\n";
			if (isVerbose)
			{
				cout << "Searching island... party found treasure at " << treasurePos.row << "," << treasurePos.col << "." << "\n";
			}
			treasureFound = true;
			return;
		}
		
		cout << "	Search position: " << searchPos.row << "," << searchPos.col << "\n";
		cout << "	Land tiles discovered: " << landCount << "\n";
		count++;
	}
}

void game::searchInvestigate()
{
	for (int i = 0; i < 4; i++)
	{
		if (order[i] == 'N' && searchPos.row != 0 && huntMap.checkSail(isCaptain, huntMap.at(searchPos.row - 1, searchPos.col)))
		{
			if (huntMap.at(searchPos.row - 1, searchPos.col).type == '$')
			{
				treasureFound = true;
				search_box.push_back(huntMap.at(searchPos.row - 1, searchPos.col));
				return;
			}
			search_box.push_back(huntMap.at(searchPos.row - 1, searchPos.col));
			huntMap.grid[searchPos.row - 1][searchPos.col].track = 'N';
		}
		else if (order[i] == 'E' && searchPos.col != huntMap.size - 1 && huntMap.checkSail(isCaptain, huntMap.at(searchPos.row, searchPos.col + 1)))
		{
			if (huntMap.at(searchPos.row, searchPos.col + 1).type == '$')
			{
				treasureFound = true;
				search_box.push_back(huntMap.at(searchPos.row, searchPos.col + 1));
				return;
			}
			search_box.push_back(huntMap.at(searchPos.row, searchPos.col + 1));
			huntMap.at(searchPos.row, searchPos.col + 1).track = 'E';
		}
		else if (order[i] == 'S' && searchPos.row != huntMap.size - 1 && huntMap.checkSail(isCaptain, huntMap.at(searchPos.row + 1, searchPos.col)))
		{
			if (huntMap.at(searchPos.row + 1, searchPos.col).type == '$')
			{
				treasureFound = true;
				search_box.push_back(huntMap.at(searchPos.row + 1, searchPos.col));
				return;
			}
			search_box.push_back(huntMap.at(searchPos.row + 1, searchPos.col));
			huntMap.at(searchPos.row + 1, searchPos.col).track = 'S';
			
		}
		else if (order[i] == 'W' && searchPos.col != 0 && huntMap.checkSail(isCaptain, huntMap.at(searchPos.row, searchPos.col - 1)))
		{
			if (huntMap.at(searchPos.row, searchPos.col - 1).type == '$')
			{
				treasureFound = true;
				search_box.push_back(huntMap.at(searchPos.row, searchPos.col - 1));
				return;
			}
			search_box.push_back(huntMap.at(searchPos.row, searchPos.col - 1));
			huntMap.at(searchPos.row, searchPos.col - 1).track = 'W';
			
		} // end of if statements
	} // for loop
}

void game::sailInvestigate()
{
	bool landFound = false;
	for (int i = 0; i < 4; i++)
	{
		if (order[i] == 'N' && sailPos.row != 0 && huntMap.checkSail(isCaptain, huntMap.at(sailPos.row - 1, sailPos.col)))
		{
			if ((huntMap.at(sailPos.row - 1, sailPos.col).type == 'o' && !landFound) || (huntMap.at(sailPos.row - 1, sailPos.col).type == '$' && !landFound))
			{
				search_box.push_back(huntMap.at(sailPos.row - 1, sailPos.col));
				searchPos = huntMap.at(sailPos.row - 1, sailPos.col);
				huntMap.at(sailPos.row - 1, sailPos.col).track = 'N';
				landFound = true;
			}
			else
			{
				sail_box.push_back(huntMap.at(sailPos.row - 1, sailPos.col));
				huntMap.at(sailPos.row - 1, sailPos.col).track = 'N';
			}
		}
		if (order[i] == 'E' && sailPos.col != huntMap.size - 1 && huntMap.checkSail(isCaptain, huntMap.at(sailPos.row, sailPos.col + 1)))
		{
			if ((huntMap.at(sailPos.row, sailPos.col + 1).type == 'o' && !landFound) || (huntMap.at(sailPos.row, sailPos.col + 1).type == '$' && !landFound))
			{
				search_box.push_back(huntMap.at(sailPos.row, sailPos.col + 1));
				searchPos = huntMap.at(sailPos.row, sailPos.col + 1);
				huntMap.at(sailPos.row, sailPos.col + 1).track = 'E';
				landFound = true;
			}
			else
			{
				sail_box.push_back(huntMap.at(sailPos.row, sailPos.col + 1));
				huntMap.at(sailPos.row, sailPos.col + 1).track = 'E';
			}
		}
		if (order[i] == 'S' && sailPos.row != huntMap.size - 1 && huntMap.checkSail(isCaptain, huntMap.at(sailPos.row + 1, sailPos.col)))
		{
			if ((huntMap.at(sailPos.row + 1, sailPos.col).type == 'o' && !landFound) || (huntMap.at(sailPos.row + 1, sailPos.col).type == '$' && !landFound))
			{
				search_box.push_back(huntMap.at(sailPos.row + 1, sailPos.col));
				searchPos = huntMap.at(sailPos.row + 1, sailPos.col);
				huntMap.at(sailPos.row + 1, sailPos.col).track = 'S';
				landFound = true;
			}
			else
			{
				sail_box.push_back(huntMap.at(sailPos.row + 1, sailPos.col));
				huntMap.at(sailPos.row + 1, sailPos.col).track = 'S';
			}
		}
		if (order[i] == 'W' && sailPos.col != 0 && huntMap.checkSail(isCaptain, huntMap.at(sailPos.row, sailPos.col - 1)))
		{
			if ((huntMap.at(sailPos.row, sailPos.col - 1).type == 'o' && !landFound) || (huntMap.at(sailPos.row, sailPos.col - 1).type == '$' && !landFound))
			{
				search_box.push_back(huntMap.at(sailPos.row, sailPos.col - 1));
				searchPos = huntMap.at(sailPos.row, sailPos.col - 1);
				huntMap.at(sailPos.row, sailPos.col - 1).track = 'W';
				landFound = true;
			}
			else 
			{
				sail_box.push_back(huntMap.at(sailPos.row, sailPos.col - 1));
				huntMap.at(sailPos.row, sailPos.col - 1).track = 'W';
			}
			
		} // end of if statements
	} // for loop
	if (landFound)
	{
		if (isVerbose)
		{
			islandCount++;
			cout << "Went ashore at: " << search_box.back().row << "," << search_box.back().col << "\n";
		}
		isCaptain = false;
	}
}


