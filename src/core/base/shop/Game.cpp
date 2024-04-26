#include "src/core/shop/game.h"
#include "src/core/shop/game_state.h"
class MenuState;


   ShopGame::Game::Game() : running(true), gameName("Default"), canvas(new GameRenderer::TextCanvas(0, 0)), currentState(nullptr), prevState(nullptr) {
        registerCommands();
    }

    ShopGame::Game::Game(int canvasWidth, int canvasHeight, std::string name) : canvas(new GameRenderer::TextCanvas(canvasWidth, canvasHeight)), running(true), gameName(name), currentState(nullptr),  prevState(nullptr) {
    
        registerCommands();
    }

    // Destructor
    ShopGame::Game::~Game() {
        registerCommands();
    }

    void ShopGame::Game::addCommand(const std::string& command, const std::function<void(Game*)> consumer) {
     //   commandMap[command] = (consumer);
        commandMap.emplace(command, consumer);
    }

    std::string ShopGame::Game::getName() {
        return gameName;
    }

    void ShopGame::displayItemList(GameRenderer::TextCanvas* canvas, const std::unordered_map<std::string, ItemRegistry::ItemFactory>& itemList, const std::string& displayTitle, const Vec2& topLeft, int maxWidth, int itemWidth, int itemHeight, int maxItemCount) {
        int itemCount = std::min(static_cast<int>(itemList.size()), maxItemCount);

        // Calculate the number of rows needed based on the item count
        int numRows = (itemCount + (maxWidth - 1)) / maxWidth;
        int numCols = (itemCount + numRows - 1) / numRows;

        // Draw the title of the item list
        canvas->drawSquare(topLeft + Vec2{2, - 1},  itemWidth * numRows + 3 , itemHeight, '*', displayTitle, true);

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
                row += itemHeight ; // Move to the next row
            }

            // Get the item name from the item pair
            std::string itemName = itemPair.first;

            // Render the item at the current position
            canvas->drawSquare(Vec2(col, row + 1), itemWidth, itemHeight, '*', itemName, true);

            // Move to the next column position
            col += itemWidth + 1;

            ++itemIndex;
        }
    }

    void ShopGame::Game::registerCommands() {
        GameRenderer::TextCanvas* canvas = this->getCanvas();

      
   
       
        addCommand("start", [canvas](Game* g) {
       //     std::cout << "Starting game..." << std::endl;
           canvas->drawSquare(Vec2(0, 0), 112, 28, '*', "", true);
            g->setGameState(new MenuState(g));
            std::cout << "[Game Started]" << std::endl;
            });

        
    }

    // Method to process input and trigger associated consumers
    void ShopGame::Game::processInput(const std::string& input) {
        auto it = commandMap.find(input);
        if (it != commandMap.end()) {
            it->second(this);
        }
        else {
            if (currentState) {
               currentState->handleInput(this, input);
            }
            else {
                std::cout << "Command not recognized. Try again." << std::endl;
            }
        }
    }

    void ShopGame::Game::update(GameRenderer::TextCanvas* canvas) {
        canvas->drawSquare(Vec2(0, 0), 112, 28, '*', "", true);
        std::string input;
        std::cout << "Enter a command: ";
        std::cin >> input;
       
        processInput(input);
    }


    void ShopGame::Game::clean() {
    }

    void ShopGame::Game::render() {
        if (currentState) {
       
            currentState->render(canvas);
            canvas->render(); // Render the canvas after updating its content
        }
    }

    const bool ShopGame::Game::isRunning() {

        return this->running;
    }

     void ShopGame::Game::setRunning(bool val) {
      
        this->running = val;
        
    }

    GameRenderer::TextCanvas* ShopGame::Game::getCanvas() {

        return canvas;
    }

    void ShopGame::Game::setGameState(GameState* state) {
        prevState = currentState;

       
        std::cout << "Switching GameState.. " << state->getName() << std::endl;
        currentState = state;

        if (currentState != nullptr) {
            currentState->initCommands(); // Register commands for the new state
            currentState->init(this); // Initialize the new state
           
        }
    }

    ShopGame::GameState* ShopGame::Game::getGameState() {
        return currentState;
    }

    ShopGame::GameState* ShopGame::Game::getPreviousState() {
        return prevState;
    }

    // Method to start the game
    void ShopGame::Game::start() {
    //   std::cout << "[Game Started]" << std::endl;
        std::cout << "Type 'start' to start the game." << std::endl;
        //  std::cout << "Type 'exit' to quit the game." << std::endl;
    }


    // Helper method for handling user input
    void ShopGame::Game::handleInput(const std::string& input) {


       
     
    }
