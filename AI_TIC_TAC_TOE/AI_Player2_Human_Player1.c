#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define SIZE 3
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

void printGrid(char grid[SIZE][SIZE]) { // grid to be used, in tic tac toe, for loops increment i and j matrices
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("    %c    ", grid[i][j]);
        }
        printf("\n");
        printf("\n");
    }
}

int MakeMove(char grid[SIZE][SIZE], char Player_entry, int keypadinput) {
    // This function attempts to place a player's symbol ('X' or 'O') on the grid based on a keypad input.
//It calculates the row and column from the keypad input and checks if the cell is already occupied.

    int row = (keypadinput - 1) / SIZE;
    int col = (keypadinput - 1) % SIZE;

    if (grid[row][col] == 'X' || grid[row][col] == 'O') {
        return 0;
    } else {
        grid[row][col] = Player_entry;
        return 1;
    }
}

int CheckWin(char grid[SIZE][SIZE]) {
//This function checks if there's a winning line (horizontal, vertical, or diagonal) on the board.

    for (int i = 0; i < SIZE; i++) {
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) {
            if (grid[i][0] == 'X') {
                return 1;
            } else if (grid[i][0] == 'O') {
                return 2;
            }
        }
    }

    for (int j = 0; j < SIZE; j++) {
        if (grid[0][j] == grid[1][j] && grid[1][j] == grid[2][j]) {
            if (grid[0][j] == 'X') {
                return 1;
            } else if (grid[0][j] == 'O') {
                return 2;
            }
        }
    }

    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
        if (grid[0][0] == 'X') {
            return 1;
        } else if (grid[0][0] == 'O') {
            return 2;
        }
    }

    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
        if (grid[0][2] == 'X') {
            return 1;
        } else if (grid[0][2] == 'O') {
            return 2;
        }
    }

    return 0;
}

int evaluateBoard(char grid[SIZE][SIZE], int depth) {
    // This function evaluates the current state of the board and returns a score.
//The score is based on who's winning and how many moves it took to reach that state.
// A positive score favors 'O' (AI), and a negative score favors 'X' (human player).

    int winner = CheckWin(grid);
    if (winner == 1) return depth - 10;
    if (winner == 2) return 10 - depth;
    return 0;
}

int minimax(char grid[SIZE][SIZE], int depth, bool isMax) {
    int score = evaluateBoard(grid, depth);

    //This is a recursive function that simulates all possible moves on the board to determine the best score for the current player.

    if (score == 10) return score;
    if (score == -10) return score;
    if (depth == 9) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (grid[i][j] != 'X' && grid[i][j] != 'O') {
                    char prev = grid[i][j];
                    grid[i][j] = 'O';
                    best = max(best, minimax(grid, depth + 1, !isMax));
                    grid[i][j] = prev;
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (grid[i][j] != 'X' && grid[i][j] != 'O') {
                    char prev = grid[i][j];
                    grid[i][j] = 'X';
                    best = min(best, minimax(grid, depth + 1, !isMax));
                    grid[i][j] = prev;
                }
            }
        }
        return best;
    }
}

int findBestMove(char grid[SIZE][SIZE]) {
  //This function determines the best move for the AI.
//It iterates over all possible moves, simulates each move, and evaluates the resulting board state using the minimax function.
//The move with the best score for the AI is chosen.


    int bestVal = 1000;
    int bestMove = -1;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] != 'X' && grid[i][j] != 'O') {
                char prev = grid[i][j];
                grid[i][j] = 'O';
                int moveVal = minimax(grid, 0, false);
                grid[i][j] = prev;

                if (moveVal < bestVal) {
                    bestMove = (i * SIZE) + j + 1;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

//Start of main routine

int main() {
    char grid[SIZE][SIZE] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };
    int keypadinput = 0;
    char Player_entry = 0;

    printf ("---TIC TAC TOE with AI--by Marcel Dorti Silva - 2023 - Player 1 - Human, Player 2 - AI\n\n");

    printGrid(grid);

    for (int i = 1; i <= 9; i++) {
        int success = 0;

        if (i % 2 == 0) {
            keypadinput = findBestMove(grid);
            if (keypadinput == -1) {
                printf("Error: AI couldn't find a valid move.\n");
                break;
            }
            Player_entry = 'O';
            success = MakeMove(grid, Player_entry, keypadinput);
            printf("AI chose position: %d\n", keypadinput);
        } else {
            while (!success) {
                char input[1000];
                printf("Player 1 (X): ");
                fgets(input, sizeof(input), stdin);
                keypadinput = atoi(input);

                if (keypadinput < 1 || keypadinput > 9) continue;

                Player_entry = 'X';
                success = MakeMove(grid, Player_entry, keypadinput);
                if (!success) {
                    printf("Invalid move. Try again.\n");
                }
            }
        }

        printGrid(grid);

        int result = CheckWin(grid);
        if (result == 1) {
            printf("Player 1 (X) wins!\n");
            break;
        } else if (result == 2) {
            printf("Player 2 (O) wins!\n");
            break;
        }
    }

    return 0;
}
