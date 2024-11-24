#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char board[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};

// Function to print the game board
void printBoard() {
    printf("%c | %c | %c\n", board[0], board[1], board[2]);
    printf("%c | %c | %c\n", board[3], board[4], board[5]);
    printf("%c | %c | %c\n", board[6], board[7], board[8]);
}

// Function to handle a player's turn
void takeTurn(char player) {
    int position;
    printf("%c's turn.\n", player);
    printf("Choose a position from 1-9: ");
    scanf("%d", &position);
    position -= 1;
    
    while (position < 0 || position > 8 || board[position] != '-') {
        printf("Invalid input or position already taken. Choose a different position: ");
        scanf("%d", &position);
        position -= 1;
    }
    
    board[position] = player;
    printBoard();
}

// Function to check if the game is over
char* checkGameOver() {
    // Check for a win
    if ((board[0] == board[1] && board[1] == board[2] && board[0] != '-') ||
        (board[3] == board[4] && board[4] == board[5] && board[3] != '-') ||
        (board[6] == board[7] && board[7] == board[8] && board[6] != '-') ||
        (board[0] == board[3] && board[3] == board[6] && board[0] != '-') ||
        (board[1] == board[4] && board[4] == board[7] && board[1] != '-') ||
        (board[2] == board[5] && board[5] == board[8] && board[2] != '-') ||
        (board[0] == board[4] && board[4] == board[8] && board[0] != '-') ||
        (board[2] == board[4] && board[4] == board[6] && board[2] != '-')) {
        return "win";
    }
    // Check for a tie
    else if (strchr(board, '-') == NULL) {
        return "tie";
    }
    // Game is not over
    return "play";
}

// Main game loop
int main() {
    printBoard();
    char currentPlayer = 'X';
    bool gameOver = false;
    
    while (!gameOver) {
        takeTurn(currentPlayer);
        char* gameResult = checkGameOver();
        
        if (strcmp(gameResult, "win") == 0) {
            printf("%c wins!\n", currentPlayer);
            gameOver = true;
        } else if (strcmp(gameResult, "tie") == 0) {
            printf("It's a tie!\n");
            gameOver = true;
        } else {
            // Switch to the other player
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
    return 0;
}
