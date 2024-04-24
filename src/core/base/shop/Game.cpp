#include "src/core/shop/Game.h"

namespace ShopGame {

    // Constructor
    Game::Game() : running(true) , canvas(new GameRenderer::TextCanvas(0,0)) {}

    Game::Game(int canvasWidth, int canvasHeight) : canvas(new GameRenderer::TextCanvas(canvasWidth, canvasHeight)), running(true) {}

    // Destructor
    Game::~Game() {
       
    }

    void Game::update() { 
        std::string input;
  
       // std::cin >> input;
        if (input == "q" || input == "exit") {
            getCanvas()->drawSquare(Vec2(5, 5), 10, 10, '*', "Game Ended", true);
            running = false;
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

        getCanvas()->drawSquare(Vec2(14, 14), 8, 5, '*', "Game Started", true);
        getCanvas()->drawCircle(Vec2(6, 6), 3, '*');
        
    }

    // Helper method for handling user input
    void Game::handleInput(const std::string& input) {
       
      std::cout << "Command not recognized. Try again." << std::endl;
    }

} // namespace ShopGame