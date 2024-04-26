
#include "src/core/shop/game_state.h"
#include "src/core/shop/game.h"
#include <sstream>

class InventoryState;
class MenuState;
class ShopState;

	//GAME STATE
	ExolorGame::GameState::GameState(Game* pgame, std::string name) : game(pgame), stateName(name) {}

	void ExolorGame::GameState::handleInput(ExolorGame::Game* game, const std::string& input) {
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
            game->setGameState(game->getPreviousState());
        }
	};

	void ExolorGame::GameState::update(Game* game) {

	};

	void ExolorGame::GameState::init(Game* game) {
        GameRenderer::TextCanvas* canvas = game->getCanvas();


       // game->getCanvas()->drawSquare(Vec2(46, 10), 20, 5, '*', getName(), true);
        canvas->drawText(Vec2(50, 1), getName()); //draw state title

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
        
	}

	void ExolorGame::GameState::addCommand(const std::string& command, const InputFunction consumer) {
		commandMap.emplace(command, consumer);
	}

    ExolorGame::Game* ExolorGame::GameState::getGame() {
        return game;
    }

    std::string ExolorGame::GameState::getName() {
        return stateName;
    }

    //GLOBAL COMMANDS(Shared across all gamestates) always call this
	void ExolorGame::GameState::initCommands() {
        GameRenderer::TextCanvas* canvas = getGame()->getCanvas();
        addCommand("menu", [this](Game* g, InputParameter& param) {
             GameState* menu = new MenuState(g);

               g->setGameState(menu);
            });
        addCommand("back", [this](Game* g, InputParameter& param) {
           

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


	void ExolorGame::GameState::render(GameRenderer::TextCanvas* canvas) {

	}

  

