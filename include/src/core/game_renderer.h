#pragma once
#include <chrono>
#include "src/core/shop/Game.h";
#include <thread>
class ShopGame::ItemRegistry;

namespace GameRenderer {

    void clearScreen();

  
    void render(ShopGame::Game* game);

} // namespace GameRenderer
