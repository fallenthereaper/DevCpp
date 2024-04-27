#include <SDL.h>

namespace Blaze2D {

    class IGame {
    public:
        virtual ~IGame() {}

        virtual bool init() = 0;
        virtual void handleEvents(SDL_Event& event) = 0;
        virtual void update(float deltaTime) = 0;
        virtual void render() = 0;
        virtual void clean() = 0;


    };

} // namespace Blaze2D