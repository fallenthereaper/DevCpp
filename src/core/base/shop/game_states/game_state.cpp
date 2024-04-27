#include "src/core/shop/character.h"
#include "src/core/shop/game_state.h"
#include "src/core/shop/game.h"
#include <sstream>
#include <iomanip> 
#include <iostream>
class InventoryState;
class MenuState;
class ShopState;

	//GAME STATE
	ExolorGame::GameMenu::GameMenu(Game* pgame, std::string name) : game(pgame), stateName(name) {}


    void ExolorGame::GameMenu::nextPage() {
        if (currentPage < totalPages) {
            currentPage++;
        
        }
        else {
            std::cout << "No next page available.\n";
        }
    }

    void ExolorGame::GameMenu::prevPage() {
        if (currentPage > 1) {
            currentPage--;
          
        }
        else {
            std::cout << "No previous page available.\n";
        }
    }

    void ExolorGame::GameMenu::setCurrentPage(int page) {
        if (page >= 1 && page <= totalPages) {
            currentPage = page;
      
        }
        else {
            std::cout << "Invalid page number.\n";
        }
    }

	void ExolorGame::GameMenu::handleInput(ExolorGame::Game* game, const std::string& input) {
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

	void ExolorGame::GameMenu::update(Game* game) {

	};

	void ExolorGame::GameMenu::init(Game* game) {
        GameRenderer::TextCanvas* canvas = game->getCanvas();

        if (game->getCharacter()) { //Only if it has a selected character
            ExolorGame::Character* character = game->getCharacter();

            std::string name = character->getName();
            BankAccount* bankAccount = character->getBankAccount();
            // Format the bank balance to display a limited number of decimal places
            std::stringstream balanceStream;
            balanceStream << "Balance: $" << std::fixed << std::setprecision(2) << bankAccount->getBalance();
            std::string description = balanceStream.str();
            canvas->drawText(Vec2(99, 2), name);
            canvas->drawText(Vec2(70, 8), description);
        }


       // game->getCanvas()->drawSquare(Vec2(46, 10), 20, 5, '*', getName(), true);
        canvas->drawText(Vec2(50, 1), getName()); //draw state title

        int x = 6;
        int y = 5;
        int commandCount = commandMap.size();
      
        canvas->drawSquare(Vec2(x - 2, 2), 28, 3 * commandCount - 3, '*', "", true);


        canvas->drawText(Vec2(x + 3, 3), "Available Commands:");

        int txtX = x - 2;

        for (const auto& commands : commandMap) {

            std::string commandName = commands.first;

            int xPos = (28 - static_cast<int>(commandName.length())) / 2;

            canvas->drawText(Vec2(txtX + xPos , y), commandName);

               y += 2;
        }
        
	}

	void ExolorGame::GameMenu::addCommand(const std::string& command, const InputFunction consumer) {
		commandMap.emplace(command, consumer);
	}

    ExolorGame::Game* ExolorGame::GameMenu::getGame() {
        return game;
    }

    std::string ExolorGame::GameMenu::getName() {
        return stateName;
    }

    //GLOBAL COMMANDS(Shared across all gamestates) always call this
	void ExolorGame::GameMenu::initCommands() {
        GameRenderer::TextCanvas* canvas = getGame()->getCanvas();
        addCommand("menu", [this](Game* g, InputParameter& param) {
             GameMenu* menu = new MenuState(g);

               g->setGameState(menu);
            });
        addCommand("back", [this](Game* g, InputParameter& param) {
           

            if (g->getPreviousState() != nullptr) {
                g->setGameState(g->getPreviousState());
            }
            });
        addCommand("exit", [this](Game* g, InputParameter& param) {
            Blaze2D::GameEngine::getInstance()->quit();

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


	void ExolorGame::GameMenu::render(GameRenderer::TextCanvas* canvas) {

	}

  

