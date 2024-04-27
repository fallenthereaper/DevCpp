#pragma once
#include "src/core/shop/game_state.h"
#include "src/core/shop/game.h"
#include "src/core/shop/character.h" // Assuming a simple Character class exists

#include <vector>
#include <iostream>

    ExolorGame::CharacterSelectState::CharacterSelectState(Game* game) : ExolorGame::GameState(game, "Character Selection Menu"), selectedCharacterIndex(0) {
        this->characters = game->getCharacters();
        totalPages = (characters.size() + 2) / 3;
        }

    void ExolorGame::CharacterSelectState::init(Game* g) {
        ExolorGame::GameState::init(g);
    }

        void ExolorGame::CharacterSelectState::initCommands()  {
            ExolorGame::GameState::initCommands();
            addCommand("next", [this](Game* game, const InputParameter& param) {
                nextPage();
                });

            addCommand("prev", [this](Game* game, const InputParameter& param) {
                prevPage();
                });

            addCommand("select", [this](Game* game, const InputParameter& param) {
                if (param.size() == 1) {
                    int index = std::stoi(param[0]);
                    selectCharacter(index);
                }
                });
        }

        void ExolorGame::CharacterSelectState::update(Game* game)  {
            // Logic to update game state if necessary
        }

        void ExolorGame::CharacterSelectState::render(GameRenderer::TextCanvas* canvas)  {
            canvas->clear();
            int start = (currentPage - 1) * 3;
            int end = std::min(start + 3, static_cast<int>(characters.size()));
            for (int i = start; i < end; ++i) {
                // Explicitly cast integers to float if the drawSquare method expects floats
                canvas->drawSquare({ 10.0f, static_cast<float>(4 + i * 10) }, 30, 10, '*', "", true);
                canvas->drawText({ 15.0f, static_cast<float>(7 + i * 10) }, characters[i]->getName());
            }
        }

        void ExolorGame::CharacterSelectState::selectCharacter(int index) {
            if (index >= 0 && index < characters.size()) {
                selectedCharacterIndex = index;
                std::cout << "Character " << characters[index]->getName() << " selected." << std::endl;
                getGame()->setCharacter(std::make_shared<Character>(characters[index]));
            }
            else {
                std::cout << "Invalid character index." << std::endl;
            }
        }

        void ExolorGame::CharacterSelectState::addCharacter(const Character& character) {
        
        }

