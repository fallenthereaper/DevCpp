
#include "src/core/shop/game.h"

namespace ShopGame {

    class GameState {
    public:
        virtual ~GameState() = default;
        virtual void handleInput(Game* game, const std::string& input) = 0;
        virtual void update(Game* game) = 0;
        virtual void render(GameRenderer::TextCanvas* canvas) = 0;
    };
}