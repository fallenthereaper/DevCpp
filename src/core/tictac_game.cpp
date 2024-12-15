

#include "src/core/tictac_game.h"

const int BOARD_SIZE = 9;
char board[BOARD_SIZE][BOARD_SIZE];

using namespace std;

    const string repeatString(const string &str, int count) {
        string result;
        for (int i = 0; i < count; ++i) {
            result += str;
        }
        return result;
    }


    void drawBoard() {
        int cellWidth = 3; // Width of each board cell (e.g., "| X |")
        int totalCellWidth = BOARD_SIZE * cellWidth; // Total width occupied by cells
        int totalDividers = BOARD_SIZE + 1; // Number of vertical dividers
        int totalSpaces = totalCellWidth + totalDividers; // Total spaces needed for the board

        string horizontalDivider = repeatString("-", totalSpaces);

        cout << horizontalDivider << '\n';
        for (int i = 0; i < BOARD_SIZE; ++i) {
            cout << "| ";
            for (int j = 0; j < BOARD_SIZE; ++j) {
                cout << board[i][j] << " | "; // Draw columns
            }
            cout << '\n' << horizontalDivider << '\n';
        }
    }


    bool checkWin(const char &symbol) {
        // Check rows and columns
        for (int i = 0; i < BOARD_SIZE; ++i) {
            bool rowWin = true;
            bool colWin = true;

            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] != symbol) {
                    rowWin = false;
                }
                if (board[j][i] != symbol) {
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
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (board[i][i] != symbol) {
                diag1Win = false;
            }
            if (board[i][BOARD_SIZE - 1 - i] != symbol) {
                diag2Win = false;
            }
        }

        return diag1Win || diag2Win;
    }

    bool isBoardFull() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] == ' ') {
                    return false; // Board is not full
                }
            }
        }
        return true; // Board is full
    }

    int evaluateBoard() {
        if (checkWin('O')) {
            return 1; // AI wins
        } else if (checkWin('X')) {
            return -1; // Human wins
        } else if (isBoardFull()) {
            return 0; // Draw
        } else {
            return INT_MIN; // Game still ongoing
        }
    }

    // Function to check if the game is over
    bool gameOver() {
        // Check rows and columns for a win
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                return true; // Row win
            }
            if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                return true; // Column win
            }
        }

        // Check diagonals for a win
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            return true; // Diagonal (\) win
        }
        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            return true; // Diagonal (/) win
        }

        // Check for a draw
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] == ' ') {
                    return false; // Game is not over yet
                }
            }
        }
        return true; // Draw
    }


    // Minimax function for AI's move
    int minimax(int depth, bool isMaximizing) {
        int score = evaluateBoard();

        // Base cases (terminal states)
        if (score == 1) return score; // AI wins
        if (score == -1) return score; // Human wins
        if (score == 0) return 0; // Draw

        // Maximizer's turn (AI)
        if (isMaximizing) {
            int bestScore = INT_MIN;
            for (int i = 0; i < BOARD_SIZE; ++i) {
                for (int j = 0; j < BOARD_SIZE; ++j) {
                    if (board[i][j] == ' ') {
                        board[i][j] = 'O';
                        bestScore = std::max(bestScore, minimax(depth + 1, false));
                        board[i][j] = ' ';
                    }
                }
            }
            return bestScore;
        }
            // Minimizer's turn (Human)
        else {
            int bestScore = INT_MAX;
            for (int i = 0; i < BOARD_SIZE; ++i) {
                for (int j = 0; j < BOARD_SIZE; ++j) {
                    if (board[i][j] == ' ') {
                        board[i][j] = 'X';
                        bestScore = std::min(bestScore, minimax(depth + 1, true));
                        board[i][j] = ' ';
                    }
                }
            }
            return bestScore;
        }
    }

    // Function to make AI's move using minimax algorithm
    void makeAIMove() {
        int bestScore = INT_MIN;
        int bestMoveRow = -1;
        int bestMoveCol = -1;

        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int moveScore = minimax(0, false);
                    board[i][j] = ' ';

                    if (moveScore > bestScore) {
                        bestScore = moveScore;
                        bestMoveRow = i;
                        bestMoveCol = j;
                    }
                }
            }
        }

        board[bestMoveRow][bestMoveCol] = 'O';
    }

    void initializeBoard() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board[i][j] = ' ';
            }
        }
    }


    void TicTacGame::startUp() {

        GameGrid *gameGrid = new GameGrid(3, 3);



        // Game loop
        while (gameGrid->evaluate() == INT_MIN) {
            // Display the board
            gameGrid->draw();

            // Human player's turn
            int row, col;
            std::cout << "Enter your move (row and column, e.g., 1 2): ";
            std::cin >> row >> col;

            if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || !gameGrid->placeSymbol(row, col, 'X')) {
                std::cout << "Invalid move! Try again.\n";
                continue;
            }

            // Check if the game is over after human player's move
            if (gameGrid->evaluate() != INT_MIN) {
                break;
            }

            // AI's turn
            std::cout << "AI's turn...\n";
            // gameGrid.makeAIMove();

            // Check if the game is over after AI's move
            //if (gameGrid.gameOver()) {
            //    break;
            // }
        }

        // Display the final board
        gameGrid->draw();

        // Evaluate the final game state
        int gameResult = gameGrid->evaluate();
        if (gameResult == 1) {
            std::cout << "AI wins!\n";
        } else if (gameResult == -1) {
            std::cout << "Human wins!\n";
        } else {
            std::cout << "It's a draw!\n";
        }

        delete gameGrid;
    }