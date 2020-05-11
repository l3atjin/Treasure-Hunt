// Project ID: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD

#include "game.h"

using namespace std;

// game constructor
game::game(options mode_in, map map_in)
	: order(mode_in.order), huntMap(map_in),
	treasurePos(map_in.treasurePos), 
	startPos(map_in.startPos), isCStack(mode_in.isCStack), 
	isFStack(!mode_in.isFQueue), isVerbose(mode_in.verbose),
	isStats(mode_in.stats), isPath(mode_in.showPath)
{
	sailPos = startPos;
	sailPos.isDiscovered = true;
	sail_box.push_back(startPos);
}

// returns true if the teasure is found

void game::printStats()
{
	cout << "--- STATS ---" << endl;
	cout << "Starting location: " << startPos.row << "," << startPos.col << endl;
	cout << "Water locations investigated: " << waterCount << endl;
	cout << "Land locations investigated: " << landCount << endl;
	cout << "Went ashore: " << islandCount << endl;
	cout << "Path length: " << endl;
	cout << "Treasure location: " << treasurePos.row << "," << treasurePos.col << endl;
	cout << "--- STATS ---" << endl;
}

void game::conTest()
{
	for (unsigned int i = 0; i < path.size(); i++)
	{
		cout << path[i] << " ";
	}
	cout << endl;
}

void game::sail()
{
	while (isCaptain && !treasureFound) {
		if (sail_box.empty())
		{
			cout << "Treasure hund failed" << endl;
			return;
		}
		if (sailPos.type == '@')
		{
			path.push_back('@');
		}
		if (isCStack)
		{
			waterCount++;
			sailPos = sail_box.back();
			sail_box.pop_back();
			sailPos.isDiscovered = true;
		}
		else
		{
			waterCount++;
			sailPos = sail_box.front();
			sail_box.pop_front();
			sailPos.isDiscovered = true;
		}
		cout << "Sail position: " << sailPos.row << "," << sailPos.col << endl;
		sailInvestigate();
		
		
	} // while loop
}

void game::search()
{
	while (!isCaptain && !treasureFound)
	{
		if (searchPos.type == '$')
		{
			landCount++;
			cout << "game won!!!" << endl;
			treasureFound = true;
			if (isVerbose)
			{
				cout << "Searching island... party found treasure at " << treasurePos.row << "," << treasurePos.col << endl;
			}
			return;
		}
		if (search_box.empty())
		{
			isCaptain = true;
			if (isVerbose)
			{
				cout << "Searching island... party returned with no treasure" << endl;
			}
			return;
		}
		if (isFStack)
		{
			landCount++;
			searchPos = search_box.back();
			search_box.pop_back();
			huntMap.at(searchPos.row, searchPos.col).isDiscovered = true;
			searchPos.isDiscovered = true;
		}
		else
		{
			landCount++;
			searchPos = search_box.front();
			search_box.pop_front();
			huntMap.at(searchPos.row, searchPos.col).isDiscovered = true;
			searchPos.isDiscovered = true;
		}
		cout << "Search position: " << searchPos.row << "," << searchPos.col << endl;
		searchInvestigate();
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
			huntMap.at(searchPos.row - 1, searchPos.col).isInvestigated = true;
			path.push_back('N');
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
			huntMap.at(searchPos.row, searchPos.col + 1).isInvestigated = true;
			path.push_back('E');
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
			huntMap.at(searchPos.row + 1, searchPos.col).isInvestigated = true;
			path.push_back('S');
			
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
			huntMap.at(searchPos.row, searchPos.col - 1).isInvestigated = true;
			path.push_back('W');
			
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
				landFound = true;
			}
			sail_box.push_back(huntMap.at(sailPos.row - 1, sailPos.col));
			huntMap.at(sailPos.row - 1, sailPos.col).isInvestigated = true;
			path.push_back('N');
		}
		if (order[i] == 'E' && sailPos.col != huntMap.size - 1 && huntMap.checkSail(isCaptain, huntMap.at(sailPos.row, sailPos.col + 1)))
		{
			if ((huntMap.at(sailPos.row, sailPos.col + 1).type == 'o' && !landFound) || (huntMap.at(sailPos.row, sailPos.col + 1).type == '$' && !landFound))
			{
				search_box.push_back(huntMap.at(sailPos.row, sailPos.col + 1));
				landFound = true;
			}
			sail_box.push_back(huntMap.at(sailPos.row, sailPos.col + 1));
			huntMap.at(sailPos.row, sailPos.col + 1).isInvestigated = true;
			path.push_back('E');
		}
		if (order[i] == 'S' && sailPos.row != huntMap.size - 1 && huntMap.checkSail(isCaptain, huntMap.at(sailPos.row + 1, sailPos.col)))
		{
			if ((huntMap.at(sailPos.row + 1, sailPos.col).type == 'o' && !landFound) || (huntMap.at(sailPos.row + 1, sailPos.col).type == '$' && !landFound))
			{
				search_box.push_back(huntMap.at(sailPos.row + 1, sailPos.col));
				landFound = true;
			}
			sail_box.push_back(huntMap.at(sailPos.row + 1, sailPos.col));
			huntMap.at(sailPos.row + 1, sailPos.col).isInvestigated = true;
			path.push_back('S');
		}
		if (order[i] == 'W' && sailPos.col != 0 && huntMap.checkSail(isCaptain, huntMap.at(sailPos.row, sailPos.col - 1)))
		{
			if ((huntMap.at(sailPos.row, sailPos.col - 1).type == 'o' && !landFound) || (huntMap.at(sailPos.row, sailPos.col - 1).type == '$' && !landFound))
			{
				search_box.push_back(huntMap.at(sailPos.row, sailPos.col - 1));
				landFound = true;
			}
			sail_box.push_back(huntMap.at(sailPos.row, sailPos.col - 1));
			huntMap.at(sailPos.row, sailPos.col - 1).isInvestigated = true;
			path.push_back('W');
		} // end of if statements
	} // for loop
	if (landFound)
	{
		if (isVerbose)
		{
			islandCount++;
			cout << "Went ashore at: " << search_box.back().row << "," << search_box.back().col << endl;
		}
		isCaptain = false;
	}
}


