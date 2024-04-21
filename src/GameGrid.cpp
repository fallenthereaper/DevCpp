#include "GameGrid.h"

GameGrid::GameGrid(int size) : GameGrid(size, size) {
    // Delegates to the previous constructor with width = height = size
}



GameGrid::GameGrid(int width = 3, int height = 3) : width(width), height(height) {
    // Initialize the board
    grid = new char* [height];
    for (int i = 0; i < height; ++i) {
        grid[i] = new char[width];
        for (int j = 0; j < width; ++j) {
            grid[i][j] = ' ';
        }
    }
}

// Destructor
GameGrid::~GameGrid() {
    // Free dynamically allocated memory
    for (int i = 0; i < height; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

// Function to draw the game board
void GameGrid::draw() const {
    std::string horizontalDivider = std::string((width * 3) + width + 1, '-');

    std::cout << horizontalDivider << '\n';
    for (int i = 0; i < height; ++i) {
        std::cout << "| ";
        for (int j = 0; j < width; ++j) {
            std::cout << grid[i][j] << " | ";
        }
        std::cout << '\n' << horizontalDivider << '\n';
    }
}


// Function to place a symbol on the board
bool GameGrid::placeSymbol(int row, int col, char symbol) {
    if (row >= 0 && row < height && col >= 0 && col < width && grid[row][col] == ' ') {
        grid[row][col] = symbol;
        return true; // Valid move
    }
    return false; // Invalid move
}


bool GameGrid::checkWin(char symbol) const {
    // Check rows and columns
    for (int i = 0; i < height; ++i) {
        bool rowWin = true;
        bool colWin = true;

        for (int j = 0; j < width; ++j) {
            if (grid[i][j] != symbol) {
                rowWin = false;
            }
            if (grid[j][i] != symbol) {
                colWin = false;
            }
        }

        if (rowWin || colWin) {
            return true;
        }
    }

    // Check diagonals
    bool diag1Win = true;
    bool diag2Win = true;
    for (int i = 0; i < height; ++i) {
        if (grid[i][i] != symbol) {
            diag1Win = false;
        }
        if (grid[i][height - 1 - i] != symbol) {
            diag2Win = false;
        }
    }

    return diag1Win || diag2Win;
}

int GameGrid::evaluate() const {
    if (checkWin('O')) {
        return 1; // AI wins
    }
    else if (checkWin('X')) {
        return -1; // Human wins
    }
    else if (isGridFull()) {
        return 0; // Draw
    }
    else {
        return INT_MIN; // Game still ongoing
    }
}

bool GameGrid::isGridFull() const {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (grid[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}