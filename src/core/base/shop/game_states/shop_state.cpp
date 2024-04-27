
#include "src/core/shop/game_state.h"
#include "src/core/shop/game.h"

ExolorGame::ShopState::ShopState(Game* game) : ExolorGame::GameMenu(game, "Shop Menu") {
    // Update logic for the menu state
}

void ExolorGame::ShopState::update(Game* game) {
    // Implement update logic for the shop state
}

void ExolorGame::ShopState::init(Game* game) {
    GameMenu::init(game);
}

void ExolorGame::ShopState::render(GameRenderer::TextCanvas* canvas) {
    // Implement rendering logic for the shop state
}

void ExolorGame::ShopState::initCommands() {
    GameMenu::initCommands();

    GameRenderer::TextCanvas* canvas = getGame()->getCanvas();

    addCommand("buy", [canvas](Game* g, InputParameter param) {
        canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Buy Item", true);
        });

    addCommand("inventory", [canvas](Game* g, InputParameter param) {
        g->setGameState(new InventoryState(g));
        });


    addCommand("sell", [canvas](Game* g, InputParameter param) {
        canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Sell Item", true);
        });
    addCommand("show", [canvas](Game* g, InputParameter param) {
    

        const auto& itemMap = ItemRegistry::getInstance()->getItemMap();


        Vec2 shopTopLeft(16, 3);
        int maxWidth = 6; // Maximum items per row
        int itemWidth = 18;
        int itemHeight = 3;
        int maxItemCount = 30; // Maximum items to display

        displayItemList(canvas, itemMap, "Item Shop", shopTopLeft, maxWidth, itemWidth, itemHeight, maxItemCount);
        });


}