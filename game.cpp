// Project ID: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD

#include "game.h"

using namespace std;

// game constructor
game::game(options mode_in, map map_in)
	: order(mode_in.order), huntMap(map_in),
	treasurePos(map_in.treasurePos), 
	startPos(map_in.startPos), isCStack(mode_in.isCStack), 
	isFStack(!mode_in.isFQueue)
{
	sailPos = startPos;
	sailPos.isDiscovered = true;
	sail_box.push_back(startPos);
}

// returns true if the teasure is found

void game::conTest()
{
	cout << order[0] << " ";
	cout << order[1] << " ";
	cout << order[2] << " ";
	cout << order[3] << " ";
	cout << endl;
	cout << endl;

	cout << "Start position: " << startPos.type << " " << startPos.row << " " << startPos.col << endl;
	cout << "Treasure position: " << treasurePos.type << " " << treasurePos.row << " " << treasurePos.col << endl;
	cout << "Sail position: " << sailPos.type << " " << sailPos.row << " " << sailPos.col << endl;



}

void game::sail()
{
	while (isCaptain && !treasureFound) {
		if (sail_box.empty())
		{
			break;
		}
		if (isCStack)
		{
			sailPos = sail_box.back();
			sail_box.pop_back();
			sailPos.isDiscovered = true;
		}
		else
		{
			sailPos = sail_box.front();
			sail_box.pop_front();
			sailPos.isDiscovered = true;
		}
		cout << "Sail location: " << sailPos.row << " " << sailPos.col << endl;
		sailInvestigate();
		
		
	} // while loop
}

