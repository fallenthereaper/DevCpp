#pragma once
#include "src/core/shop/game_state.h"
#include "src/core/shop/game.h"
#include "src/core/shop/character.h" // Assuming a simple Character class exists
#include <iomanip> // Include for std::setprecision and std::fixed
#include <vector>
#include <iostream>



    ExolorGame::CharacterSelectState::CharacterSelectState(Game* game) : ExolorGame::GameMenu(game, "Character Selection Menu"), selectedCharacterIndex(0), characters(game->getCharacters()) {

        totalPages = (characters.size() + 2) / 3;
        }


    int findIndex(const std::vector<std::string>& vec, const std::string& target) {
        auto it = std::find(vec.begin(), vec.end(), target);
        if (it != vec.end()) {
            return std::distance(vec.begin(), it); // Calculate the index
        }
        return -1; // String not found
    }

    void ExolorGame::CharacterSelectState::init(Game* g) {
       // ExolorGame::GameState::init(g);
        g->getCanvas()->drawText(Vec2(50, 1), getName());
    }

        void ExolorGame::CharacterSelectState::initCommands()  {
            ExolorGame::GameMenu::initCommands();
            addCommand("next", [this](Game* game, const InputParameter& param) {
                nextPage();
                });

            addCommand("prev", [this](Game* game, const InputParameter& param) {
                prevPage();
                });

            addCommand("select", [this](Game* game, const InputParameter& param) {
                if (param.size() == 1) {
         
                    int index = findIndex(param, param[0]);
               
                    selectCharacter(index);
                    game->setGameState(new MenuState(game));
                }
                });
        }

        void ExolorGame::CharacterSelectState::update(Game* game)  {
            GameRenderer::TextCanvas* canvas = game->getCanvas();

       

            int start = (currentPage - 1) * 3;
            int end = std::min(start + 3, static_cast<int>(characters.size()));

            int startX = 10;
            int yPos = 10;
            float boxWidth = 30.0f;


            for (int i = 0; i < 3; ++i) {
                // Calculate the x-coordinate for the current character
                float xPos = startX + i * (boxWidth + 2.0f); // Adjust the spacing between characters

                // Draw a box for the character
                canvas->drawSquare(Vec2(xPos, yPos), 30.0f, 10.0f, '*', "", true);

                // Get the character's name and description
                std::string name = characters[i]->getName();
                BankAccount* bankAccount = characters[i]->getBankAccount();
                // Format the bank balance to display a limited number of decimal places
                std::stringstream balanceStream;
                balanceStream << "Bank Balance: $" << std::fixed << std::setprecision(2) << bankAccount->getBalance();
                std::string description = balanceStream.str();

                

                // Calculate the position to center the text within the box
                float textX = xPos + (30.0f - name.length()) / 2.0f; // Center horizontally
                float textY = yPos + 3.0f; // Position vertically within the box

                // Draw the character's name
                canvas->drawText(Vec2( textX, textY ), name);

                // Draw the character's description
                canvas->drawText(Vec2(xPos + 2.0f, yPos + 6.0f ), description);

            }
        }

        void ExolorGame::CharacterSelectState::render(GameRenderer::TextCanvas* canvas)  {
     
  
        }

        void ExolorGame::CharacterSelectState::selectCharacter(int index) {
            if (index >= 0 && index < characters.size()) {
                selectedCharacterIndex = index;
                std::cout << "Character " << characters[index]->getName() << " selected." << std::endl;
                getGame()->setCharacter(characters[index]);
            }
            else {
                std::cout << "Invalid character index." << std::endl;
            }
        }

        void ExolorGame::CharacterSelectState::addCharacter(const Character& character) {
        
        }

