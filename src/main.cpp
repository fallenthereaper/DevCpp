// main.cpp : Defines the entry point for the application.
//

#define MAX_CANVAS_WIDTH 112
#define MAX_CANVAS_HEIGHT 28

#include "src/core/input/keyboard_handler.h"
#include "src/core/main.h"
#include "src/core/game_engine.h"
#include "src/core/utils/utility.h"
#include "src/core/utils/containers.h"
#include <vector>
#include "src/core/bank/bank.h"
#include "src/core/bank/bank_account.h"
#include "src/core//tictac_game.h"
#include <sstream>
#include <iomanip>
#include "src/core/shop/registry/item_registry.h"
#include "src/core/shop/registry/items.h";
#include "src/core/shop/game.h";
#include "src/core/Game_renderer.h";


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


  ExolorGame::Game* game = nullptr;

  void coreInit() {

      ExolorGame::registerItems();
  }

  // Function to compare two canvas data arrays
  bool compareData(const char** canvas1, const char** canvas2, int width, int height) {
      for (int y = 0; y < height; ++y) {
          for (int x = 0; x < width; ++x) {
              if (canvas1[y][x] != canvas2[y][x]) {
                  return false; // Found a difference in the canvas content
              }
          }
      }
      return true; // Canvases are identical
  }

  // Function to copy canvas data
  const char** copyData(const char** canvas, int width, int height) {
      char** copiedCanvas = new char* [height];
      for (int y = 0; y < height; ++y) {
          copiedCanvas[y] = new char[width];
          for (int x = 0; x < width; ++x) {
              copiedCanvas[y][x] = canvas[y][x];
          }
      }
      return const_cast<const char**>(copiedCanvas);
  }

  void deleteData(const char** canvas, int height) {
      if (canvas != nullptr) {
          for (int y = 0; y < height; ++y) {
              delete[] canvas[y]; // Free each row of the canvas
          }
          delete[] canvas; // Free the array of rows
      }
  }


  atomic<bool> isRunning = true;

  // Function to handle game updates
  void serverThread() {

      while (game->isRunning()) {
          // Perform game updates
          GameRenderer::TextCanvas* canvas = game->getCanvas();
          game->update(canvas);

          // Sleep for a short time to control update rate
          this_thread::sleep_for(chrono::milliseconds(0));
      }
  }

  // Function to handle rendering
  void renderThread() {
      const char** prevCanvas = nullptr;
   
      while (game->isRunning()) {
          GameRenderer::TextCanvas* canvas = game->getCanvas();
          const char** currentCanvas = canvas->getData();

          // Check if the canvas content has changed
          if (prevCanvas == nullptr || !compareData(prevCanvas, currentCanvas, canvas->getWidth(), canvas->getHeight())) {
              // Render the game only if the canvas content has changed
              GameRenderer::render(game);

              // Update the previous canvas to match the current canvas
              if (prevCanvas != nullptr) {
                  deleteData(prevCanvas, canvas->getHeight());
              }
              prevCanvas = copyData(currentCanvas, canvas->getWidth(), canvas->getHeight());
          }

          // Sleep for a short time to control rendering rate
          this_thread::sleep_for(chrono::milliseconds(0));
      }

      // Clean up allocated memory for the last recorded canvas
      if (prevCanvas != nullptr) {
          deleteData(prevCanvas, game->getCanvas()->getHeight());
      }
  }


  int SDL_main(int argc, char* argv[]) {
      // Initialize game
      coreInit();
      game = new ExolorGame::Game(MAX_CANVAS_WIDTH, MAX_CANVAS_HEIGHT, "Exolor");
      game->start();

      // Create threads
     // std::thread updateThread(serverThread);
    // std::thread renderThread(renderThread);

      const char** prevCanvas = nullptr;

      GameRenderer::TextCanvas* canvas = game->getCanvas();
      

      while (game->isRunning()) {


          game->update(canvas);

          const char** currentCanvas = canvas->getData();

          // Check if the canvas content has changed
          if (prevCanvas == nullptr || !compareData(prevCanvas, currentCanvas, canvas->getWidth(), canvas->getHeight())) {
              // Render the game only if the canvas content has changed
              GameRenderer::render(game);

              // Update the previous canvas to match the current canvas
              if (prevCanvas != nullptr) {
                  delete[] prevCanvas; // Free the previously allocated memory
              }
              prevCanvas = copyData(currentCanvas, canvas->getWidth(), canvas->getHeight());
          }

          //  GameRenderer::render(game);
      }

      // Clean up allocated memory for the last recorded canvas
      if (prevCanvas != nullptr) {
          delete[] prevCanvas;
      }
  
     

    }

