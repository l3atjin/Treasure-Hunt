// Project ID: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD

#include "game.h"

using namespace std;

game::game(options mode_in, map map_in)
	: order(mode_in.order), treasureMap(map_in),
	isCStack(mode_in.isCStack), isFStack(mode_in.isFQueue)
{

}
