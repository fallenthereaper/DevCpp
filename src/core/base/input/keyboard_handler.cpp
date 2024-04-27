#include "src/core/input/keyboard_handler.h"

KeyboardHandler::KeyboardHandler()
{
    std::fill(m_keys.begin(), m_keys.end(), false);
}

void KeyboardHandler::update(SDL_Event& e) {
  
    if (e.type == SDL_KEYDOWN && !e.key.repeat) {
        m_keys[e.key.keysym.scancode] = true;
    }
    else if (e.type == SDL_KEYUP) {
        m_keys[e.key.keysym.scancode] = false;
        m_recentlyReleased = e.key.keysym.scancode;
    }
}

bool KeyboardHandler::isKeyDown(SDL_Scancode key) const {
    return m_keys[key];
}

bool KeyboardHandler::isKeyReleased(SDL_Scancode key) const
{
    return m_recentlyReleased == key;
}