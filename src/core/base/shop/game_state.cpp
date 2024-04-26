
#include "src/core/shop/game_state.h"
#include "src/core/shop/game.h"
#include <sstream>

class InventoryState;
	//GAME STATE
	ShopGame::GameState::GameState(Game* pgame, std::string name) : game(pgame), stateName(name) {

	}

	void ShopGame::GameState::handleInput(ShopGame::Game* game, const std::string& input) {
        auto parsedCommand = Utility::parseCommand(input); // Parse the input command

        std::string commandWord = parsedCommand.first;
        std::vector<std::string> parameters = parsedCommand.second;


        std::cout << "DEBUG Command Word: " + commandWord << std::endl;

        auto it = commandMap.find(commandWord);
        if (it != commandMap.end()) {
            it->second(game, parameters); // Execute the command function with parameters
        }
        else {
            std::cout << "Command not recognized. Try again." << std::endl;
        }
	};

	void ShopGame::GameState::update(Game* game) {

	};

	void ShopGame::GameState::init(Game* game) {
        GameRenderer::TextCanvas* canvas = game->getCanvas();


        game->getCanvas()->drawSquare(Vec2(46, 10), 20, 5, '*', getName(), true);


        int x = 6;
        int y = 5;
        int commandCount = commandMap.size();
      
        canvas->drawSquare(Vec2(x - 2, 2), 28, 3 * commandCount - 3, '*', "", true);


        canvas->drawText(Vec2(x + 3, 3), "Available Commands:");


        for (const auto& commands : commandMap) {

            std::string commandName = commands.first;

            canvas->drawText(Vec2(x + 9, y), commandName);

               y += 2;
        }


     /*
     
     canvas->drawText(Vec2(x, 5), "shop - Open shop");
        canvas->drawText(Vec2(x, 7), "exit - Exit game");
        canvas->drawText(Vec2(x, 9), "clear - Clear canvas");
        canvas->drawText(Vec2(x, 11), "info - Display game info");
        canvas->drawText(Vec2(x, 13), "help - Display help menu");
     
     */
        
	}

	void ShopGame::GameState::addCommand(const std::string& command, const InputFunction consumer) {
		//   commandMap[command] = (consumer);
		commandMap.emplace(command, consumer);
	}

    ShopGame::Game* ShopGame::GameState::getGame() {
        return game;
    }

    std::string ShopGame::GameState::getName() {
        return stateName;
    }

    //GLOBAL COMMANDS(Shared across all gamestates) always call this
	void ShopGame::GameState::initCommands() {
        GameRenderer::TextCanvas* canvas = getGame()->getCanvas();
        addCommand("menu", [this](Game* g, InputParameter& param) {
             GameState* menu = new MenuState(g);

               g->setGameState(menu);
            });
        addCommand("back", [this](Game* g, InputParameter& param) {
            GameState* menu = new MenuState(g);

            if (g->getPreviousState() != nullptr) {
                g->setGameState(g->getPreviousState());
            }
            });
        addCommand("exit", [this](Game* g, InputParameter& param) {
            std::cout << "Closing game..." << std::endl;
            g->getCanvas()->drawSquare(Vec2(46, 10), 20, 5, '*', "Game Closed", true);

            g->setRunning(false); // Set running flag to false to exit the game loop
            });
        addCommand("clear", [canvas](Game* g, InputParameter& param) {
            std::cout << "Clearing canvas..." << std::endl;
            canvas->clear(); // Clear the canvas
            canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Cleared Canvas", true);
            });
	}


	void ShopGame::GameState::render(GameRenderer::TextCanvas* canvas) {

	}

	//MENU STATE

    ShopGame::MenuState::MenuState(Game* game) : ShopGame::GameState(game, "Game Menu") {
        // Update logic for the menu state
    }
	void ShopGame::MenuState::update(Game* game) {
		// Update logic for the menu state
	}
    void ShopGame::MenuState::init(Game* game) {
       GameState::init(game);
    }
	void ShopGame::MenuState::initCommands()  {
        GameState::initCommands();

        GameRenderer::TextCanvas* canvas = getGame()->getCanvas();

        addCommand("shop", [canvas](Game* g, InputParameter param) {
            g->setGameState(new ShopState(g));
         
            });
        addCommand("help", [canvas](Game* g, InputParameter param) {
            canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Help Menu", false);
            canvas->drawSquare(Vec2(48, 12), 16, 3, '*', "Commands:", false);
            canvas->drawSquare(Vec2(50, 14), 12, 3, '*', "shop - Open shop", false);
            canvas->drawSquare(Vec2(50, 16), 12, 3, '*', "exit - Exit game", false);
            canvas->drawSquare(Vec2(50, 18), 12, 3, '*', "clear - Clear canvas", false);
            canvas->drawSquare(Vec2(50, 20), 12, 3, '*', "info - Game info", false);
            canvas->drawSquare(Vec2(50, 22), 12, 3, '*', "help - Display help", false);
            });

        addCommand("info", [canvas](Game* g, InputParameter param) {
            std::cout << "Displaying info..." << std::endl;
            canvas->drawSquare(Vec2(46, 3), 20, 5, '*', "Game Information", true);

            canvas->drawText(Vec2(46, 14), "Version: 1.0");
            canvas->drawText(Vec2(46, 16), "Developer: " + g->getName());

            // Display screen size
            int screenWidth = g->getCanvas()->getWidth();
            int screenHeight = g->getCanvas()->getHeight();
            canvas->drawText(Vec2(46, 18), "Screen Size:");
            canvas->drawText(Vec2(46, 20), "Width: " + std::to_string(screenWidth));
            canvas->drawText(Vec2(46, 22), "Height: " + std::to_string(screenHeight));

            // Display available commands
            int x = 6;
            canvas->drawSquare(Vec2(x - 2, 2), 28, 14, '*', "", true);
            canvas->drawText(Vec2(x, 3), "Commands:");
            canvas->drawText(Vec2(x, 5), "shop - Open shop");
            canvas->drawText(Vec2(x, 7), "exit - Exit game");
            canvas->drawText(Vec2(x, 9), "clear - Clear canvas");
            canvas->drawText(Vec2(x, 11), "info - Display game info");
            canvas->drawText(Vec2(x, 13), "help - Display help menu");
            });
	}


	void ShopGame::MenuState::render(GameRenderer::TextCanvas* canvas) {
		// Render the menu state on the canvas
	}



    //SHOP STATE

    ShopGame::ShopState::ShopState(Game* game) : ShopGame::GameState(game, "Shop Menu") {
        // Update logic for the menu state
    }

    void ShopGame::ShopState::update(Game* game) {
        // Implement update logic for the shop state
    }

    void ShopGame::ShopState::init(Game* game) {
        GameState::init(game);
    }

    void ShopGame::ShopState::render(GameRenderer::TextCanvas* canvas) {
        // Implement rendering logic for the shop state
    }

    void ShopGame::ShopState::initCommands()  {
        GameState::initCommands();

        GameRenderer::TextCanvas* canvas = getGame()->getCanvas();

        addCommand("buy", [canvas](Game* g, InputParameter param) {
            canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Buy Item", true);
            });

        addCommand("inventory", [canvas](Game* g, InputParameter param) {
            g->setGameState(new InventoryState(g));
            });


        addCommand("sell", [canvas](Game* g, InputParameter param) {
            canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Sell Item", true);
            });
        addCommand("show", [canvas](Game* g, InputParameter param) {
            std::cout << "Opening shop..." << std::endl;

            const auto& itemMap = ItemRegistry::getInstance()->getItemMap();

        
            Vec2 shopTopLeft(16, 3);
            int maxWidth = 6; // Maximum items per row
            int itemWidth = 18;
            int itemHeight = 3;
            int maxItemCount = 30; // Maximum items to display

            displayItemList(canvas, itemMap, "Item Shop", shopTopLeft, maxWidth, itemWidth, itemHeight, maxItemCount);
            });


    }
  

