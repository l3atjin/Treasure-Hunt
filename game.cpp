// Project ID: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD

#include "game.h"

using namespace std;

// game constructor
game::game(options mode_in, map map_in)
	: order(mode_in.order), huntMap(map_in),
	treasurePos(&map_in.treasurePos), 
	startPos(&map_in.startPos), isCStack(mode_in.isCStack), 
	isFStack(mode_in.isFQueue)
{
	sail_box.push_back(startPos);
	sailPos = startPos;
	sailPos->isDiscovered = true;
}

// returns true if the teasure is found

void game::sail()
{
	while (isCaptain && !treasureFound) {
		if (sail_box.empty())
		{
			break;
		}
		sailInvestigate();
		if (isCStack)
		{
			sailPos = sail_box.back();
			sail_box.pop_back();
			sailPos->isDiscovered = true;
		}
		else
		{
			sailPos = sail_box.front();
			sail_box.pop_front();
			sailPos->isDiscovered = true;
		}
	} // while loop
}

void game::search()
{
	while (!isCaptain && !treasureFound)
	{
		if (sail_box.empty())
		{
			break;
		}
		searchInvestigate();
		if (isFStack)
		{
			searchPos = search_box.back();
			search_box.pop_back();
			searchPos->isDiscovered = true;
		}
		else
		{
			searchPos = search_box.front();
			search_box.pop_front();
			searchPos->isDiscovered = true;
		}
	}
}

void game::searchInvestigate()
{
	for (int i = 0; i < 4; i++)
	{
		if (order[i] == 'N' && searchPos->row != 0 && huntMap.checkSail(isCaptain, huntMap.at(searchPos->row - 1, searchPos->col)))
		{
			if (huntMap.at(searchPos->row - 1, searchPos->col)->type == '$')
			{
				treasureFound = true;
				search_box.push_back(huntMap.at(searchPos->row - 1, searchPos->col));
				break;
			}
			if (isFStack)
			{
				search_box.push_back(huntMap.at(searchPos->row - 1, searchPos->col));
				huntMap.at(searchPos->row - 1, searchPos->col)->isInvestigated = true;
			}
			else
			{
				search_box.push_front(huntMap.at(searchPos->row - 1, searchPos->col));
				huntMap.at(searchPos->row - 1, searchPos->col)->isInvestigated = true;
			}
		}
		else if (order[i] == 'E' && searchPos->col != huntMap.size - 1 && huntMap.checkSail(isCaptain, huntMap.at(searchPos->row, searchPos->col + 1)))
		{
			if (huntMap.at(searchPos->row, searchPos->col + 1)->type == '$')
			{
				treasureFound = true;
				search_box.push_back(huntMap.at(searchPos->row, searchPos->col + 1));
				break;
			}
			if (isFStack)
			{
				search_box.push_back(huntMap.at(searchPos->row, searchPos->col + 1));
				huntMap.at(searchPos->row, searchPos->col + 1)->isInvestigated = true;
			}
			else
			{
				search_box.push_front(huntMap.at(searchPos->row, searchPos->col + 1));
				huntMap.at(searchPos->row, searchPos->col + 1)->isInvestigated = true;
			}
		}
		else if (order[i] == 'S' && searchPos->row != huntMap.size - 1 && huntMap.checkSail(isCaptain, huntMap.at(searchPos->row + 1, searchPos->col)))
		{
			if (huntMap.at(searchPos->row + 1, searchPos->col)->type == '$')
			{
				treasureFound = true;
				search_box.push_back(huntMap.at(searchPos->row + 1, searchPos->col));
				break;
			}
			if (isFStack)
			{
				search_box.push_back(huntMap.at(searchPos->row + 1, searchPos->col));
				huntMap.at(searchPos->row + 1, searchPos->col)->isInvestigated = true;
			}
			else
			{
				search_box.push_front(huntMap.at(searchPos->row + 1, searchPos->col));
				huntMap.at(searchPos->row + 1, searchPos->col)->isInvestigated = true;
			}
		}
		else if (order[i] == 'W' && searchPos->col != 0 && huntMap.checkSail(isCaptain, huntMap.at(searchPos->row, searchPos->col - 1)))
		{
			if (huntMap.at(sailPos->row, sailPos->col - 1)->type == '$')
			{
				treasureFound = true;
				search_box.push_back(huntMap.at(sailPos->row, sailPos->col - 1));
				break;
			}
			if (isFStack)
			{
				search_box.push_back(huntMap.at(searchPos->row, searchPos->col - 1));
				huntMap.at(searchPos->row, searchPos->col - 1)->isInvestigated = true;
			}
			else
			{
				search_box.push_front(huntMap.at(searchPos->row, searchPos->col - 1));
				huntMap.at(searchPos->row, searchPos->col - 1)->isInvestigated = true;
			}
		} // end of if statements
	} // for loop
}

