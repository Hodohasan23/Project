#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>

#define MAXIMUM_SIZE 100

typedef struct {
    char **Size; // This represents the layout of the maze using a 2d array
    int width;
    int height;
} Maze; //This is the structure that represents the maze

typedef struct {
    int x; //coordinates e.g (x,y)
    int y;
} Player; //This is the structure that represents the player 

//These are the functions used in maze.c
bool mazeValidation(const Maze* maze);
int loadMaze(Maze* maze, const char *filename);
bool playerMovement(Player* player, const Maze* maze, char direction);
void displayMap(const Maze* maze, const Player* player);
void locateStart(Player* player, const Maze* maze);
bool locateEnd(const Player* player, const Maze* maze);
void displayMaze(const Maze* maze);
int helpScreen();
void freeMaze(Maze* maze);

#endif // MAZE_H




