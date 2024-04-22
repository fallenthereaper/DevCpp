#ifndef GAMEGRID_H
#define GAMEGRID_H

#include <iostream>
#include <string>

class GameGrid {
private:
    char** grid;
    int width;
    int height;

public:
    // Alternate constructor with separate width and height
    GameGrid(int width, int height);
    // Constructor with default width and height
    GameGrid(int gridSize = 3);
    // Destructor
    ~GameGrid();

    void draw() const;

    bool placeSymbol(int row, int col, char symbol);

    bool matchesPattern(char symbol) const;

    int evaluate() const;

    bool isGridFull() const;
};

#endif // GAMEGRID_H