void game::search()
{
	while (!isCaptain && !treasureFound)
	{
		if (searchPos.type == '$')
		{
			treasureFound = true;
			return;
		}
		if (search_box.empty())
		{
			isCaptain = true;
			break;
		}
		if (isFStack)
		{
			searchPos = search_box.back();
			search_box.pop_back();
			huntMap.at(searchPos.row, searchPos.col).isDiscovered = true;
			searchPos.isDiscovered = true;
		}
		else
		{
			searchPos = search_box.front();
			search_box.pop_front();
			huntMap.at(searchPos.row, searchPos.col).isDiscovered = true;
			searchPos.isDiscovered = true;
		}
		cout << "Search location: " << searchPos.row << " " << searchPos.col << endl;
		
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
				break;
			}
			if (isFStack)
			{
				search_box.push_back(huntMap.at(searchPos.row - 1, searchPos.col));
				huntMap.at(searchPos.row - 1, searchPos.col).isInvestigated = true;
			}
			else
			{
				search_box.push_front(huntMap.at(searchPos.row - 1, searchPos.col));
				huntMap.at(searchPos.row - 1, searchPos.col).isInvestigated = true;
			}
		}
		else if (order[i] == 'E' && searchPos.col != huntMap.size - 1 && huntMap.checkSail(isCaptain, huntMap.at(searchPos.row, searchPos.col + 1)))
		{
			if (huntMap.at(searchPos.row, searchPos.col + 1).type == '$')
			{
				treasureFound = true;
				search_box.push_back(huntMap.at(searchPos.row, searchPos.col + 1));
				break;
			}
			if (isFStack)
			{
				search_box.push_back(huntMap.at(searchPos.row, searchPos.col + 1));
				huntMap.at(searchPos.row, searchPos.col + 1).isInvestigated = true;
			}
			else
			{
				search_box.push_front(huntMap.at(searchPos.row, searchPos.col + 1));
				huntMap.at(searchPos.row, searchPos.col + 1).isInvestigated = true;
			}
		}
		else if (order[i] == 'S' && searchPos.row != huntMap.size - 1 && huntMap.checkSail(isCaptain, huntMap.at(searchPos.row + 1, searchPos.col)))
		{
			if (huntMap.at(searchPos.row + 1, searchPos.col).type == '$')
			{
				treasureFound = true;
				search_box.push_back(huntMap.at(searchPos.row + 1, searchPos.col));
				break;
			}
			if (isFStack)
			{
				search_box.push_back(huntMap.at(searchPos.row + 1, searchPos.col));
				huntMap.at(searchPos.row + 1, searchPos.col).isInvestigated = true;
			}
			else
			{
				search_box.push_front(huntMap.at(searchPos.row + 1, searchPos.col));
				huntMap.at(searchPos.row + 1, searchPos.col).isInvestigated = true;
			}
		}
		else if (order[i] == 'W' && searchPos.col != 0 && huntMap.checkSail(isCaptain, huntMap.at(searchPos.row, searchPos.col - 1)))
		{
			if (huntMap.at(searchPos.row, searchPos.col - 1).type == '$')
			{
				treasureFound = true;
				search_box.push_back(huntMap.at(searchPos.row, searchPos.col - 1));
				break;
			}
			if (isFStack)
			{
				search_box.push_back(huntMap.at(searchPos.row, searchPos.col - 1));
				huntMap.at(searchPos.row, searchPos.col - 1).isInvestigated = true;
			}
			else
			{
				search_box.push_front(huntMap.at(searchPos.row, searchPos.col - 1));
				huntMap.at(searchPos.row, searchPos.col - 1).isInvestigated = true;
			}
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
			else if (isCStack)
			{
				sail_box.push_back(huntMap.at(sailPos.row - 1, sailPos.col));
				huntMap.at(sailPos.row - 1, sailPos.col).isInvestigated = true;
			}
			else
			{
				sail_box.push_front(huntMap.at(sailPos.row - 1, sailPos.col));
				huntMap.at(sailPos.row - 1, sailPos.col).isInvestigated = true;
			}
		}
		if (order[i] == 'E' && sailPos.col != huntMap.size - 1 && huntMap.checkSail(isCaptain, huntMap.at(sailPos.row, sailPos.col + 1)))
		{
			if ((huntMap.at(sailPos.row, sailPos.col + 1).type == 'o' && !landFound) || (huntMap.at(sailPos.row, sailPos.col + 1).type == '$' && !landFound))
			{
				search_box.push_back(huntMap.at(sailPos.row, sailPos.col + 1));
				landFound = true;
			}
			else if (isCStack)
			{
				sail_box.push_back(huntMap.at(sailPos.row, sailPos.col + 1));
				huntMap.at(sailPos.row, sailPos.col + 1).isInvestigated = true;
			}
			else
			{
				sail_box.push_front(huntMap.at(sailPos.row, sailPos.col + 1));
				huntMap.at(sailPos.row, sailPos.col + 1).isInvestigated = true;
			}
		}
		if (order[i] == 'S' && sailPos.row != huntMap.size - 1 && huntMap.checkSail(isCaptain, huntMap.at(sailPos.row + 1, sailPos.col)))
		{
			if ((huntMap.at(sailPos.row + 1, sailPos.col).type == 'o' && !landFound) || (huntMap.at(sailPos.row + 1, sailPos.col).type == '$' && !landFound))
			{
				search_box.push_back(huntMap.at(sailPos.row + 1, sailPos.col));
				landFound = true;
			}
			else if (isCStack)
			{
				sail_box.push_back(huntMap.at(sailPos.row + 1, sailPos.col));
				huntMap.at(sailPos.row + 1, sailPos.col).isInvestigated = true;
			}
			else
			{
				sail_box.push_front(huntMap.at(sailPos.row + 1, sailPos.col));
				huntMap.at(sailPos.row + 1, sailPos.col).isInvestigated = true;
			}
		}
		if (order[i] == 'W' && sailPos.col != 0 && huntMap.checkSail(isCaptain, huntMap.at(sailPos.row, sailPos.col - 1)))
		{
			if ((huntMap.at(sailPos.row, sailPos.col - 1).type == 'o' && !landFound) || (huntMap.at(sailPos.row, sailPos.col - 1).type == '$' && !landFound))
			{
				search_box.push_back(huntMap.at(sailPos.row, sailPos.col - 1));
				landFound = true;
			}
			else if (isCStack)
			{
				sail_box.push_back(huntMap.at(sailPos.row, sailPos.col - 1));
				huntMap.at(sailPos.row, sailPos.col - 1).isInvestigated = true;
			}
			else
			{
				sail_box.push_front(huntMap.at(sailPos.row, sailPos.col - 1));
				huntMap.at(sailPos.row, sailPos.col - 1).isInvestigated = true;
			}
		} // end of if statements
	} // for loop
	if (landFound)
	{
		isCaptain = false;
	}
}


