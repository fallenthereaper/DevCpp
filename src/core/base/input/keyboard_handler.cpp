#include "src/core/input/keyboard_handler.h"

KeyboardHandler::KeyboardHandler()
{
    std::fill(m_keys.begin(), m_keys.end(), false);
}

void KeyboardHandler::update(int& e) {

    /*
    if (e.type == 0 && !e.key.repeat) {
        m_keys[e.key.keysym.scancode] = true;
    }
    else if (e.type == 0) {
        m_keys[e.key.keysym.scancode] = false;
        m_recentlyReleased = e.key.keysym.scancode;
    }
     */
}

bool KeyboardHandler::isKeyDown(int key) const {
    return m_keys[key];
}

bool KeyboardHandler::isKeyReleased(int key) const
{
    return m_recentlyReleased == key;
}