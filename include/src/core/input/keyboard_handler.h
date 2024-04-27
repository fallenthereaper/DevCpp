#pragma once

#include <SDL.h>
#include <array>

class KeyboardHandler {
public:
    KeyboardHandler();

    void update(SDL_Event& e);

    bool isKeyDown(SDL_Scancode key) const;

    bool isKeyReleased(SDL_Scancode key) const;

private:
    std::array<bool, SDL_NUM_SCANCODES> m_keys;
    SDL_Scancode m_recentlyReleased;
};