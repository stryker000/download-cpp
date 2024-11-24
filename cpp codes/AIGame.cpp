#include <iostream>
#include <vector>

using namespace std;

class TicTacToe {
private:
    vector<vector<char>> board;
    char currentPlayer;

public:
    TicTacToe() {
        board = vector<vector<char>>(3, vector<char>(3, ' '));
        currentPlayer = 'X';
    }

    void displayBoard() {
        cout << "  0 1 2\n";
        for (int i = 0; i < 3; ++i) {
            cout << i << " ";
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j];
                if (j < 2) cout << "|";
            }
            cout << "\n";
            if (i < 2) cout << "  -----\n";
        }
    }

    bool checkWin(char player) {
        for (int i = 0; i < 3; ++i) {
            if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
                (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
                return true;
            }
        }
        if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
            (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
            return true;
        }
        return false;
    }

    bool checkDraw() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') return false;
            }
        }
        return true;
    }

    int minimax(bool isMaximizing) {
        if (checkWin('O')) return 1; 
        if (checkWin('X')) return -1; 
        if (checkDraw()) return 0; 

        if (isMaximizing) {
            int bestScore = -1000;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (board[i][j] == ' ') {
                        board[i][j] = 'O'; 
                        int score = minimax(false);
                        board[i][j] = ' '; 
                        bestScore = max(score, bestScore);
                    }
                }
            }
            return bestScore;
        } else {
            int bestScore = 1000;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (board[i][j] == ' ') {
                        board[i][j] = 'X'; 
                        int score = minimax(true);
                        board[i][j] = ' '; 
                        bestScore = min(score, bestScore);
                    }
                }
            }
            return bestScore;
        }
    }

    pair<int, int> findBestMove() {
        int bestScore = -1000;
        pair<int, int> bestMove = {-1, -1};

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O'; 
                    int score = minimax(false);
                    board[i][j] = ' '; 
                    if (score > bestScore) {
                        bestScore = score;
                        bestMove = {i, j};
                    }
                }
            }
        }
        return bestMove;
    }

    void play() {
        int row, col;
        while (true) {
            displayBoard();
            if (currentPlayer == 'X') {
                cout << "Player X, enter your move (row and column): ";
                cin >> row >> col;

                if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
                    cout << "Invalid move! Try again.\n";
                    continue;
                }
                board[row][col] = currentPlayer;

                if (checkWin(currentPlayer)) {
                    displayBoard();
                    cout << "Player X wins!\n";
                    break;
                } else if (checkDraw()) {
                    displayBoard();
                    cout << "It's a draw!\n";
                    break;
                }

                currentPlayer = 'O'; 
            } else {
                cout << "AI is making a move...\n";
                pair<int, int> bestMove = findBestMove();
                board[bestMove.first][bestMove.second] = currentPlayer;

                if (checkWin(currentPlayer)) {
                    displayBoard();
                    cout << "Player O wins!\n";
                    break;
                } else if (checkDraw()) {
                    displayBoard();
                    cout << "It's a draw!\n";
                    break;
                }

                currentPlayer = 'X'; 
            }
        }
    }
};

int main() {
    TicTacToe game;
    game.play();
    return 0;
}