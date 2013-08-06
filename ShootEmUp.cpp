// ShootEmUp.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "Game.hpp"

/*! 
 *  \brief     Main file of the ShootEmUp game
 *  \author    Vincent Studer
 *  \date      2013
 *  \copyright GNU Public License.
 */

int _tmain(int argc, _TCHAR* argv[])
{
	Game game;
	if(game.loadConfig())
		game.StartGame();
	std::cout << "Leaving game now !" << std::endl;
	while(true) {}
    return 0;
}

