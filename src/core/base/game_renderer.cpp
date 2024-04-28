#pragma once


#include "src/core/game_renderer.h";
#include <SDL.h>

namespace GameRenderer {

    void GameRenderer::clearScreen() {
        system("CLS");
    }

	void GameRenderer::cls()
	{
	
	}

    // Renders the game state
    void GameRenderer::render(ExolorGame::Game* game) {
         clearScreen();

          // Calculate FPS
        static auto lastTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();
        double deltaTime = std::chrono::duration<double, std::milli>(currentTime - lastTime).count();
        lastTime = currentTime;
        double fps = 1000.0 / deltaTime; 

        
        static double smoothedFps = 0.1;
        const double smoothingFactor = 0.1; 
        smoothedFps = (smoothingFactor * fps) + ((1.0 - smoothingFactor) * smoothedFps);

        game->render();
        game->getCanvas()->clear(); //Clear the buffer after rendering the current canvas
       

        std::this_thread::sleep_for(std::chrono::milliseconds(30)); 
    }

} // namespace GameRenderer
