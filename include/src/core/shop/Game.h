#pragma once
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <unordered_map>
#include <functional>
#include "src/core/text_canvas.h"
#include "src/core/shop/registry/item_registry.h"
#include "src/core/shop/game_state.h"



namespace ShopGame {

    class Game {
    public:
        Game();
        ~Game();
        Game(int canvasWidth, int canvasHeight, std::string gameName);
        void start();
        void update(GameRenderer::TextCanvas* canvas);
        void clean();
        void render();
        const bool isRunning();
        void setRunning(bool val);
        GameRenderer::TextCanvas* getCanvas();
        void addCommand(const std::string& command, const std::function<void(Game*)> function);
        void processInput(const std::string& input);
        std::string getName();
        void setGameState(GameState* state);
        GameState* getGameState();
        GameState* getPreviousState();

    private:
        GameState* prevState;
        GameState* currentState;
        bool running;
        std::string gameName;
        GameRenderer::TextCanvas* canvas;
        std::unordered_map<std::string, std::function<void(Game*)>> commandMap;
        void handleInput(const std::string& input);
        void registerCommands();

        friend void displayItemList(GameRenderer::TextCanvas* canvas, const std::unordered_map<std::string, ItemRegistry::ItemFactory>& itemList, const std::string& displayTitle, const Vec2& topLeft, int maxWidth, int itemWidth, int itemHeight, int maxItemCount);
    };

} // namespace ShopGame

#endif