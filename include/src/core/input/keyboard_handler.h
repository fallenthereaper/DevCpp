#pragma once

#include <array>

class KeyboardHandler {
public:
    KeyboardHandler();

    void update(int& e);

    bool isKeyDown(int key) const;

    bool isKeyReleased(int key) const;

private:
    std::array<bool, 12> m_keys;
    int m_recentlyReleased;
};