#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to validate the maze according to the given specifications
bool mazeValidation(const Maze* maze) {
    int startCount = 0;
    int endCount = 0;

    for (int i = 0; i < maze->height; i++) {
        // Check if all rows are of the same length
        if (strlen(maze->Size[i]) != maze->width) {
            printf("Row %d length mismatch\n", i);
            return false; // All rows must be the same length
        }
        for (int j = 0; j < maze->width; j++) {
            char c = maze->Size[i][j];
            if (c == 'S') startCount++;
            else if (c == 'E') endCount++;
            else if (c != '#' && c != ' ' && c != 'S' && c != 'E') {
                printf("Invalid character %c at row %d, col %d\n", c, i, j);
                return false; // Invalid character
            }
        }
    }

    // There must be exactly one start and one end point
    if (startCount != 1 || endCount != 1) {
        printf("Start points: %d, End points: %d\n", startCount, endCount);
        return false;
    }

    return true;
}

// Function to load the maze from a file
int loadMaze(Maze* maze, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return 2; // File error
    }

    // Check if the file is empty
    fseek(file, 0, SEEK_END); // Move to the end of the file
    long fileSize = ftell(file); // Get the current byte offset in the file
    if (fileSize == 0) {
        printf("Error: File is empty %s\n", filename);
        fclose(file);
        return 2; 
    }
    fseek(file, 0, SEEK_SET); // Move back to the beginning of the file

    char line[MAXIMUM_SIZE + 2];
    int lineCount = 0;

    while (fgets(line, sizeof(line), file) && lineCount < MAXIMUM_SIZE) {
        line[strcspn(line, "\n")] = '\0'; // Remove the newline character
        if (strlen(line) > 0) {
            strcpy(maze->Size[lineCount], line);
            lineCount++;
        }
    }

    maze->height = lineCount;
    maze->width = strlen(maze->Size[0]); // Assuming all lines are of equal length

    fclose(file);

    if (!mazeValidation(maze)) {
        printf("Error: txt file is in an incorrect format\n");
        return 3; // Invalid maze
    }

    printf("File %s has been loaded successfully\n", filename);
    return 0; // Success
}

// Function to move the player
bool playerMovement(Player* player, const Maze* maze, char direction) {
    int newX = player->x;
    int newY = player->y;

    switch (direction) {
        case 'W':
        case 'w':
            newY--;
            break;
        case 'A':
        case 'a':
            newX--;
            break;
        case 'S':
        case 's':
            newY++;
            break;
        case 'D':
        case 'd':
            newX++;
            break;
        default:
            printf("Error: Movement character key is invalid\n");
            return false;
    }

    if (newX < 0 || newX >= maze->width || newY < 0 || newY >= maze->height || maze->Size[newY][newX] == '#') {
        printf("Error: Movement is invalid\n");
        return false;
    }

    player->x = newX;
    player->y = newY;

    if (maze->Size[newY][newX] == 'E') {
        printf("Congratulations - successfully exited the maze\n");
        return true; // Game over
    }

    return false;
}

// Function to display the map
void displayMap(const Maze* maze, const Player* player) {
    printf("\n");
    for (int i = 0; i < maze->height; i++) {
        for (int j = 0; j < maze->width; j++) {
            if (i == player->y && j == player->x) {
                printf("X");
            } else {
                printf("%c", maze->Size[i][j]);
            }
        }
        printf("\n");
    }
}

// Function to locate the start position of the player
void locateStart(Player* player, const Maze* maze) {
    for (int i = 0; i < maze->height; i++) {
        for (int j = 0; j < maze->width; j++) {
            if (maze->Size[i][j] == 'S') {
                player->x = j;
                player->y = i;
                return;
            }
        }
    }
}

// Function to check if the player has reached the end
bool locateEnd(const Player* player, const Maze* maze) {
    return maze->Size[player->y][player->x] == 'E';
}

// Function to display the maze
void displayMaze(const Maze* maze) {
    printf("Displaying maze:\n");
    for (int i = 0; i < maze->height; i++) {
        printf("%s\n", maze->Size[i]);
    }
}

// Function to display the help screen
int helpScreen() {
    printf("Help screen\n");
    return 0;
}

// Main function
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <maze_file>\n", argv[0]);
        return 1; // Argument error
    }

    Maze maze; // Assuming maze is a single Maze structure
    Player player;

    int result = loadMaze(&maze, argv[1]);
    if (result != 0) {
        return result; // Return the error code from loadMaze
    }

    locateStart(&player, &maze);

    // Maze game loop
    char turn;
    bool EndOfGame = false;
    while (!EndOfGame) {
        printf("To move in different directions in maze press keys WASD, press M to display map, get help with H, end game with Q: ");
        scanf(" %c", &turn);

        switch (turn) {
            case 'W':
            case 'A':
            case 'S':
            case 'D':
            case 'w':
            case 'a':
            case 's':
            case 'd':
                EndOfGame = playerMovement(&player, &maze, turn);
                if (!EndOfGame) {
                    displayMaze(&maze);
                }
                break;
            case 'm':
            case 'M':
                displayMap(&maze, &player);
                break;
            case 'h':
            case 'H':
                helpScreen();
                break;
            case 'q':
            case 'Q':
                printf("Ending game.\n");
                EndOfGame = true;
                break;
            default:
                printf("Character is invalid. For further help press 'H'.\n");
        }
    }

    return 0;
}

