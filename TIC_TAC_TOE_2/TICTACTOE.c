#include<stdio.h>
#include<stdlib.h>

// program used to create a Tic-Tac-Toe Game

#define SIZE 3 // instead of addressing a global variable, let us define a type of grid for all functions used,

void printGrid(char grid[SIZE][SIZE]) // creates an array of [SIZE] x [SIZE] - which will be used in all functions of main routine
{
    for (int i = 0; i < SIZE; i++)
        {
        for (int j = 0; j < SIZE; j++)
        {
            printf("    %c    ", grid[i][j]);
        }
        printf("\n");
        printf("\n");
    }
}

int MakeMove(char grid[SIZE][SIZE], char Player_entry, int keypadinput)
{
int row = (keypadinput - 1) / SIZE;  // Convert user input to row and column
int col = (keypadinput - 1) % SIZE; // Integer division gives the row.

if (grid[row][col] == 'X' || grid[row][col] == 'O') // here the function checks if the position row, col is not already occupied by O or X
    {
        return 0; // Return 0 to indicate failure - indicates failures
    }
    else {
        grid[row][col] = Player_entry;
        return 1; // Return 1 to indicate success
}
}

int CheckWin(char grid[SIZE][SIZE]) {
    // Check for a win in each row
    for (int i = 0; i < SIZE; i++) {
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) {
            if (grid[i][0] == 'X') {
                return 1;  // Player 1 wins
            } else if (grid[i][0] == 'O') {
                return 2;  // Player 2 wins
            }
        }
    }

    // Check for a win in each column
    for (int j = 0; j < SIZE; j++) {
        if (grid[0][j] == grid[1][j] && grid[1][j] == grid[2][j]) {
            if (grid[0][j] == 'X') {
                return 1;  // Player 1 wins
            } else if (grid[0][j] == 'O') {
                return 2;  // Player 2 wins
            }
        }
    }

    // Check for a win in the diagonals
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
        if (grid[0][0] == 'X') {
            return 1;  // Player 1 wins
        } else if (grid[0][0] == 'O') {
            return 2;  // Player 2 wins
        }
    }

    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
        if (grid[0][2] == 'X') {
            return 1;  // Player 1 wins
        } else if (grid[0][2] == 'O') {
            return 2;  // Player 2 wins
        }
    }

    return 0;  // No winner
}


//Start of main rountine
int main ()
{
char grid [SIZE][SIZE]= { // allocates a number to the grid function
{'1',   '2',   '3'},
{'4',   '5',   '6'},
{'7',   '8',   '9'}
};
int keypadinput=0; // declares keypadinput in the main function
char Player_entry=0; // initiates player_entry

printf ("---TIC TAC TOE---by Marcel Dorti Silva 2023---\n\n");
printGrid(grid); //calls grid

for (int i=1; i<=9; i++) // creates loop of 9 iteractions, for players to fulfill the matrix with X or O
{
int success =0; // comes from the MakeMove Function, in which, if it returns a zero, it means one of the players tried to overwrite the other

    while (!success) // creates a loop that, while the function MakeMove does not return success, which means, no overwriting, it will keep looping for a valid non-overwriting entry.
    {

    do
     {
    char input [1000];
    printf ("Player %d: ", (i%2 == 0) ? 2 : 1);
    fgets(input, sizeof(input), stdin); // reads a line of text from standard input into input
    keypadinput = atoi(input); // converts the string to an integer
     }
         while (keypadinput < 1 || keypadinput > 9); // repeat while the input is out of range

     //printf ("Player %d: ", (i%2 == 0) ? 2 : 1); // if number is even, it is player 2, other player 1
    //scanf("%d", &keypadinput); //gets input of the keypad


    Player_entry = (i%2 == 0) ? 'O' : 'X'; // if number is even it is O, otherwise X.
    success = MakeMove(grid, Player_entry, keypadinput); // checks if MakeMove is sucessful in getting a valid entry.
    if (!success) // if not, try again
        {
        printf("Invalid move. Try again.\n");
        }
    }
    printGrid(grid); // print grid, now modified
    int result = CheckWin(grid); // Check for a winner after the move
    if (result == 1) {
        printf("Player 1 X wins!\n");
        break;  // Exit the game loop
    } else if (result == 2) {
        printf("Player 2 O wins!\n");
        break;  // Exit the game loop
    }

}


return 0;
}

