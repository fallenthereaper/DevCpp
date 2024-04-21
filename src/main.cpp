// main.cpp : Defines the entry point for the application.
//

#include "main.h"
#include "utility.h"
#include <vector>
#include "practice.h"
#include "tictac_game.h"
using namespace std;
using Day = Utility::Day;
using namespace Utility;
using namespace Utility::Mth;

//using Vec3 = Utility::Mth::Vec3;

///int argc, char * argv[]
int main()
{
	Consumer<int> consumer = [](int x) {

			std::cout << "n called: " << x << std::endl;
		
		};

	

	Predicate<int> predicate([](int x) -> bool { return false;});

	Predicate<int> predicate2 = [](int x) -> bool { return false; };

	Optional<string> optional();




	std::vector<int> nums = std::vector<int>{ 1, 2, 3, 4, 5, 7, 8 };

std:for_each(nums.begin(), nums.end(), consumer);

	Practice::startUp();
	//TicTacGame::startUp();

	Vec2 mousePosition = Vec2(-37, 2.3);


	std::cout << mousePosition * 3 + mousePosition * 100 << std::endl;



	Day day = Day::FRIDAY;


	//std::cout << pairList.at(0).first << '\n';
	return 0;
}
