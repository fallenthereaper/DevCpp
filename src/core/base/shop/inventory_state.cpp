
#include "src/core/shop/game_state.h"
#include "src/core/shop/game.h"
#include "src/core/shop/inventory.h"
#include "src/core/utils/utility.h" // Include utility for parsing commands

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

void ShopGame::InventoryState::initCommands() {
    GameState::initCommands();

    GameRenderer::TextCanvas* canvas = getGame()->getCanvas();

    addCommand("bank", [canvas](Game* g, InputParameter& param) {
        canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Bank Menu", true);
        });


    addCommand("sell", [canvas](Game* g, InputParameter& param) {
        canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Sell Item", true);
        });
    addCommand("show", [canvas](Game* g, InputParameter& param) {
        std::cout << "Opening Inventory..." << std::endl;

        const auto& itemMap = ItemRegistry::getInstance()->getItemMap();


        Vec2 shopTopLeft(16, 3);
        int maxWidth = 6; // Maximum items per row
        int itemWidth = 18;
        int itemHeight = 3;
        int maxItemCount = 30; // Maximum items to display

        displayItemList(canvas, itemMap, "Inventory", shopTopLeft, maxWidth, itemWidth, itemHeight, maxItemCount);
        });

    addCommand("select", [this](Game* g, const InputParameter& param) {
        if (param.size() == 1) {
            std::string itemName = param[0];
            Item* selectedItem = nullptr;

            // Try to find the item by name first
            selectedItem = ItemRegistry::getInstance()->getItem(itemName);


            std::cout << selectedItem->getName();
            if (selectedItem != nullptr) {
                std::cout << selectedItem->getName();
                //g->getCanvas()->drawText({ 2, 2 }, selectedItem->getName());

            }
          }
        });


}