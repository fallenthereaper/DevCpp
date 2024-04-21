// main.cpp : Defines the entry point for the application.
//

#include "main.h"
#include <vector>
#include "practice.h"
#include "tictac_game.h"
using namespace std;


///int argc, char * argv[]
int main()
{


	Practice::startUp();
	TicTacGame::startUp();


	//std::cout << pairList.at(0).first << '\n';
	return 0;
}
