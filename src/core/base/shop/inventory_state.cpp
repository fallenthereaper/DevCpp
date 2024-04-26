
#include "src/core/shop/game_state.h"
#include "src/core/shop/game.h"
#include "src/core/shop/inventory.h"


ShopGame::InventoryState::InventoryState(Game* game) : ShopGame::GameState(game, "Inventory Menu"), inventory(new ShopGame::Inventory(18)) {
    
}

void ShopGame::InventoryState::update(Game* game) {
   
}

void ShopGame::InventoryState::init(Game* game) {
    GameState::init(game);
}

void ShopGame::InventoryState::render(GameRenderer::TextCanvas* canvas) {
   
}

ShopGame::Inventory* ShopGame::InventoryState::getInventory() {
    return inventory;
}

void ShopGame::InventoryState::registerCommands() {
    GameState::registerCommands();

    GameRenderer::TextCanvas* canvas = getGame()->getCanvas();

    addCommand("bank", [canvas](Game* g) {
        canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Bank Menu", true);
        });


    addCommand("sell", [canvas](Game* g) {
        canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Sell Item", true);
        });
    addCommand("show", [canvas](Game* g) {
        std::cout << "Opening shop..." << std::endl;

        const auto& itemMap = ItemRegistry::getInstance()->getItemMap();


        Vec2 shopTopLeft(16, 3);
        int maxWidth = 6; // Maximum items per row
        int itemWidth = 18;
        int itemHeight = 3;
        int maxItemCount = 30; // Maximum items to display

        displayItemList(canvas, itemMap, "Inventory", shopTopLeft, maxWidth, itemWidth, itemHeight, maxItemCount);
        });


}