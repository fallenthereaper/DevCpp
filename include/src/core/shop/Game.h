#pragma once

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "src/core/text_canvas.h"


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

        std::vector<Utility::Consumer<Game*>> getGameStates() const;

        Utility::Consumer<Game*> getGameState();


    private:
         bool running;
         GameRenderer::TextCanvas* canvas;
         Utility::Consumer<Game*> currentFrame = [](Game* g) {};
         std::vector <Utility::Consumer<Game*>> gameFrames;
        // Helper method for handling user input
        void handleInput(const std::string& input);

    };

} // namespace ShopGame

#endif // GAME_H