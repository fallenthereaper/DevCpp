
#include "src/core/shop/game_state.h"
#include "src/core/shop/game.h"

ExolorGame::QuitGameState::QuitGameState(Game* game) : ExolorGame::GameMenu(game, "Quit Game Menu") {
    // Update logic for the menu state
}
void ExolorGame::QuitGameState::update(Game* game) {
    GameMenu::update(game);
}
void ExolorGame::QuitGameState::init(Game* game) {

    Blaze2D::GameEngine::getInstance()->quit();

    std::cout << "Closing game..." << std::endl;
  

    game->setRunning(false); 
}
void ExolorGame::QuitGameState::initCommands() {


 
}

void ExolorGame::QuitGameState::render(GameRenderer::TextCanvas* canvas) {
    game->getCanvas()->drawSquare(Vec2(46, 10), 20, 5, '*', "Game Closed", true);

    }
