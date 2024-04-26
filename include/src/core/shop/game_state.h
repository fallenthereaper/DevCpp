#pragma once

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
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

} // namespace ShopGam

#endif