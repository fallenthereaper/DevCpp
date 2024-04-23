#pragma once

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "src/core/TextCanvas.h"


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

        void update();

        void clean();

        void render();

        const bool isRunning();

        GameRenderer::TextCanvas* getCanvas();



    private:
        bool running;
        GameRenderer::TextCanvas* canvas;
        // Helper method for handling user input
        void handleInput(const std::string& input);

    };

} // namespace ShopGame

#endif // GAME_H