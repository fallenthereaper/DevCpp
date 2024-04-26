#pragma once
#include <chrono>
#include "src/core/shop/Game.h";
#include <thread>

class ExolorGame::ItemRegistry;

namespace GameRenderer {

    void clearScreen();
    void cls();
  
    void render(ExolorGame::Game* game);

} // namespace GameRenderer
