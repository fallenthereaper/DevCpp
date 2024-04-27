#pragma once

#include <SDL.h>

namespace Blaze2D {
    struct Vec3 {
        float x, y, z;
    };
    class GameEngine {
    public:
        // Singleton instance getter
        static GameEngine* getInstance() {

            return instance = (instance != nullptr ? instance : new GameEngine());
        }

        // Initialize the game engine
        bool init();
        // Clean up resources
        void clean();
        // Quit the game engine
        void quit();

        // Update the game with delta time
        void tick();

        // Handle SDL events
        void handleEvents();

       void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Uint8 r, Uint8 g, Uint8 b);
        void drawPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b);
        void renderGrid();
        void renderCube(float angle);
        SDL_Point project(const Vec3& point, float fov, float aspectRatio);
        // Render the game
        void render();

        inline bool isRunning() const { 
           
            return m_isRunning;
        };


        

    private:
        GameEngine(); // Private constructor for singleton
        ~GameEngine(); // Private destructor
        static GameEngine* instance;
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        bool m_isRunning;
        int m_screenWidth;
        int m_screenHeight;
    };

} // namespace Blaze2D