#pragma once

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <unordered_map>
#include <functional>
#include "src/core/utils/utility.h"
#include "src/core/text_canvas.h"



namespace ShopGame {

    class Game;
    class Inventory;

    class GameState {
   

    public:
        GameState(ShopGame::Game* game, std::string name);
        ~GameState() = default;
        void handleInput(Game* game, const std::string& input);
        virtual void update(ShopGame::Game* game) = 0;
        virtual void registerCommands() = 0;
        void init(ShopGame::Game* game);
        void addCommand(const std::string& command, const std::function<void(ShopGame::Game*)> function);
        ShopGame::Game* getGame();
        std::string getName();
        virtual void render(GameRenderer::TextCanvas* canvas) = 0;

        private:
         std::string stateName;
         ShopGame::Game* game;
         std::unordered_map<std::string, std::function<void(ShopGame::Game*)>> commandMap;
    };

    class MenuState : public GameState {
    public:
        MenuState(Game* game);
        void registerCommands() override;
        void update(Game* game) override;
        void init(Game* game);
        void render(GameRenderer::TextCanvas* canvas) override;
    };

    class ShopState : public GameState {
    public:
        ShopState(Game* game);
        void registerCommands() override;
        void update(Game* game) override;
        void init(Game* game);
        void render(GameRenderer::TextCanvas* canvas) override;
    };

    class InventoryState : public GameState {
    private:
        Inventory* inventory;
    public:
        InventoryState(Game* game);
        void registerCommands() override;
        void update(Game* game) override;
        void init(Game* game);
        void render(GameRenderer::TextCanvas* canvas) override;
        Inventory* getInventory();
    };

} // namespace ShopGam

#endif