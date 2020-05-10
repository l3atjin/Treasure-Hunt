// Project ID: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD

#include "game.h"

using namespace std;

// game constructor
game::game(options mode_in, map map_in)
	: order(mode_in.order), huntMap(map_in),
	treasurePos(map_in.treasurePos), 
	startPos(map_in.startPos), isCStack(mode_in.isCStack), 
	isFStack(mode_in.isFQueue)
{
	sail_box.push_back(startPos);
	sailPos = startPos;
}

// returns true if the teasure is found
bool game::treasureFound()
{
	return searchPos.row == treasurePos.row &&
		searchPos.col == treasurePos.col;
}

void game::sail()
{
	while (isCaptain) {
		sailInvestigate();
		if (!sail_box.empty())
		{
			if (isCStack)
			{
				sailPos = sail_box.back();
			}
			else
			{
				sailPos = sail_box.front();
			}
		}
	} // while loop

}

void game::sailInvestigate()
{
	for (int i = 0; i < 4; i++)
	{
		if (order[i] == 'N' && sailPos.row != 0 && huntMap.checkSail(isCaptain, *huntMap.at(sailPos.row - 1, sailPos.col)))
		{
			if (isCStack)
			{
				sail_box.push_back(*huntMap.at(sailPos.row - 1, sailPos.col));
				huntMap.at(sailPos.row - 1, sailPos.col)->isInvestigated = true;
			}
			else
			{
				sail_box.push_front(*huntMap.at(sailPos.row - 1, sailPos.col));
			}
		}
		else if (order[i] == 'E' && sailPos.col != huntMap.size - 1 && huntMap.checkSail(isCaptain, *huntMap.at(sailPos.row, sailPos.col + 1)))
		{
			if (isCStack)
			{
				sail_box.push_back(*huntMap.at(sailPos.row, sailPos.col + 1));
			}
			else
			{
				sail_box.push_front(*huntMap.at(sailPos.row, sailPos.col + 1));
			}
		}
		else if (order[i] == 'S' && sailPos.row != huntMap.size - 1 && huntMap.checkSail(isCaptain, *huntMap.at(sailPos.row + 1, sailPos.col)))
		{
			if (isCStack)
			{
				sail_box.push_back(*huntMap.at(sailPos.row + 1, sailPos.col));
			}
			else
			{
				sail_box.push_front(*huntMap.at(sailPos.row + 1, sailPos.col));
			}
		}
		else if (order[i] == 'W' && sailPos.col != 0 && huntMap.checkSail(isCaptain, *huntMap.at(sailPos.row, sailPos.col - 1)))
		{
			if (isCStack)
			{
				sail_box.push_back(*huntMap.at(sailPos.row, sailPos.col - 1));
			}
			else
			{
				sail_box.push_front(*huntMap.at(sailPos.row, sailPos.col - 1));
			}
		} // end of if statements
	} // for loop
}


