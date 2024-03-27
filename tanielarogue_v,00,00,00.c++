#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// Constants
const int MAP_SIZE = 10;
const int MAX_ENEMIES = 3;

// Function prototypes
void initializeMap(char map[][MAP_SIZE]);
void printMap(char map[][MAP_SIZE]);
void movePlayer(char map[][MAP_SIZE], int &playerX, int &playerY);
void spawnEnemies(char map[][MAP_SIZE]);
void moveEnemies(char map[][MAP_SIZE]);
bool isGameOver(char map[][MAP_SIZE], int playerX, int playerY);

int main() {
    char map[MAP_SIZE][MAP_SIZE];
    int playerX, playerY;
    bool gameOver = false; // Flag to track game over state

    // Initialize random seed
    srand(time(0));

    // Initialize map and player position
    initializeMap(map);
    playerX = rand() % MAP_SIZE;
    playerY = rand() % MAP_SIZE;
    map[playerY][playerX] = 'P';

    // Game loop
    while (!gameOver) {
        printMap(map);
        movePlayer(map, playerX, playerY);
        if (isGameOver(map, playerX, playerY)) {
            gameOver = true; // Set game over flag
            break; // Exit loop immediately upon game over
        } else {
            spawnEnemies(map); // Spawn enemies only if game is not over
            moveEnemies(map);
        }
    }

    // Game over
    cout << "Game Over You Sucker!\n";

    return 0;
}

// Initialize the map with empty spaces
void initializeMap(char map[][MAP_SIZE]) {
    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            map[i][j] = '.';
        }
    }
}

// Print the map
void printMap(char map[][MAP_SIZE]) {
    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            cout << map[i][j] << ' ';
        }
        cout << endl;
    }
}

// Move the player
void movePlayer(char map[][MAP_SIZE], int &playerX, int &playerY) {
    char move;
    cout << "Input Your Next Move (W/A/S/D): ";
    cin >> move;

    switch (move) {
        case 'W':
        case 'w':
            if (playerY > 0) {
                map[playerY][playerX] = '.';
                playerY--;
                if (isGameOver(map, playerX, playerY)) {
                    cout << "Game Over You Sucker!\n";
                    printMap(map); // Print the final map state
                    cout << "Press any key to exit...";
                    cin.ignore(); // Clear the input buffer
                    cin.get(); // Wait for the user to press any key
                    exit(0);
                }
                map[playerY][playerX] = 'P';
            }
            break;
        case 'A':
        case 'a':
            if (playerX > 0) {
                map[playerY][playerX] = '.';
                playerX--;
                if (isGameOver(map, playerX, playerY)) {
                    cout << "Game Over You Sucker!\n";
                    printMap(map); // Print the final map state
                    cout << "Press any key to exit...";
                    cin.ignore(); // Clear the input buffer
                    cin.get(); // Wait for the user to press any key
                    exit(0);
                }
                map[playerY][playerX] = 'P';
            }
            break;
        case 'S':
        case 's':
            if (playerY < MAP_SIZE - 1) {
                map[playerY][playerX] = '.';
                playerY++;
                if (isGameOver(map, playerX, playerY)) {
                    cout << "Game Over You Sucker!\n";
                    printMap(map); // Print the final map state
                    cout << "Press any key to exit...";
                    cin.ignore(); // Clear the input buffer
                    cin.get(); // Wait for the user to press any key
                    exit(0);
                }
                map[playerY][playerX] = 'P';
            }
            break;
        case 'D':
        case 'd':
            if (playerX < MAP_SIZE - 1) {
                map[playerY][playerX] = '.';
                playerX++;
                if (isGameOver(map, playerX, playerY)) {
                    cout << "Game Over You Sucker!\n";
                    printMap(map); // Print the final map state
                    cout << "Press any key to exit...";
                    cin.ignore(); // Clear the input buffer
                    cin.get(); // Wait for the user to press any key
                    exit(0);
                }
                map[playerY][playerX] = 'P';
            }
            break;
        default:
            cout << "Invalid move!\n";
    }
}

// Spawn enemies
void spawnEnemies(char map[][MAP_SIZE]) {
    static int numEnemies = 0; // Keep track of total number of enemies

    if (numEnemies < MAX_ENEMIES) {
        int x = rand() % MAP_SIZE;
        int y = rand() % MAP_SIZE;

        if (map[y][x] == '.') {
            map[y][x] = 'E';
            numEnemies++;
        }
    }
}

// Move enemies
void moveEnemies(char map[][MAP_SIZE]) {
    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            if (map[i][j] == 'E') {
                int direction = rand() % 4; // 0: up, 1: left, 2: down, 3: right

                switch (direction) {
                    case 0:
                        if (i > 0 && map[i - 1][j] == '.') {
                            map[i][j] = '.';
                            map[i - 1][j] = 'E';
                        }
                        break;
                    case 1:
                        if (j > 0 && map[i][j - 1] == '.') {
                            map[i][j] = '.';
                            map[i][j - 1] = 'E';
                        }
                        break;
                    case 2:
                        if (i < MAP_SIZE - 1 && map[i + 1][j] == '.') {
                            map[i][j] = '.';
                            map[i + 1][j] = 'E';
                        }
                        break;
                    case 3:
                        if (j < MAP_SIZE - 1 && map[i][j + 1] == '.') {
                            map[i][j] = '.';
                            map[i][j + 1] = 'E';
                        }
                        break;
                }
            }
        }
    }
}

// Check if the game is over
bool isGameOver(char map[][MAP_SIZE], int playerX, int playerY) {
    if (map[playerY][playerX] == 'E') {
        return true; // Player encountered an enemy
    }
    return false; // Player did not encounter an enemy
}
