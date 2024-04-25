#pragma once

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <unordered_map>
#include <functional>
#include "src/core/shop/game.h"  // Include the necessary header

namespace ShopGame {

    class GameState {
   

    public:
        GameState(ShopGame::Game* game);
        virtual ~GameState() = default;
        void handleInput(ShopGame::Game* game, const std::string& input);
        virtual void update(ShopGame::Game* game) = 0;
        virtual void registerCommands() = 0;
        void init(ShopGame::Game* game);
        void addCommand(const std::string& command, const std::function<void(ShopGame::Game*)> function);
        ShopGame::Game* getGame();
        virtual void render(GameRenderer::TextCanvas* canvas) = 0;

        private:
        ShopGame::Game* game;
        std::unordered_map<std::string, std::function<void(ShopGame::Game*)>> commandMap;
    };

    class MenuState : public GameState {
    public:
        MenuState(ShopGame::Game* game) : GameState(game) {}
        void registerCommands() override;
        void update(ShopGame::Game* game) override;
        void render(GameRenderer::TextCanvas* canvas) override;
    };

} // namespace ShopGam

#endif