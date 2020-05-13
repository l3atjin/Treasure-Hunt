// Project ID: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD

#include "game.h"

using namespace std;

// game constructor
game::game(options& mode_in, vector<vector <Point>>& grid_in, Position startPos_in, Position treasurePos_in, int size_in)
	: order(mode_in.order), grid(grid_in),
	treasurePos(treasurePos_in),
	startPos(startPos_in), isCStack(mode_in.isCStack),
	isFStack(!mode_in.isFQueue), isVerbose(mode_in.verbose),
	isStats(mode_in.stats), showMap(mode_in.showMap), showList(mode_in.showList), size(size_in)
{
	//treasurePos.track = '$';
	//grid[treasurePos.row][treasurePos.col].track = '$';
	//.at(treasurePos.row, treasurePos.col).track = '$';
	sailPos = startPos;
	grid[sailPos.row][sailPos.col].track = '@';
	//at(sailPos.row, sailPos.col).track = '@';
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
	Point currentPoint = grid[treasurePos.row][treasurePos.col];
	Position currentPos;
	currentPos.row = treasurePos.row;
	currentPos.col = treasurePos.col;
	pathPos.push_back(currentPos);

	int count = 0;
	path.push_back(currentPoint);
	while (currentPoint.type != '@')
	{
		//cout << path.at(count).type << "\n";
		if (currentPoint.track == 'n')
		{
			if (count > 0 && (path.at(count - 1).track == 'w' || path.at(count - 1).track == 'e'))
			{
				grid[currentPos.row][currentPos.col].type = '+';
			}
			else
			{
				grid[currentPos.row][currentPos.col].type = '|';
			}
			currentPoint = grid[currentPos.row + 1][currentPos.col];
			currentPos.row = currentPos.row + 1;
		}
		else if (currentPoint.track == 'e')
		{
			if (count > 0 && (path.at(count - 1).track == 'n' || path.at(count - 1).track == 's'))
			{
				grid[currentPos.row][currentPos.col].type = '+';
			}
			else
			{
				grid[currentPos.row][currentPos.col].type = '-';
			}
			currentPoint = grid[currentPos.row][currentPos.col - 1];
			currentPos.col = currentPos.col - 1;
		}
		else if (currentPoint.track == 's')
		{
			if (count > 0 && (path.at(count - 1).track == 'w' || path.at(count - 1).track == 'e'))
			{
				grid[currentPos.row][currentPos.col].type = '+';
			}
			else
			{
				grid[currentPos.row][currentPos.col].type = '|';
			}
			currentPoint = grid[currentPos.row - 1][currentPos.col];
			currentPos.row = currentPos.row - 1;
		}
		else if (currentPoint.track == 'w')
		{
			if (count > 0 && (path.at(count - 1).track == 'n' || path.at(count - 1).track == 's'))
			{
				grid[currentPos.row][currentPos.col].type = '+';
			}
			else
			{
				grid[currentPos.row][currentPos.col].type = '-';
			}
			currentPoint = grid[currentPos.row][currentPos.col + 1];
			currentPos.col = currentPos.col + 1;
		}
		path.push_back(currentPoint);
		pathPos.push_back(currentPos);
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
		grid[treasurePos.row][treasurePos.col].type = 'X';
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << grid[i][j].type;
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
				cout << pathPos[i].row << "," << pathPos[i].col << "\n";
			}
		}
		// might wanna check
		cout << "Search:" << "\n";
		for (size_t i = path.size() - 1; i > 0; i--)
		{
			if (path[i].type == 'o' || path[i].type == '$')
			{
				cout << pathPos[i].row << "," << pathPos[i].col << "\n";
			}
		}
		cout << pathPos[0].row << "," << pathPos[0].col << "\n";
	}
}


void game::print_map()
{
	cout << "Printing map:" << "\n";
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << grid[i][j].track << " ";
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
		//cout << "Sail position: " << sailPos.row << "," << sailPos.col << "\n";
		//cout << "	Water tiles discovered: " << waterCount << "\n";

	} // while loop
}

bool game::checkSail(bool isCaptain, Point pos)
{
	if (pos.track != 'M')
	{
		return false;
	}
	else if (pos.type == '#')
	{
		return false;
	}
	else if (!isCaptain && pos.type != 'o' && pos.type != '$')
	{
		return false;
	}
	return true;
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

		//cout << "Search position: " << searchPos.row << "," << searchPos.col << "\n";
		//cout << "	Land tiles discovered: " << landCount << "\n";
	}
}

