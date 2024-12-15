#pragma once

#include <iostream>
#include <chrono>
#include <memory>


namespace Blaze2D {
    class IGame;
    struct Vec3 {
        float x, y, z;
    };
    class GameEngine {
    public:
        // Singleton instance getter
        static GameEngine* getInstance() {

            return instance = (instance != nullptr ? instance : new GameEngine());
        }

        float calculateDeltaTime() {
          //  static Uint32 lastTime = SDL_GetTicks();
          //  Uint32 currentTime = SDL_GetTicks();
          //  float deltaTime = (currentTime - lastTime) / 1000.0f;
          //  lastTime = currentTime;
          //  return deltaTime;
          return 0;
        }

       void run(std::unique_ptr<IGame> game);

        // Initialize the game engine
        bool init(const std::string& windowTitle, int screenHeight, int screenWidth);
        // Clean up resources
        void clean();
        // Quit the game engine
        void quit();

        // Update the game with delta time
        void tick();

        // Handle SDL events
        void handleEvents();

        void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b);
      //  void drawPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b);
        void renderGrid();
        void renderCube(float angle);
      //  SDL_Point project(const Vec3& point, float fov, float aspectRatio);
        // Render the game
        void render();

        inline bool isRunning() const { 
           
            return m_isRunning;
        };


        

    private:
        GameEngine(); // Private constructor for singleton
        ~GameEngine(); // Private destructor
        static GameEngine* instance;
       // SDL_Window* m_window;
       // SDL_Renderer* m_renderer;
        std::string title;
        bool m_isRunning;
        int m_screenWidth;
        int m_screenHeight;
        float  m_fpsCounter, m_lastSecondTime, m_lastTickTime, m_fps;
    };

} // namespace Blaze2D