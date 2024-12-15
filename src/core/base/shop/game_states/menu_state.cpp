
#include "src/core/shop/game_state.h"
#include "src/core/shop/game.h"
#include "core/tictac_game.h"
#include <windows.h>

ExolorGame::MenuState::MenuState(Game* game) : ExolorGame::GameMenu(game, "Game Menu") {
    // Update logic for the menu state
}
void ExolorGame::MenuState::update(Game* game) {
    GameMenu::update(game);
}
void ExolorGame::MenuState::init(Game* game) {
    GameMenu::init(game);
}
void ExolorGame::MenuState::initCommands() {
    GameMenu::initCommands();

    GameRenderer::TextCanvas* canvas = getGame()->getCanvas();

    addCommand("shop", [canvas](Game* g, InputParameter param) {
        g->setGameState(new ShopState(g));
        g->getGameState()->handleInput(g, "show");

        });
    addCommand("snake_game", [canvas](Game* g, InputParameter& param) {
        std::cout << "Starting Blaze2D..." << std::endl;
    
        Utility::bootGameEngine("Snake Game", 640, 640);

        });

    addCommand("tictac_game", [canvas](Game* g, InputParameter& param) {
        std::cout << "Starting Blaze2D..." << std::endl;

   //     Utility::bootGameEngine("TicTac Game", 500, 500);
        TicTacGame::startUp(canvas);
        });

    addCommand("rpg_game", [canvas](Game* g, InputParameter& param) {
        std::cout << "Starting Blaze2D..." << std::endl;

        Utility::bootGameEngine("RPG Game", 500, 500);

        });



    addCommand("help", [canvas](Game* g, InputParameter param) {
        canvas->drawSquare(Vec2(46, 10), 20, 5, '*', "Help Menu", false);
        canvas->drawSquare(Vec2(48, 12), 16, 3, '*', "Commands:", false);
        canvas->drawSquare(Vec2(50, 14), 12, 3, '*', "shop - Open shop", false);
        canvas->drawSquare(Vec2(50, 16), 12, 3, '*', "exit - Exit game", false);
        canvas->drawSquare(Vec2(50, 18), 12, 3, '*', "clear - Clear canvas", false);
        canvas->drawSquare(Vec2(50, 20), 12, 3, '*', "info - Game info", false);
        canvas->drawSquare(Vec2(50, 22), 12, 3, '*', "help - Display help", false);
        });

    addCommand("info", [canvas](Game* g, InputParameter param) {
        std::cout << "Displaying info..." << std::endl;
        canvas->drawSquare(Vec2(46, 3), 20, 5, '*', "Game Information", true);

        canvas->drawText(Vec2(46, 14), "Version: 1.0");
        canvas->drawText(Vec2(46, 16), "Developer: " + g->getName());

        // Display screen size
        int screenWidth = g->getCanvas()->getWidth();
        int screenHeight = g->getCanvas()->getHeight();
        canvas->drawText(Vec2(46, 18), "Screen Size:");
        canvas->drawText(Vec2(46, 20), "Width: " + std::to_string(screenWidth));
        canvas->drawText(Vec2(46, 22), "Height: " + std::to_string(screenHeight));

        // Display available commands
        int x = 6;
        canvas->drawSquare(Vec2(x - 2, 2), 28, 14, '*', "", true);
        canvas->drawText(Vec2(x, 3), "Commands:");
        canvas->drawText(Vec2(x, 5), "shop - Open shop");
        canvas->drawText(Vec2(x, 7), "exit - Exit game");
        canvas->drawText(Vec2(x, 9), "clear - Clear canvas");
        canvas->drawText(Vec2(x, 11), "info - Display game info");
        canvas->drawText(Vec2(x, 13), "help - Display help menu");
        });
}


void ExolorGame::MenuState::render(GameRenderer::TextCanvas* canvas) {


    GameMenu::render(canvas);

    
}