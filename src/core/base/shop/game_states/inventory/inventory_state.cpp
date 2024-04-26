
#include "src/core/shop/game_state.h"
#include "src/core/shop/game.h"
#include "src/core/shop/inventory.h"
#include "src/core/utils/utility.h" // Include utility for parsing commands

ExolorGame::InventoryState::InventoryState(Game* game) : ExolorGame::GameState(game, "Inventory Menu"), inventory(new ExolorGame::Inventory(18)) {
    
}

void ExolorGame::InventoryState::update(Game* game) {
   
}

void ExolorGame::InventoryState::init(Game* game) {
    GameState::init(game);
}

void ExolorGame::InventoryState::render(GameRenderer::TextCanvas* canvas) {
   
}

ExolorGame::Inventory* ExolorGame::InventoryState::getInventory() {
    return inventory;
}

void ExolorGame::InventoryState::initCommands() {
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

            // Try to find the item by name
            selectedItem = ItemRegistry::getInstance()->getItem(itemName);

            if (selectedItem != nullptr) {
                GameRenderer::TextCanvas* canvas = g->getCanvas();
                std::string itemName = selectedItem->getName();

                // Calculate the required dimensions for the square
                int width = itemName.length() + 4; // Width of the square (item name + padding)
                int height = 5; // Height of the square

                // Draw a square with item information
                canvas->drawSquare({ 8, 2 }, width, height, '*', "Selected Item", true);
                canvas->drawText({ 8, 8 }, itemName); // Display item name within the square
            }
            else {
                std::cout << "Item not found." << std::endl;
            }
        }
       
        });
     }



