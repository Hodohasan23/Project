#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>

#define MAXIMUM_SIZE 100
#define MINIMUM_SIZE 5

#define WALL '#'
#define SPACE ' '
#define START 'S'
#define END 'E'

typedef struct {
    int x, y;
} Player;

typedef struct {
    char grid[MAXIMUM_SIZE][MAXIMUM_SIZE];
    int width, height;
} Maze;

bool mazeValidation(const Maze* maze);
int loadMaze(Maze* maze, const char *filename);
bool playerMovement(Player* player, const Maze* maze, char direction);
void displayMap(const Maze* maze, const Player* player);
void initializePlayer(const Maze* maze, Player* player);
void gameLoop(const Maze* maze, Player* player);

#endif // MAZE_H