void game::searchInvestigate()
{
	for (int i = 0; i < 4; i++)
	{
		if (order[i] == 'n' && searchPos.row != 0 && checkSail(isCaptain, grid[searchPos.row - 1][searchPos.col]))
		{
			if (grid[searchPos.row - 1][searchPos.col].type == '$')
			{
				treasureFound = true;
				Position newPos;
				newPos.row = searchPos.row - 1;
				newPos.col = searchPos.col;
				search_box.push_back(newPos);
				grid[searchPos.row - 1][searchPos.col].track = 'n';
				return;
			}
			Position newPos;
			newPos.row = searchPos.row - 1;
			newPos.col = searchPos.col;
			search_box.push_back(newPos);
			grid[searchPos.row - 1][searchPos.col].track = 'n';
		}
		else if (order[i] == 'e' && searchPos.col != size - 1 && checkSail(isCaptain, grid[searchPos.row][searchPos.col + 1]))
		{
			if (grid[searchPos.row][searchPos.col + 1].type == '$')
			{
				treasureFound = true;
				Position newPos;
				newPos.row = searchPos.row;
				newPos.col = searchPos.col + 1;
				search_box.push_back(newPos);
				grid[searchPos.row][searchPos.col + 1].track = 'e';
				return;
			}
			Position newPos;
			newPos.row = searchPos.row;
			newPos.col = searchPos.col + 1;
			search_box.push_back(newPos);
			grid[searchPos.row][searchPos.col + 1].track = 'e';
		}
		else if (order[i] == 's' && searchPos.row != size - 1 && checkSail(isCaptain, grid[searchPos.row + 1][searchPos.col]))
		{
			if (grid[searchPos.row + 1][searchPos.col].type == '$')
			{
				treasureFound = true;
				Position newPos;
				newPos.row = searchPos.row + 1;
				newPos.col = searchPos.col;
				search_box.push_back(newPos);
				grid[searchPos.row + 1][searchPos.col].track = 's';
				return;
			}
			Position newPos;
			newPos.row = searchPos.row + 1;
			newPos.col = searchPos.col;
			search_box.push_back(newPos);
			grid[searchPos.row + 1][searchPos.col].track = 's';

		}
		else if (order[i] == 'w' && searchPos.col != 0 && checkSail(isCaptain, grid[searchPos.row][searchPos.col - 1]))
		{
			if (grid[searchPos.row][searchPos.col - 1].type == '$')
			{
				treasureFound = true;
				Position newPos;
				newPos.row = searchPos.row;
				newPos.col = searchPos.col - 1;
				search_box.push_back(newPos);
				grid[searchPos.row][searchPos.col - 1].track = 'w';
				return;
			}
			Position newPos;
			newPos.row = searchPos.row;
			newPos.col = searchPos.col - 1;
			search_box.push_back(newPos);
			grid[searchPos.row][searchPos.col - 1].track = 'w';

		} // end of if statements
	} // for loop
}

void game::sailInvestigate()
{
	bool landFound = false;
	for (int i = 0; i < 4; i++)
	{
		if (order[i] == 'n' && sailPos.row != 0 && checkSail(isCaptain, grid[sailPos.row - 1][sailPos.col]))
		{
			if ((grid[sailPos.row - 1][sailPos.col].type == 'o' && !landFound) || (grid[sailPos.row - 1][sailPos.col].type == '$' && !landFound))
			{
				Position newPos;
				newPos.row = sailPos.row - 1;
				newPos.col = sailPos.col;
				search_box.push_back(newPos);
				grid[sailPos.row - 1][sailPos.col].track = 'n';
				landFound = true;
				searchPos = newPos;
			}
			else if (grid[sailPos.row - 1][sailPos.col].type == '.')
			{
				Position newPos;
				newPos.row = sailPos.row - 1;
				newPos.col = sailPos.col;
				sail_box.push_back(newPos);
				grid[sailPos.row - 1][sailPos.col].track = 'n';
			}
		}
		if (order[i] == 'e' && sailPos.col != size - 1 && checkSail(isCaptain, grid[sailPos.row][sailPos.col + 1]))
		{
			if ((grid[sailPos.row][sailPos.col + 1].type == 'o' && !landFound) || (grid[sailPos.row][sailPos.col + 1].type == '$' && !landFound))
			{
				Position newPos;
				newPos.row = sailPos.row;
				newPos.col = sailPos.col + 1;
				search_box.push_back(newPos);
				grid[sailPos.row][sailPos.col + 1].track = 'e';
				landFound = true;
				searchPos = newPos;
			}
			else if (grid[sailPos.row][sailPos.col + 1].type == '.')
			{
				Position newPos;
				newPos.row = sailPos.row;
				newPos.col = sailPos.col + 1;
				sail_box.push_back(newPos);
				grid[sailPos.row][sailPos.col + 1].track = 'e';
			}
		}
		if (order[i] == 's' && sailPos.row != size - 1 && checkSail(isCaptain, grid[sailPos.row + 1][sailPos.col]))
		{
			if ((grid[sailPos.row + 1][sailPos.col].type == 'o' && !landFound) || (grid[sailPos.row + 1][sailPos.col].type == '$' && !landFound))
			{
				Position newPos;
				newPos.row = sailPos.row + 1;
				newPos.col = sailPos.col;
				search_box.push_back(newPos);
				grid[sailPos.row + 1][sailPos.col].track = 's';
				landFound = true;
				searchPos = newPos;
			}
			else if (grid[sailPos.row + 1][sailPos.col].type == '.')
			{
				Position newPos;
				newPos.row = sailPos.row + 1;
				newPos.col = sailPos.col;
				sail_box.push_back(newPos);
				grid[sailPos.row + 1][sailPos.col].track = 's';
			}
		}
		if (order[i] == 'w' && sailPos.col != 0 && checkSail(isCaptain, grid[sailPos.row][sailPos.col - 1]))
		{
			if ((grid[sailPos.row][sailPos.col - 1].type == 'o' && !landFound) || (grid[sailPos.row][sailPos.col - 1].type == '$' && !landFound))
			{
				Position newPos;
				newPos.row = sailPos.row;
				newPos.col = sailPos.col - 1;
				search_box.push_back(newPos);
				grid[sailPos.row][sailPos.col - 1].track = 'w';
				landFound = true;
				searchPos = newPos;
			}
			else if (grid[sailPos.row][sailPos.col - 1].type == '.')
			{
				Position newPos;
				newPos.row = sailPos.row;
				newPos.col = sailPos.col - 1;
				sail_box.push_back(newPos);
				grid[sailPos.row][sailPos.col - 1].track = 'w';
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


