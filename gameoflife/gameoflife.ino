#include <Gamer.h>

int gameGrid[8][8];
int sleep = 100;

Gamer gamer;

// initializes the grid randomly
void initGrid(int grid[][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            grid[i][j] = 0;
        }
    }

    // encoded glider
    grid[1][0] = 1;
    grid[0][2] = 1;
    grid[1][2] = 1;
    grid[2][2] = 1;
    grid[2][1] = 1;
}

// updates the given grid based on the rules
void updateGrid(int grid[][8]) {
    int newGrid[8][8];

    // copy old to new
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            newGrid[i][j] = grid[i][j];
        }
    }

    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
            int n = getNeighbors(i, j, grid);

            // if dead
            if (grid[i][j] == 0) {
                if (n == 3) {
                    newGrid[i][j] = 1;
                }
            }
            // if alive
            else {
                if (n < 2 || n > 3) {
                    newGrid[i][j] = 0;
                }
            }
        }
    }

    // copy new to old
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            grid[i][j] = newGrid[i][j];
        }
    }
}

// loads the grid values into the display
void loadDisplay(int grid[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (grid[i][j] == 0) {
                gamer.display[i][j] = LOW;
            }
            else {
                gamer.display[i][j] = HIGH;
            }
        }
    }
}

// returns the number of neighbors around a point
int getNeighbors(int x, int y, int arr[][8]) {
    int sum = 0;

    for (int j = (y - 1); j <= (y + 1); j++) {
        for (int i = (x - 1); i <= (x + 1); i++) {
            if (!(x == i && y == j)) {
                if (arr[((i + 8) % 8)][((j + 8) % 8)] == 1) {
                    sum++;
                }
            }
        }
    }

    return sum;
}

void setup() {
    initGrid(gameGrid);
    gamer.begin();
}

void loop() {
    updateGrid(gameGrid);
    loadDisplay(gameGrid);
    gamer.updateDisplay();

    delay(sleep);
}
