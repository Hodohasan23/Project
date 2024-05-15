#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>

#define MAXIMUM_SIZE 100

typedef struct {
    char Size[MAXIMUM_SIZE][MAXIMUM_SIZE];
    int width;
    int height;
} Maze;

typedef struct {
    // Define player attributes (e.g., position)
    int x;
    int y;
} Player;

bool mazeValidation(const Maze* maze);
int loadMaze(Maze* maze, const char *filename);
bool playerMovement(Player* player, const Maze* maze, char direction);
void displayMap(const Maze* maze, const Player* player);
void locateStart(Player* player, const Maze* maze);
bool locateEnd(const Player* player, const Maze* maze);
void displayMaze(const Maze* maze);
int helpScreen();

#endif // MAZE_H

