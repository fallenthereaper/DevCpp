#include "src/core/shop/game.h"
class ItemRegistry;

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

    void displayItemList(GameRenderer::TextCanvas* canvas, const std::unordered_map<std::string, ItemRegistry::ItemFactory>& itemList, const std::string& displayTitle, const Vec2& topLeft, int maxWidth, int itemWidth, int itemHeight, int maxItemCount) {
        int itemCount = std::min(static_cast<int>(itemList.size()), maxItemCount);

        // Calculate the number of rows needed based on the item count
        int numRows = (itemCount + (maxWidth - 1)) / maxWidth;
        int numCols = (itemCount + numRows - 1) / numRows;

        // Draw the title of the item list
        canvas->drawSquare(topLeft + Vec2{0, - 1}, numCols * itemWidth, itemHeight, '*', displayTitle, true);

        int row = topLeft.y + 2; // Start rendering items below the title
        int col = topLeft.x + 2;

        int itemIndex = 0;
        for (const auto& itemPair : itemList) {
            if (itemIndex >= maxItemCount) {
                break; // Stop rendering if maximum item count is reached
            }

            // Check if we need to move to the next row
            if (col + itemWidth > topLeft.x + numCols * itemWidth) {
                col = topLeft.x + 2; // Reset column position to start a new row
                row += itemHeight + 1; // Move to the next row
            }

            // Get the item name from the item pair
            std::string itemName = itemPair.first;

            // Render the item at the current position
            canvas->drawSquare(Vec2(col, row), itemWidth, itemHeight, '*', itemName, true);

            // Move to the next column position
            col += itemWidth + 1;

            ++itemIndex;
        }
    }

    void Game::registerCommands() {
        GameRenderer::TextCanvas* canvas = this->getCanvas();

        addCommand("shop", [canvas](Game* g) {
            std::cout << "Opening shop..." << std::endl;

            const auto& itemMap = ItemRegistry::getInstance()->getItemMap();

            // Define the dimensions and layout of the item shop display
            Vec2 shopTopLeft(6 , 3);
            int maxWidth = 6; // Maximum items per row
            int itemWidth = 18;
            int itemHeight = 3;
            int maxItemCount = 30; // Maximum items to display

        
            displayItemList(canvas, itemMap, "Item Shop", shopTopLeft, maxWidth, itemWidth, itemHeight, maxItemCount);
            
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