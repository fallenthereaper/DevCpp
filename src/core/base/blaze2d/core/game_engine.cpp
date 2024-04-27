#include "src/core/game_engine.h"
#include "src/core/igame.h"
#include <string>
#define SCREEN_WIDTH 500;
#define SCREEN_HEIGHT 500;

namespace Blaze2D {

    GameEngine* GameEngine::instance = nullptr;

    GameEngine::GameEngine()
        : m_window(nullptr), m_renderer(nullptr), m_isRunning(false), m_screenWidth(0), m_screenHeight(0), m_fpsCounter(0), m_lastSecondTime(0), m_lastTickTime(0), m_fps(0), title("") {}


    void GameEngine::run(std::unique_ptr<IGame> game) {
        m_isRunning = true;

        game->init();

        while (m_isRunning) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    quit();
                }
                game->handleEvents(event);
            }

            game->update(calculateDeltaTime()); // Fixed time step update (60 FPS equivalent)
            game->render();
        }

        game->clean();
        clean();
    }
  

    bool GameEngine::init(const std::string& windowTitle, int screenHeight, int screenWidth) {
       // clean();

        m_screenHeight = screenHeight;
        m_screenWidth = screenWidth;
        title = windowTitle; 
        


     
       
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            SDL_Log("SDL initialization failed: %s", SDL_GetError());
            return false;
        }

        m_window = SDL_CreateWindow(("Blaze2D Engine | " + windowTitle).c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);


        if (!m_window) {
            SDL_Log("Window creation failed: %s", SDL_GetError());
            SDL_Quit();
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!m_renderer) {
            SDL_Log("Renderer creation failed: %s", SDL_GetError());
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        ;
      
  
        return m_isRunning = true;
    }



    void GameEngine::tick() {
        SDL_Delay(0.16);
        Uint32 currentTime = SDL_GetTicks();  // Get current time in milliseconds since SDL initialization
        Uint32 deltaTime = currentTime - m_lastTickTime;  // Calculate time elapsed since last frame
        m_lastTickTime = currentTime;  // Update the last tick time to current time

        // Increment the FPS counter for each frame
        ++m_fpsCounter;

        // Update FPS display every second (1000 milliseconds)
        if (currentTime - m_lastSecondTime >= 1000) {
            // Calculate FPS as the number of frames rendered in the last second
            m_fps = m_fpsCounter;

            // Reset the FPS counter for the next second
            m_fpsCounter = 0;

            // Update the last second time to the current time
            m_lastSecondTime = currentTime;

            // Update the window title to display the current FPS
            std::string windowTitle = "Blaze2D Engine | " + std::string(title) + std::string(" | FPS: ") + std::to_string((int)m_fps);
            
            SDL_SetWindowTitle(m_window, windowTitle.c_str());
        }
    }

    void GameEngine::drawPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b) {
        SDL_SetRenderDrawColor(m_renderer, r, g, b, 255);
        SDL_RenderDrawPoint(m_renderer, x, y);
    }


    void GameEngine::handleEvents() {
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type) {
        case SDL_QUIT:
                quit();
                break;
        
        }
       


    }

    void GameEngine::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Uint8 r, Uint8 g, Uint8 b) {
        // Set the render draw color
        SDL_SetRenderDrawColor(m_renderer, r, g, b, 255);

        // Draw lines connecting the vertices to form the triangle
        SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
        SDL_RenderDrawLine(m_renderer, x2, y2, x3, y3);
        SDL_RenderDrawLine(m_renderer, x3, y3, x1, y1);
    }

    void GameEngine::renderGrid() {
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255); // Set draw color to white

        // Calculate cell width and height based on screen size and grid dimensions
        int cellWidth = 20;
        int cellHeight = 20;

        // Draw vertical grid lines
        for (int col = 0; col <= 16; ++col) {
            int x = col * cellWidth;
            SDL_RenderDrawLine(m_renderer, x, 0, x, 600);
        }

        // Draw horizontal grid lines
        for (int row = 0; row <= 16; ++row) {
            int y = row * cellHeight;
            SDL_RenderDrawLine(m_renderer, 0, y, 800, y);
        }
    }

   

    // Function to project 3D coordinates onto 2D screen
    SDL_Point GameEngine::project(const Vec3& point, float fov, float aspectRatio) {
        float x = point.x / (-point.z * tan(fov / 2));
        float y = point.y / (-point.z * tan(fov / 2) / aspectRatio);
        return { static_cast<int>(x + 800 / 2), static_cast<int>(y + 600 / 2) };
    }

    void GameEngine::renderCube(float angle) {
        // Define cube vertices
        Blaze2D::Vec3 vertices[8] = {
            {-50, -50, -50}, {50, -50, -50}, {50, 50, -50}, {-50, 50, -50},
            {-50, -50, 50},  {50, -50, 50},  {50, 50, 50},  {-50, 50, 50} };

        // Define cube edges
        const int edges[12][2] = {
            {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Front face
            {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Back face
            {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Connecting edges
        };

        // Calculate rotation matrix
        float s = sin(angle);
        float c = cos(angle);
        float rotationMatrix[3][3] = { {c, 0, -s}, {0, 1, 0}, {s, 0, c} };

        // Project and render edges
        for (const auto& edge : edges) {
            Blaze2D::Vec3 start = vertices[edge[0]];
            Vec3 end = vertices[edge[1]];

            // Apply rotation to vertices
            Vec3 rotatedStart = {
                start.x * rotationMatrix[0][0] + start.y * rotationMatrix[0][1] + start.z * rotationMatrix[0][2],
                start.x * rotationMatrix[1][0] + start.y * rotationMatrix[1][1] + start.z * rotationMatrix[1][2],
                start.x * rotationMatrix[2][0] + start.y * rotationMatrix[2][1] + start.z * rotationMatrix[2][2] };

            Vec3 rotatedEnd = {
                end.x * rotationMatrix[0][0] + end.y * rotationMatrix[0][1] + end.z * rotationMatrix[0][2],
                end.x * rotationMatrix[1][0] + end.y * rotationMatrix[1][1] + end.z * rotationMatrix[1][2],
                end.x * rotationMatrix[2][0] + end.y * rotationMatrix[2][1] + end.z * rotationMatrix[2][2] };

            // Project vertices onto 2D screen
            SDL_Point screenStart = project(rotatedStart, M_PI / 3, 800 / static_cast<float>(600));
            SDL_Point screenEnd = project(rotatedEnd, M_PI / 3, 800 / static_cast<float>(600));

            // Render edge
            SDL_RenderDrawLine(m_renderer, screenStart.x, screenStart.y, screenEnd.x, screenEnd.y);
        }
    }

    void GameEngine::render() {
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); // Clear with black color
        SDL_RenderClear(m_renderer);

        int numRows = 8; // Number of rows
        int numCols = 8; // Number of columns
        int blockSize = m_screenWidth / numRows; // Size of each block (assuming square blocks)




        // Render grid of black and white squares (checkerboard pattern)
        for (int row = 0; row < numRows; ++row) {
            for (int col = 0; col < numCols; ++col) {
                // Determine color based on row and column (checkerboard pattern)
                SDL_Color color = ((row + col) % 2 == 0) ? SDL_Color{ 255, 255, 255, 255 } : SDL_Color{ 128, 128, 128, 255 };

                // Set render draw color based on current color
                SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

                // Calculate block position and size
                SDL_Rect blockRect = { col * blockSize, row * blockSize, blockSize, blockSize };

                // Render filled rectangle (block)
                SDL_RenderFillRect(m_renderer, &blockRect);
            }
        }

        SDL_RenderPresent(m_renderer); // Present rendered content
    }

    void GameEngine::clean() {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        quit();
    
    }

    void GameEngine::quit() {
        m_isRunning = false;
    }

} // namespace Blaze2D