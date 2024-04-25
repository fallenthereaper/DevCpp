#include "src/core/shop/game.h"

namespace ShopGame {

    // Constructor
    Game::Game() : running(true) , canvas(new GameRenderer::TextCanvas(0,0)) {
        registerCommands();
    }

    Game::Game(int canvasWidth, int canvasHeight) : canvas(new GameRenderer::TextCanvas(canvasWidth, canvasHeight)), running(true) {
    
        registerCommands();
    }

    // Destructor
    Game::~Game() {
        registerCommands();
    }

    void Game::addCommand(const std::string& command, const std::function<void(Game*)> consumer) {
     //   commandMap[command] = (consumer);
        commandMap.emplace(command, consumer);
    }

    void Game::registerCommands() {
        GameRenderer::TextCanvas* canvas = this->getCanvas();

        addCommand("shop", [canvas](ShopGame::Game* g) {
         
         
            canvas->drawSquare(Vec2(25 + 9, 1), 24, 5, '*', "Item Shop", true);

            //FIRST ROW
            g->getCanvas()->drawSquare(Vec2(25, 7), 14, 3, '*', "Item 1", true);
            g->getCanvas()->drawSquare(Vec2(25 + 14 + 2, 7), 14, 3, '*', "Item 2", true);
            g->getCanvas()->drawSquare(Vec2(25 + 14 + 14 + 4, 7), 14, 3, '*', "Item 3", true);
            //SECOND ROW
            g->getCanvas()->drawSquare(Vec2(25, 10), 14, 3, '*', "Item 4", true);
            g->getCanvas()->drawSquare(Vec2(25 + 14 + 2, 10), 14, 3, '*', "Item 5", true);
            g->getCanvas()->drawSquare(Vec2(25 + 14 + 14 + 4, 10), 14, 3, '*', "Item 6", true);
            });

        addCommand("exit", [canvas](Game* g) {
            canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Game Closed", true);

            g->running = false; // Set running flag to false to exit the game loop
            });

        addCommand("clear", [canvas](Game* g) {
         
            canvas->clear(); // Clear the canvas
            canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Cleared Canvas", true);
            });
    }

    // Method to process input and trigger associated consumers
    void Game::processInput(const std::string& input) {
        auto it = commandMap.find(input);
        if (it != commandMap.end()) {
            // Execute the consumer associated with the input command
            it->second(this); // Pass 'this' pointer to the Game object
        }
        else {
            canvas->drawSquare(Vec2(38, 10), 38, 5, '*', "Command not recognized. Try again.", true);
          
        }
    }

   

    void Game::update(GameRenderer::TextCanvas* canvas) {
        canvas->drawSquare(Vec2(0, 0), 112, 28, '*', "", true);
        std::string input;
        std::cout << "Enter a command: ";
        std::cin >> input;
       
        processInput(input);
    }


    void Game::clean() {

     
   
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
       std::cout << "[Game Started]" << std::endl;
      std::cout << "Type 'exit' to quit the game." << std::endl;
    }


    // Helper method for handling user input
    void Game::handleInput(const std::string& input) {


       
      std::cout << "Command not recognized. Try again." << std::endl;
    }

} // namespace ShopGame