#include <iostream>
using namespace std;

char square[10] = {'o', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

int checkwin();
void board();
int ai_move(char mark, char opponent);

int main()
{
    int player = 1, i, choice;
    char mark;

    do
    {
        board();
        player = (player % 2) ? 1 : 2;

        if (player == 1)
        {
            cout << "Player " << player << ", enter a number: ";
            cin >> choice;

            mark = 'X';  // Player 1 is always X

            if (choice == 1 && square[1] == '1')
                square[1] = mark;
            else if (choice == 2 && square[2] == '2')
                square[2] = mark;
            else if (choice == 3 && square[3] == '3')
                square[3] = mark;
            else if (choice == 4 && square[4] == '4')
                square[4] = mark;
            else if (choice == 5 && square[5] == '5')
                square[5] = mark;
            else if (choice == 6 && square[6] == '6')
                square[6] = mark;
            else if (choice == 7 && square[7] == '7')
                square[7] = mark;
            else if (choice == 8 && square[8] == '8')
                square[8] = mark;
            else if (choice == 9 && square[9] == '9')
                square[9] = mark;
            else
            {
                cout << "Invalid move! Try again.\n";
                player--; // Decrement player number to retry the move
            }
        }
        else
        {
            cout << "AI is making its move...\n";
            mark = 'O';  // AI is always O
            choice = ai_move('O', 'X');

            if (choice != 0)
                square[choice] = mark;
        }

        i = checkwin();
        player++;
    } while (i == -1);

    board();

    if (i == 1)
        cout << "==> \aPlayer " << --player << " wins!\n";
    else
        cout << "==> \aGame draw.\n";

    return 0;
}

int checkwin()
{
    // Check for winning combinations
    if (square[1] == square[2] && square[2] == square[3])
        return 1;
    else if (square[4] == square[5] && square[5] == square[6])
        return 1;
    else if (square[7] == square[8] && square[8] == square[9])
        return 1;
    else if (square[1] == square[4] && square[4] == square[7])
        return 1;
    else if (square[2] == square[5] && square[5] == square[8])
        return 1;
    else if (square[3] == square[6] && square[6] == square[9])
        return 1;
    else if (square[1] == square[5] && square[5] == square[9])
        return 1;
    else if (square[3] == square[5] && square[5] == square[7])
        return 1;
    // Check if the board is full (draw condition)
    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
             square[4] != '4' && square[5] != '5' && square[6] != '6' &&
             square[7] != '7' && square[8] != '8' && square[9] != '9')
        return 0;
    else
        return -1;
}

void board()
{
    cout << "\n\n\tTic Tac Toe\n\n";
    cout << "Player 1 (X)  -  Player 2 (O)\n\n";

    cout << "     |     |     \n";
    cout << "  " << square[1] << "  |  " << square[2] << "  |  " << square[3] << "\n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << square[4] << "  |  " << square[5] << "  |  " << square[6] << "\n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << square[7] << "  |  " << square[8] << "  |  " << square[9] << "\n";
    cout << "     |     |     \n\n";
}

int ai_move(char mark, char opponent)
{
    // Win if possible
    for (int i = 1; i <= 9; i++)
    {
        if (square[i] == i + '0')  // Check if the spot is empty
        {
            square[i] = mark;
            if (checkwin() == 1)
            {
                square[i] = i + '0';  // Revert to original
                return i;  // Return the winning move
            }
            square[i] = i + '0';  // Revert to original
        }
    }

    // Block opponent's winning move
    for (int i = 1; i <= 9; i++)
    {
        if (square[i] == i + '0')
        {
            square[i] = opponent;
            if (checkwin() == 1)
            {
                square[i] = i + '0';  // Revert to original
                return i;  // Return the blocking move
            }
            square[i] = i + '0';  // Revert to original
        }
    }

    // Take center if available
    if (square[5] == '5')
        return 5;

    // Take a corner if available
    if (square[1] == '1')
        return 1;
    if (square[3] == '3')
        return 3;
    if (square[7] == '7')
        return 7;
    if (square[9] == '9')
        return 9;

    // Take any edge
    if (square[2] == '2')
        return 2;
    if (square[4] == '4')
        return 4;
    if (square[6] == '6')
        return 6;
    if (square[8] == '8')
        return 8;

    return 0;  // No moves left (shouldn't happen if the game logic is correct)
}
