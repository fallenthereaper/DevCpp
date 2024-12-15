#ifndef GAMEGRID_H
#define GAMEGRID_H

#include <iostream>
#include <string>
#include "src/core/text_canvas.h"

class GameGrid {
private:
    char** grid{};
    int width;
    int height;
    GameRenderer::TextCanvas* canvas;

public:
    // Alternate constructor with separate width and height
    GameGrid(int width, int height);
    // Constructor with default width and height
    GameGrid(int gridSize = 3);

     GameGrid(int width, int height, GameRenderer::TextCanvas* canvas);
    // Destructor
    ~GameGrid();

    void draw() const;

    bool placeSymbol(int row, int col, char symbol);

    bool matchesPattern(char symbol) const;

    int evaluate() const;

    bool isGridFull() const;

    GameRenderer::TextCanvas* getCanvas() const;
};

#endif // GAMEGRID_H