#pragma once

#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <conio.h>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <functional>
#include "src/core/utils/utility.h"
#include "src/core/text_canvas.h"



namespace ExolorGame {

    class Game;
    class Inventory;

    using InputParameter = std::vector<std::string>&;

    using InputFunction = std::function<void(Game*, const InputParameter&)>;

    using InputMap = std::unordered_map<std::string, InputFunction>;

    class GameState {
   

    public:
        GameState(ExolorGame::Game* game, std::string name);
        ~GameState() = default;
        void handleInput(Game* game, const std::string& input);
        virtual void update(ExolorGame::Game* game) = 0;
        virtual void initCommands() = 0;
        void init(ExolorGame::Game* game);
        void addCommand(const std::string& command, const InputFunction function);
        ExolorGame::Game* getGame();
        std::string getName();
        virtual void render(GameRenderer::TextCanvas* canvas) = 0;
        void nextPage();
        void prevPage();
        void setCurrentPage(int page);

    protected:
        int currentPage;
        int totalPages;

        private:
         std::string stateName;
         ExolorGame::Game* game;
         InputMap commandMap; //FOR PARAMETERS
    };

    class MenuState : public GameState {
    public:
        MenuState(Game* game);
        void initCommands() override;
        void update(Game* game) override;
        void init(Game* game);
        void render(GameRenderer::TextCanvas* canvas) override;
    };

    class ShopState : public GameState {
    public:
        ShopState(Game* game);
        void initCommands() override;
        void update(Game* game) override;
        void init(Game* game);
        void render(GameRenderer::TextCanvas* canvas) override;
    };

    class InventoryState : public GameState {
    private:
        Inventory* inventory;
    public:
        InventoryState(Game* game);
        void initCommands() override;
        void update(Game* game) override;
        void init(Game* game);
        void render(GameRenderer::TextCanvas* canvas) override;
        Inventory* getInventory();
    };

    class SelectedItemState : public GameState {
    private:
        InventoryState* parentState;
    public:
        SelectedItemState(InventoryState* parentState);
        void initCommands() override;
        void update(Game* game) override;
        void init(Game* game);
        void render(GameRenderer::TextCanvas* canvas) override;
      
    };

    class Character;

    class CharacterSelectState : public GameState {
    protected:
        std::vector<std::shared_ptr<Character>> characters;
        int selectedCharacterIndex; // Index of currently selected character
    public:
        CharacterSelectState(Game* game);
        void initCommands() override;
        void update(Game* game) override;
        void init(Game* game);
        void render(GameRenderer::TextCanvas* canvas) override;
        void selectCharacter(int index);
        void addCharacter(const Character& character);

    };

} // namespace ShopGam

#endif