void game::sailInvestigate()
{
	for (int i = 0; i < 4; i++)
	{
		if (order[i] == 'N' && sailPos->row != 0 && huntMap.checkSail(isCaptain, huntMap.at(sailPos->row - 1, sailPos->col)))
		{
			if (huntMap.at(sailPos->row - 1, sailPos->col)->type == 'o')
			{
				isCaptain = false;
				search_box.push_back(huntMap.at(sailPos->row - 1, sailPos->col));
				break;
			}
			if (isCStack)
			{
				sail_box.push_back(huntMap.at(sailPos->row - 1, sailPos->col));
				huntMap.at(sailPos->row - 1, sailPos->col)->isInvestigated = true;
			}
			else
			{
				sail_box.push_front(huntMap.at(sailPos->row - 1, sailPos->col));
				huntMap.at(sailPos->row - 1, sailPos->col)->isInvestigated = true;
			}
		}
		else if (order[i] == 'E' && sailPos->col != huntMap.size - 1 && huntMap.checkSail(isCaptain, huntMap.at(sailPos->row, sailPos->col + 1)))
		{
			if (huntMap.at(sailPos->row, sailPos->col + 1)->type == 'o')
			{
				isCaptain = false;
				search_box.push_back(huntMap.at(sailPos->row, sailPos->col + 1));
				break;
			}
			if (isCStack)
			{
				sail_box.push_back(huntMap.at(sailPos->row, sailPos->col + 1));
				huntMap.at(sailPos->row, sailPos->col + 1)->isInvestigated = true;
			}
			else
			{
				sail_box.push_front(huntMap.at(sailPos->row, sailPos->col + 1));
				huntMap.at(sailPos->row, sailPos->col + 1)->isInvestigated = true;
			}
		}
		else if (order[i] == 'S' && sailPos->row != huntMap.size - 1 && huntMap.checkSail(isCaptain, huntMap.at(sailPos->row + 1, sailPos->col)))
		{
			if (huntMap.at(sailPos->row + 1, sailPos->col)->type == 'o')
			{
				isCaptain = false;
				search_box.push_back(huntMap.at(sailPos->row + 1, sailPos->col));
				break;
			}
			if (isCStack)
			{
				sail_box.push_back(huntMap.at(sailPos->row + 1, sailPos->col));
				huntMap.at(sailPos->row + 1, sailPos->col)->isInvestigated = true;
			}
			else
			{
				sail_box.push_front(huntMap.at(sailPos->row + 1, sailPos->col));
				huntMap.at(sailPos->row + 1, sailPos->col)->isInvestigated = true;
			}
		}
		else if (order[i] == 'W' && sailPos->col != 0 && huntMap.checkSail(isCaptain, huntMap.at(sailPos->row, sailPos->col - 1)))
		{
			if (huntMap.at(sailPos->row, sailPos->col - 1)->type == 'o')
			{
				isCaptain = false;
				search_box.push_back(huntMap.at(sailPos->row, sailPos->col - 1));
				break;
			}
			if (isCStack)
			{
				sail_box.push_back(huntMap.at(sailPos->row, sailPos->col - 1));
				huntMap.at(sailPos->row, sailPos->col - 1)->isInvestigated = true;
			}
			else
			{
				sail_box.push_front(huntMap.at(sailPos->row, sailPos->col - 1));
				huntMap.at(sailPos->row, sailPos->col - 1)->isInvestigated = true;
			}
		} // end of if statements
	} // for loop
}


