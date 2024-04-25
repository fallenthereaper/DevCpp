#include "src/core/shop/game.h"

namespace ShopGame {

    // Constructor
    Game::Game() : running(true) , canvas(new GameRenderer::TextCanvas(0,0)) {}

    Game::Game(int canvasWidth, int canvasHeight) : canvas(new GameRenderer::TextCanvas(canvasWidth, canvasHeight)), running(true) {}

    // Destructor
    Game::~Game() {
       
    }

    void Game::update(GameRenderer::TextCanvas* canvas) {  //TODO: move these to be able to be represented by a GameState interface so we can have more control what gets renderered
        std::string input;

        canvas->drawSquare(Vec2(0, 0), 112, 28, '*',"", true);


     //   canvas->drawSquare(Vec2(25 + 9, 0), 12, 5, '*', "Game Tick", true);
        
  
        std::cin >> input;




      if (input == "clear") {
          getCanvas()->clear();
      }
      else if (input == "shop") {
          canvas->drawSquare(Vec2(25 + 9, 1), 24, 5, '*', "Item Shop", true);
        
          //FIRST ROW
          canvas->drawSquare(Vec2(25, 7), 14, 3, '*', "Item 1", true);
          canvas->drawSquare(Vec2(25 + 14 + 2, 7), 14, 3, '*', "Item 2", true);
          canvas->drawSquare(Vec2(25 + 14 + 14 + 4, 7), 14, 3, '*', "Item 3", true);
          //SECOND ROW
          canvas->drawSquare(Vec2(25, 10), 14, 3, '*', "Item 4", true);
          canvas->drawSquare(Vec2(25 + 14 + 2, 10), 14, 3, '*', "Item 5", true);
          canvas->drawSquare(Vec2(25 + 14 + 14 + 4, 10), 14, 3, '*', "Item 6", true);
      }

      else if (input == "q" || input == "exit") {
            canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Game Closed", true);
           
             running = false;
        } else if (input == "0" ) {
            canvas->drawSquare(Vec2(5, 5), 9, 5, '*', "Frame 0", true);

            //running = false;
        }
        else if (input == "1") {
            canvas->drawSquare(Vec2(5, 5), 9, 5, '*', "Frame 1", true);
        }
        else if (input == "2") {
            canvas->drawSquare(Vec2(10, 10), 9, 5, '*', "Frame 2", true);

            //running = false;
        }
        else if (input == "3") {
            canvas->drawSquare(Vec2(5, 5), 9, 5, '*', "Frame 3", true);

            //running = false;
        } 
        else if (input == "4") {
            getCanvas()->drawSquare(Vec2(5, 5), 9, 5, '*', "Frame 4", true);

            //running = false;
        }
    }

    void Game::clean() {

        getCanvas()->drawSquare(Vec2(0, 0), 10, 10, '*', "Game Ended", true);
   
    }

    void Game::render() {

        for (auto a : getGameStates()) {
            a.accept(this);
        }

        (*getCanvas()).render();
    }

    const bool Game::isRunning() {

        return this->running;
    }

    GameRenderer::TextCanvas* Game::getCanvas() {

        return canvas;
    }

    // Method to start the game
    void Game::start() {
       std::cout << "[Game Started]" << std::endl;
      std::cout << "Type 'exit' to quit the game." << std::endl;
    }


    std::vector<Utility::Consumer<Game*>> Game::getGameStates() const {
        return gameFrames;
    }

    Utility::Consumer<Game*> Game::getGameState() {
        return currentFrame;

    }

    // Helper method for handling user input
    void Game::handleInput(const std::string& input) {


       
      std::cout << "Command not recognized. Try again." << std::endl;
    }

} // namespace ShopGame