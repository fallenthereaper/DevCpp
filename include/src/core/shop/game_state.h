#pragma once

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <unordered_map>
#include <functional>
#include "game.h"  // Include the necessary header
class Game;

namespace ShopGame {

    class GameState {
   

    public:
        GameState(Game* game);
        virtual ~GameState() = default;
        void handleInput(Game* game, const std::string& input);
        virtual void update(Game* game) = 0;
        virtual void registerCommands() = 0;
        void init(Game* game);
        void addCommand(const std::string& command, const std::function<void(Game*)> function);
        Game* getGame();
        virtual void render(GameRenderer::TextCanvas* canvas) = 0;

        private:
        Game* game;
        std::unordered_map<std::string, std::function<void(Game*)>> commandMap;
    };

    class MenuState : public GameState {
    public:
        MenuState(Game* game) : GameState(game) {}
        void registerCommands() override;
        void update(Game* game) override;
        void render(GameRenderer::TextCanvas* canvas) override;
    };

} // namespace ShopGam

#endif