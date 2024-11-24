#include <stdio.h>
#include <limits.h>

// Constants representing players and empty cells
#define PLAYER_X 'X'
#define PLAYER_O 'O'
#define EMPTY ' '

char board[3][3] = {
    {EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY}
};

// Function to print the game board
void printBoard() {
    printf("\nCurrent Board:\n\n");
    printf("      ---------------\n");
    for (int i = 0; i < 3; i++) {
        printf("  %d ", i);
        for (int j = 0; j < 3; j++) {
            printf("|  %c  ", board[i][j]);
        }
        printf("|\n");
        printf("      ---------------\n");
    }
    printf("       0     1     2\n");
}

// Function to check if a player has won
int isWinning(char player) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return 1;
        }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return 1;
    }
    return 0;
}

// Function to check if the game is a draw
int isDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                return 0;
            }
        }
    }
    return 1;
}

// Minimax algorithm with depth to prioritize faster wins and avoid quick losses
int minimax(int depth, int isMaximizing) {
    // Base cases: check for terminal states
    if (isWinning(PLAYER_X)) return 10 - depth; // Maximize faster wins
    if (isWinning(PLAYER_O)) return depth - 10; // Minimize quicker losses
    if (isDraw()) return 0; // Draw

    if (isMaximizing) {
        int bestScore = INT_MIN;
        // Iterate over all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_X; // Make a move
                    int score = minimax(depth + 1, 0); // Recursively call minimax
                    board[i][j] = EMPTY; // Undo the move
                    if (score > bestScore) {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = INT_MAX;
        // Iterate over all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_O; // Make a move
                    int score = minimax(depth + 1, 1); // Recursively call minimax
                    board[i][j] = EMPTY; // Undo the move
                    if (score < bestScore) {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
}

// Function to find the best move for the computer (PLAYER_X)
void findBestMove(int* bestRow, int* bestCol) {
    int bestScore = INT_MIN;
    *bestRow = -1;
    *bestCol = -1;
    // Iterate over all cells to find the best move
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = PLAYER_X; // Make a move
                int score = minimax(0, 0); // Evaluate the move
                board[i][j] = EMPTY; // Undo the move
                if (score > bestScore) {
                    bestScore = score;
                    *bestRow = i;
                    *bestCol = j;
                }
            }
        }
    }
}

// Function to handle the player's move (PLAYER_O)
void playerMove() {
    int row, col;
    printf("Enter your move (row and column from 0 to 2): ");
    scanf("%d %d", &row, &col);
    while (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != EMPTY) {
        printf("Invalid move. Try again: ");
        scanf("%d %d", &row, &col);
    }
    board[row][col] = PLAYER_O;
}

// Main game function
void playGame() {
    while (1) {
        printBoard();

        // Check if the player has won
        if (isWinning(PLAYER_O)) {
            printf("Congratulations! You win!\n");
            return;
        }
        // Check if the game is a draw
        if (isDraw()) {
            printf("It's a draw!\n");
            return;
        }

        playerMove(); // Player's move

        // Check if the player has won after their move
        if (isWinning(PLAYER_O)) {
            printBoard();
            printf("Congratulations! You win!\n");
            return;
        }
        // Check if the game is a draw after the player's move
        if (isDraw()) {
            printBoard();
            printf("It's a draw!\n");
            return;
        }

        // Computer makes its move
        int bestRow, bestCol;
        findBestMove(&bestRow, &bestCol);
        board[bestRow][bestCol] = PLAYER_X;
        printf("Computer placed 'X' in position: (%d, %d)\n", bestRow, bestCol);

        // Check if the computer has won
        if (isWinning(PLAYER_X)) {
            printBoard();
            printf("Computer wins!\n");
            return;
        }
        // Check if the game is a draw after the computer's move
        if (isDraw()) {
            printBoard();
            printf("It's a draw!\n");
            return;
        }
    }
}

// Main function
int main() {
    printf("Welcome to Tic-Tac-Toe!\n");
    playGame();
    return 0;
}


//O(b^d) b=branching factor(possible moves per turn). d=depth(total moves in a game)