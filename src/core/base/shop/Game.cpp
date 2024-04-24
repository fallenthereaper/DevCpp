#include "src/core/shop/Game.h"

namespace ShopGame {

    // Constructor
    Game::Game() : running(true) , canvas(new GameRenderer::TextCanvas(0,0)) {}

    Game::Game(int canvasWidth, int canvasHeight) : canvas(new GameRenderer::TextCanvas(canvasWidth, canvasHeight)), running(true) {}

    // Destructor
    Game::~Game() {
       
    }

    void Game::update() {  //TODO: move these to be able to be represented by a GameState interface so we can have more control what gets renderered
        std::string input;

        GameRenderer::TextCanvas* canvas = this->getCanvas();

        canvas->drawSquare(Vec2(25 + 9, 1), 24, 5, '*', "Item Shop", true);

        //FIRST ROW
        canvas->drawSquare(Vec2(25, 7), 14, 3, '*', "Item 1", true);
        canvas->drawSquare(Vec2(25 + 14 + 2, 7), 14, 3, '*', "Item 2", true);
        canvas->drawSquare(Vec2(25 + 14 + 14 + 4, 7), 14, 3, '*', "Item 3", true);
        //SECOND ROW
        canvas->drawSquare(Vec2(25, 10), 14, 3, '*', "Item 4", true);
        canvas->drawSquare(Vec2(25 + 14 + 2, 10), 14, 3, '*', "Item 5", true);
        canvas->drawSquare(Vec2(25 + 14 + 14 + 4, 10), 14, 3, '*', "Item 6", true);
  
      std::cin >> input;
        if (input == "q" || input == "exit") {
            getCanvas()->drawSquare(Vec2(5, 5), 9, 5, '*', "Game Update", true);
           
            //running = false;
        } else if (input == "0" ) {
            getCanvas()->drawSquare(Vec2(5, 5), 9, 5, '*', "Frame 0", true);

            //running = false;
        }
        else if (input == "1") {
            getCanvas()->drawSquare(Vec2(5, 5), 9, 5, '*', "Frame 1", true);

            //running = false;
        }

        else if (input == "2") {
            getCanvas()->drawSquare(Vec2(5, 5), 9, 5, '*', "Frame 2", true);

            //running = false;
        }
        else if (input == "3") {
            getCanvas()->drawSquare(Vec2(5, 5), 9, 5, '*', "Frame 3", true);

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
       // std::cout << "Shop Game" << std::endl;
       // std::cout << "Type 'exit' to quit the game." << std::endl;

    
    }

    // Helper method for handling user input
    void Game::handleInput(const std::string& input) {
       
      std::cout << "Command not recognized. Try again." << std::endl;
    }

} // namespace ShopGame