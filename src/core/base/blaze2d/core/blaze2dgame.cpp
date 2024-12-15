#include "src/core/igame.h"
#include "src/core/game_engine.h"

namespace Blaze2D {

    class Blaze2DGame : public IGame {
    public:
        Blaze2DGame() : m_engine(Blaze2D::GameEngine::getInstance()) {}


        virtual bool init() override;

      //  virtual void handleEvents(SDL_Event& event) override;

        virtual void update(float deltaTime) override;

        virtual void render() override;

        virtual void clean() override;

        GameEngine* getEngine() {
            return m_engine;
        }

    private:
        GameEngine* m_engine;
    };

} // namespace Blaze2D