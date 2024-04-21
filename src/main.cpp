// main.cpp : Defines the entry point for the application.
//

#include "main.h"
#include "utility.h"
#include "containers.h"
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

    Container::ArrayList<int> myList;

    
    for (int i = 1; i <= 20; ++i) {
        myList.add(i);
    }

    // Define a consumer function to print whether a number is even or odd
    Function<int, string> numberEvaluator = [](int x) -> string {
        return (x % 2 == 0) ? "Even" : "Odd";
        };

    // Define a consumer function to print the number along with its evaluation
    Consumer<int> consumer = [numberEvaluator](int x) {
        std::cout << numberEvaluator(x) << ": " << x << std::endl;
        };

    // Use forEach with the List and the consumer function
      //forEach<int>(myList, consumer);

      myList.forEach(consumer);

    // Example of using forEach with a lambda directly
 

	Practice::startUp();
	//TicTacGame::startUp();

	Vec2 mousePosition = Vec2(-37, 2.3);

	return 0;
}
