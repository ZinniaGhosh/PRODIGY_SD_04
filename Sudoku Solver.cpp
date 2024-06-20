#include <iostream>
using namespace std;

// Size of the Sudoku grid (9x9)
const int N = 9;

// Function prototypes
bool findEmptyLocation(int grid[N][N], int& row, int& col);
bool isValid(int grid[N][N], int row, int col, int num);
bool solveSudoku(int grid[N][N]);
void printGrid(int grid[N][N]);

int main() {
    // Example Sudoku grid (0 represents empty cells)
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid)) {
        cout << "Sudoku solved successfully:\n";
        printGrid(grid);
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}

// Function to find an empty location in the grid
bool findEmptyLocation(int grid[N][N], int& row, int& col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Function to check if it's valid to place 'num' at grid[row][col]
bool isValid(int grid[N][N], int row, int col, int num) {
    // Check row constraint
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num) {
            return false;
        }
    }

    // Check column constraint
    for (int i = 0; i < N; i++) {
        if (grid[i][col] == num) {
            return false;
        }
    }

    // Check 3x3 sub-grid constraint
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (grid[i][j] == num) {
                return false;
            }
        }
    }

    return true;
}

// Main function to solve Sudoku using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // If there is no empty location, Sudoku is solved
    if (!findEmptyLocation(grid, row, col)) {
        return true; // All cells are filled
    }

    // Try numbers 1 to 9
    for (int num = 1; num <= 9; num++) {
        // Check if num can be placed at grid[row][col]
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;

            // Recursively solve the rest of the grid
            if (solveSudoku(grid)) {
                return true; // If successful, return true
            }

            // If placing num leads to an invalid solution, backtrack
            grid[row][col] = 0;
        }
    }

    return false; // Backtrack
}

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}
