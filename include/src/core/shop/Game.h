#pragma once

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "src/core/text_canvas.h"
#include "src/core/utils/utility.h"
#include "src/core/shop/registry/item_registry.h"
class ItemRegistry;
class GameState;

namespace ShopGame {

    // Game class representing the main game logic
    class Game {
    public:
        // Constructor
        Game();

        // Destructor
        ~Game();

        Game(int canvasWidth, int canvasHeight, std::string gameName);

        // Method to start the game
        void start();

        void update(GameRenderer::TextCanvas* canvas);

        void clean();

        void render();

        friend void displayItemList(GameRenderer::TextCanvas* canvas, const std::unordered_map<std::string, ItemRegistry::ItemFactory>& itemList, const std::string& displayTitle, const Vec2& topLeft, int maxWidth, int itemWidth, int itemHeight, int maxItemCount);

        const bool isRunning();

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
        // Helper method for handling user input
        void handleInput(const std::string& input);
        void registerCommands();

    };

} // namespace ShopGame

#endif // GAME_H