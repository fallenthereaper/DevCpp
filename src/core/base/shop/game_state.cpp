
#include "src/core/shop/game_state.h"

	//GAME STATE
	ShopGame::GameState::GameState(Game* game) {
		init(game);
	}

	void ShopGame::GameState::handleInput(Game* game, const std::string& input) {
		auto it = commandMap.find(input);
		if (it != commandMap.end()) {
			// Execute the consumer associated with the input command
			it->second(game); // Pass 'this' pointer to the Game object
		}
		else {
			game->getCanvas()->drawSquare(Vec2(38, 10), 38, 5, '*', "Command not recognized. Try again.", true);
		}
	};

	void ShopGame::GameState::update(Game* game) {

	};

	void ShopGame::GameState::init(Game* game) {
		registerCommands();
	}

	void ShopGame::GameState::addCommand(const std::string& command, const std::function<void(Game*)> consumer) {
		//   commandMap[command] = (consumer);
		commandMap.emplace(command, consumer);
	}

    ShopGame::Game* ShopGame::GameState::getGame() {
        return game;
    }


	void ShopGame::GameState::registerCommands() {
        addCommand("menu", [this](Game* g) {
             GameState* menu = new MenuState(g);

           //  g->setGameState(menu);
            });
	}


	void ShopGame::GameState::render(GameRenderer::TextCanvas* canvas) {

	}



	//MENU STATE

	void ShopGame::MenuState::update(ShopGame::Game* game) {
		// Update logic for the menu state
	}

	void ShopGame::MenuState::registerCommands()  {
        GameState::registerCommands();

        GameRenderer::TextCanvas* canvas = getGame()->getCanvas();

        addCommand("shop", [canvas](Game* g) {
            std::cout << "Opening shop..." << std::endl;

            const auto& itemMap = ItemRegistry::getInstance()->getItemMap();

            // Define the dimensions and layout of the item shop display
            Vec2 shopTopLeft(16, 3);
            int maxWidth = 6; // Maximum items per row
            int itemWidth = 18;
            int itemHeight = 3;
            int maxItemCount = 30; // Maximum items to display

            displayItemList(canvas, itemMap, "Item Shop", shopTopLeft, maxWidth, itemWidth, itemHeight, maxItemCount);
            });

        addCommand("exit", [canvas](Game* g) {
            std::cout << "Closing game..." << std::endl;
            canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Game Closed", true);

            g->setRunning(false); // Set running flag to false to exit the game loop
            });

        addCommand("clear", [canvas](Game* g) {
            std::cout << "Clearing canvas..." << std::endl;
            canvas->clear(); // Clear the canvas
            canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Cleared Canvas", true);
            });

        addCommand("help", [canvas](Game* g) {
            canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Help Menu", false);
            canvas->drawSquare(Vec2(48, 12), 16, 3, '*', "Commands:", false);
            canvas->drawSquare(Vec2(50, 14), 12, 3, '*', "shop - Open shop", false);
            canvas->drawSquare(Vec2(50, 16), 12, 3, '*', "exit - Exit game", false);
            canvas->drawSquare(Vec2(50, 18), 12, 3, '*', "clear - Clear canvas", false);
            canvas->drawSquare(Vec2(50, 20), 12, 3, '*', "info - Game info", false);
            canvas->drawSquare(Vec2(50, 22), 12, 3, '*', "help - Display help", false);
            });

        addCommand("info", [canvas](Game* g) {
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
            canvas->drawText(Vec2(x, 3), "Available Commands:");
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

