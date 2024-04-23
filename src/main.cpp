// main.cpp : Defines the entry point for the application.
//

#include "src/core/main.h"
#include "src/core/utils/utility.h"
#include "src/core/utils/containers.h"
#include <vector>
#include "src/core/practice.h"
#include "src/core/bank/bank.h"
#include "src/core/bank/bank_account.h"
#include "src/core//tictac_game.h"
#include <sstream>
#include <iomanip>
#include "src/core/shop/registry/ItemRegistry.h"
#include "src/core/shop/registry/Items.h";
#include "src/core/shop/Game.h";
#include "src/core/GameRenderer.h";
using namespace std;
using namespace Utility;
using namespace Utility::Mth;

//using Vec3 = Utility::Mth::Vec3;

///int argc, char * argv[]

static const std::vector<std::string> BELOW_TWENTY = {
       "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
       "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen",
       "seventeen", "eighteen", "nineteen"
};

unsigned long long hexToDecimal(const std::string& hexString) {
    unsigned long long decimalValue;
    std::stringstream ss;
    ss << std::hex << hexString;
    ss >> decimalValue;
    return decimalValue;
}

// Function to convert a decimal integer to a hexadecimal string
  std::string decimalToHex(unsigned long long decimalValue) {
    std::stringstream ss;
    ss << std::hex << std::uppercase << decimalValue;
    return ss.str();
}

  ShopGame::Game* game = nullptr;


  void clearScreen() {
      system("cls");
  }


  using Game = ShopGame::Game;

    int main(int argc, const char * argv[])
    {
      
        ShopGame::registerItems();

        game = new Game(50, 50);

   
        game->start();

 

        while (game->isRunning()) {
        
        
          
            game->update();

            GameRenderer::render(game);
        }

        GameRenderer::clearScreen();

        game->clean();

    
        return 0;
    }

