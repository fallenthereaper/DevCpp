#pragma once

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "src/core/text_canvas.h"
#include "src/core/utils/utility.h"

namespace ShopGame {

    // Game class representing the main game logic
    class Game {
    public:
        // Constructor
        Game();

        // Destructor
        ~Game();

        Game(int canvasWidth, int canvasHeight);

        // Method to start the game
        void start();

        void update(GameRenderer::TextCanvas* canvas);

        void clean();

        void render();

        const bool isRunning();

        GameRenderer::TextCanvas* getCanvas();

        void addCommand(const std::string& command, const std::function<void(Game*)> function);

        void processInput(const std::string& input);


    private:
         bool running;
         GameRenderer::TextCanvas* canvas;
         std::unordered_map<std::string, std::function<void(Game*)>> commandMap;
        // Helper method for handling user input
        void handleInput(const std::string& input);
        void registerCommands();

    };

} // namespace ShopGame

#endif // GAME_H