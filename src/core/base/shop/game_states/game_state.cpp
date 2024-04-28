#include "src/core/shop/character.h"
#include "src/core/shop/game_state.h"
#include "src/core/shop/game.h"
#include <sstream>
#include <iomanip> 
#include <iostream>


class InventoryState;
class MenuState;
class ShopState;
class QuitGameState;

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


        std::cout << "[DEBUG] Command Word: " + commandWord << std::endl;

        auto it = commandMap.find(commandWord);
        if (it != commandMap.end()) {
            it->second(game, parameters); // Execute the command function with parameters
        }
        else {
            
            std::cout << "Command not recognized. Try again." << std::endl;
           // game->setGameState(game->getPreviousState());
        }
	};

	void ExolorGame::GameMenu::update(Game* game) {


       
	};

	void ExolorGame::GameMenu::init(Game* game) {
        GameRenderer::TextCanvas* canvas = game->getCanvas();
        
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
        bool commandFlag = false;

        GameRenderer::TextCanvas* canvas = getGame()->getCanvas();
        addCommand("menu", [this](Game* g, InputParameter& param) {
           
             if (g->getCharacter() != nullptr) {
                 GameMenu* menu = new MenuState(g);
                 g->setGameState(menu);
                 handleInput(g, "commands");
             }
               
            });
        addCommand("back", [this](Game* g, InputParameter& param) {
           

            if (g->getPreviousState() != nullptr) {
                g->setGameState(g->getPreviousState());


            }
            });

        addCommand("commands", [canvas, this](Game* g, InputParameter& param) {

            // game->getCanvas()->drawSquare(Vec2(46, 10), 20, 5, '*', getName(), true);
         

            int x = 6;
            int y = 5;
            int commandCount = commandMap.size();

            canvas->drawSquare(Vec2(x - 2, 2), 28, 3 * commandCount - 3, '*', "", true);


            canvas->drawText(Vec2(x + 3, 3), "Available Commands:");

            int txtX = x - 2;

            for (const auto& commands : commandMap) {

                std::string commandName = commands.first;

                int xPos = (28 - static_cast<int>(commandName.length())) / 2;

                canvas->drawText(Vec2(txtX + xPos, y), commandName);

                y += 2;
            }
           
            });
        addCommand("quit", [this](Game* g, InputParameter& param) {
            QuitGameState* menu = new QuitGameState(g);

            g->setGameState(menu);
            delete menu;
            });
        addCommand("clear", [canvas](Game* g, InputParameter& param) {
            std::cout << "Clearing canvas..." << std::endl;
            canvas->clear(); // Clear the canvas
            canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Cleared Canvas", true);
            });
	}


	void ExolorGame::GameMenu::render(GameRenderer::TextCanvas* canvas) {
 
        std::string title = getName();
        int titleX = (canvas->getWidth() - title.length()) / 2;

    
        canvas->drawText(Vec2(titleX, 1), getName()); //draw state title
    
        if (game->getCharacter() != nullptr) { //Only if it has a selected character
            ExolorGame::Character* character = game->getCharacter();

            std::string name = character->getName();
            std::stringstream nameStream; 
            nameStream << "Character: " << name;
            BankAccount* bankAccount = character->getBankAccount();
            // Format the bank balance to display a limited number of decimal places
            std::stringstream balanceStream;
            balanceStream << "Balance: $" << std::fixed << std::setprecision(2) << bankAccount->getBalance();
            std::string description = balanceStream.str();
            int xOffset = 22;
            canvas->drawText(Vec2(((canvas->getWidth() - nameStream.str().length()) / 2) + xOffset + 2, 1), nameStream.str());
            canvas->drawText(Vec2(((canvas->getWidth() - description.length()) / 2) + xOffset + 21, 1), description);
        }
      
        
	}

  

