#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//create Sudoku random array

int isSafe(int grid[9][9], int row, int col, int num) // check if you can really play on the next phase
{
    for(int x = 0; x <= 8; x++) {
        if(grid[row][x] == num || grid[x][col] == num)
            return 0;
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(grid[i + startRow][j + startCol] == num)
                return 0;
        }
    }
    return 1; // returns 1 if columns and rows are free
}

void shuffleArray(int array[9]) // shuffle array
{
    for(int i = 8; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int fillGrid(int grid[9][9])  // fills grid 9 x 9 with arrays
{
    for(int row = 0; row < 9; row++) {
        for(int col = 0; col < 9; col++)
            {
            if(grid[row][col] == 0)
                {
                int numbers[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                shuffleArray(numbers);

                for(int i = 0; i < 9; i++)
                    {
                    if(isSafe(grid, row, col, numbers[i])) {
                        grid[row][col] = numbers[i];
                        if(fillGrid(grid))
                            return 1;
                        grid[row][col] = 0;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

void generateSolvedGrid(int grid[9][9]) // grid with the numbers
{
    fillGrid(grid);
}

int main()  // main routine

{
    int grid[9][9] = {0}; // calls grid

    srand(time(NULL)); // Seed the random number generator

    generateSolvedGrid(grid); // number in the grid

    // Display the generated solved grid
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }

    return 0;
}

