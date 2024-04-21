// main.cpp : Defines the entry point for the application.
//

#include "main.h"
#include "utility.h"
#include <vector>
#include "practice.h"
#include "tictac_game.h"
using namespace std;
using Day = Utility::Day;

using Vec2 = Utility::Mth::Vec2;
using Vec3 = Utility::Mth::Vec3;

///int argc, char * argv[]
int main()
{


	Practice::startUp();
	//TicTacGame::startUp();

	Vec2 mousePosition = Vec2(2, 0);


	std::cout << mousePosition * 100 << std::endl;



	Day day = Day::FRIDAY;


	//std::cout << pairList.at(0).first << '\n';
	return 0;
}
