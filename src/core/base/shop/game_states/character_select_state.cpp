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

    template<class T>
    int findIndex(const std::vector<T>& vec, std::function<bool(T)> pred) {
        for (size_t i = 0; i < vec.size(); ++i) {
            if (pred(vec[i])) {
                return i; // Return the index if the element is found
            }
        }
        return -1; // Return -1 if the element is not found
    }

    void ExolorGame::CharacterSelectState::init(Game* g) {
         ExolorGame::GameMenu::init(g);
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
                    auto pred = [=](Character* c) -> bool {
                        return c->getName() == param[0];
                        };
         
                    int index = findIndex<Character*>(characters, pred);

                    selectCharacter(index);
                    game->setGameState(new MenuState(game));
                }
                });
        }

        void ExolorGame::CharacterSelectState::update(Game* game)  {
            GameMenu::update(game);
        }

        void ExolorGame::CharacterSelectState::render(GameRenderer::TextCanvas* canvas)  {
     
            GameMenu::render(canvas);

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
                canvas->drawText(Vec2(textX, textY), name);

                // Draw the character's description
                canvas->drawText(Vec2(xPos + 2.0f, yPos + 6.0f), description);

            }
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

