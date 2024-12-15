#include "src/core/shop/game.h"
#include "src/core/shop/game_state.h"
#include "src/core/shop/character.h"
#include <cmath>


class BankAccount;

ExolorGame::Game::Game() : running(true), gameName("Default"), canvas(new GameRenderer::TextCanvas(0, 0)),
                           currentState(nullptr), prevState(nullptr) {
    initCharacters();
    registerCommands();
}

ExolorGame::Game::Game(int canvasWidth, int canvasHeight, std::string name) : canvas(
        new GameRenderer::TextCanvas(canvasWidth, canvasHeight)), running(true), gameName(name), currentState(nullptr),
                                                                              prevState(nullptr), character(nullptr) {
    initCharacters();
    registerCommands();
}

// Destructor
ExolorGame::Game::~Game() {

}

void ExolorGame::Game::addCommand(const std::string &command, const std::function<void(Game *)> consumer) {
    //   commandMap[command] = (consumer);
    commandMap.emplace(command, consumer);
}

std::string ExolorGame::Game::getName() {
    return gameName;
}

 void ExolorGame::displayItemList(GameRenderer::TextCanvas *canvas,
                                 const std::unordered_map<std::string, ItemRegistry::ItemFactory> &itemList,
                                 const std::string &displayTitle, const Vec2 &topLeft, int maxWidth, int itemWidth,
                                 int itemHeight, int maxItemCount) {
    int itemCount = std::min(static_cast<int>(itemList.size()), maxItemCount);

    // Calculate the number of rows needed based on the item count
    int numRows = (itemCount + (maxWidth - 1)) / maxWidth;
    int numCols = (itemCount + numRows - 1) / numRows;

    // Draw the title of the item list
    canvas->drawSquare(topLeft + Vec2{2, -1}, itemWidth * numRows + 3, itemHeight, '*', displayTitle, true);

    int row = topLeft.y + 2; // Start rendering items below the title
    int col = topLeft.x + 2;

    int itemIndex = 0;
    for (const auto &itemPair: itemList) {
        if (itemIndex >= maxItemCount) {
            break; // Stop rendering if maximum item count is reached
        }

        // Check if we need to move to the next row
        if (col + itemWidth > topLeft.x + numCols * itemWidth) {
            col = topLeft.x + 2; // Reset column position to start a new row
            row += itemHeight; // Move to the next row
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


void ExolorGame::renderItems(GameRenderer::TextCanvas *canvas,
                             const std::vector<ItemStack *> &itemList,
                             const std::string &displayTitle,
                             const Vec2 &topLeft,
                             int maxWidth,
                             int itemWidth,
                             int itemHeight,
                             int maxItemCount) {
    // Limit the number of items to render based on the maximum allowed
    int itemCount = std::min(static_cast<int>(itemList.size()), maxItemCount);

    // Determine the number of rows and columns needed
    int numCols = std::min(maxWidth, itemCount); // Columns are limited by maxWidth or the total number of items
    int numRows = (itemCount + numCols - 1) / numCols; // Calculate rows using ceiling logic

    // Draw the title of the item list (optional, commented out for now)
    // canvas->drawSquare(topLeft + Vec2{2, -1}, numCols * itemWidth + 3, itemHeight, '*', displayTitle, true);

    // Initial rendering position starts below the title
    int row = topLeft.y + 2; // Vertical offset for the first row
    int col = topLeft.x + 2; // Horizontal offset for the first column

    // Iterate over each item to render
    for (int itemIndex = 0; itemIndex < itemCount; ++itemIndex) {
        // Check if we've reached the column limit and need to move to the next row
        if (col + itemWidth > topLeft.x + numCols * itemWidth) {
            col = topLeft.x + 2;  // Reset to the first column
            row += itemHeight;    // Move down to the next row
        }

        // Get the current item stack (can be nullptr for empty slots)
        ItemStack *itemStack = itemList[itemIndex];

        // Render an empty item slot at the current position
        canvas->drawSquare(Vec2(col, row), itemWidth, itemHeight, '*', "", true);

        // If the slot contains an item, display its name and count
        if (itemStack != nullptr) {
            std::string itemName = itemStack->getItem()->getName(); // Get item name
            int stackCount = itemStack->getCount();                 // Get item count

            // Create display string for the item slot (e.g., "ItemName x10")
            std::string itemDisplay = itemName + " x" + std::to_string(stackCount);

            // Render the item details inside the slot
            canvas->drawSquare(Vec2(col, row), itemWidth, itemHeight, '*', itemDisplay, true);
        }

        // Move to the next column position for the next item
        col += itemWidth + 1; // Add 1 for spacing between slots
    }
}

void ExolorGame::Game::registerCommands() {
    GameRenderer::TextCanvas *canvas = this->getCanvas();


    if (getCharacter() == nullptr) { //Horrendous logic but will do for now
        addCommand("start", [this, canvas](Game *g) {
            if (getCharacter() == nullptr) {
                //     std::cout << "Starting game..." << std::endl;
                canvas->drawSquare(Vec2(0, 0), 112, 28, '*', "", true);
                g->setGameState(new CharacterSelectState(g));
                std::cout << "[Game Started]" << std::endl;
            }
        });

    }


}


// Method to process input and trigger associated consumers
void ExolorGame::Game::processInput(const std::string &input) {


    auto it = commandMap.find(input);
    if (it != commandMap.end()) {
        it->second(this);
    } else {
        if (currentState) {
            currentState->handleInput(this, input);
        } else {
            std::cout << "Command not recognized. Try again." << std::endl;
        }
    }
}

void ExolorGame::Game::update(GameRenderer::TextCanvas *canvas) {

    std::string input;
    std::cout << "Enter a command: ";
    std::cin >> input;


    processInput(input);

    if (currentState) {
        currentState->render(canvas);
        currentState->update(this);
    }


}


void ExolorGame::Game::clean() {
}

void ExolorGame::Game::render() {
    canvas->drawSquare(Vec2(0, 0), 112, 28, '*', "", true);
    if (currentState) {

        currentState->render(canvas);
        // Render the canvas after updating its content
    }
    canvas->render();
}

const bool ExolorGame::Game::isRunning() {

    return this->running;
}

void ExolorGame::Game::setRunning(bool val) {

    this->running = val;

}

GameRenderer::TextCanvas *ExolorGame::Game::getCanvas() {

    return canvas;
}

void ExolorGame::Game::setGameState(GameMenu *state) {
    prevState = currentState;

    if (!state) {
        return;
    }


    if (currentState != state) {
        currentState = state;
        std::cout << "Switching GameState.. " << state->getName() << std::endl;
        currentState->initCommands(); // Register commands for the new state
        currentState->init(this); // Initialize the new state
    }
}


void ExolorGame::Game::setCharacter(ExolorGame::Character *character) {

    this->character = character;
}

void ExolorGame::Game::addCharacter(ExolorGame::Character *character) {

    characters.push_back(character);


}

void ExolorGame::Game::initCharacters() {
    addCharacter(new Character("Main", 5000, 0));
    addCharacter(new Character("Villain", 6500, 1));
    addCharacter(new Character("Mentor", 50000, 3));
    addCharacter(new Character("Sidekick", 4500, 2));


}

ExolorGame::Character *ExolorGame::Game::getCharacter() {

    return character;
}


ExolorGame::GameMenu *ExolorGame::Game::getGameState() {
    return currentState;
}

ExolorGame::GameMenu *ExolorGame::Game::getPreviousState() {
    return prevState;
}

// Method to start the game
void ExolorGame::Game::start() {
    //   std::cout << "[Game Started]" << std::endl;
    std::cout << "Type 'start' to start the game." << std::endl;
    //  canvas->drawText({ 0, 0 }, "Type 'start' to start the game.");

    //  std::cout << "Type 'exit' to quit the game." << std::endl;
}


// Helper method for handling user input
void ExolorGame::Game::handleInput(const std::string &input) {


}