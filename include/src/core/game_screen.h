#pragma once

#include <SDL.h>

class GameScreen {
public:
    virtual void initialize() {}
    virtual void update(float deltaTime) {}
    virtual void render(SDL_Renderer* renderer) {}
    virtual void handleEvent(SDL_Event& event) {}
};