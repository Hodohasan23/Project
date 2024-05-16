Maze Game

Description

The Maze Game is a simple text-based game where the player navigates through a maze to find the exit. The game provides commands to move the player character within the maze and displays the current state of the maze.

How to Build and Run

Building with Makefile
To build the Maze Game, navigate to the project directory in your terminal and run the following command:


make
This will compile the source files and create an executable named maze.

Running the Game
After building the game, you can run it with the following command:


./maze <maze_file>
Replace <maze_file> with the path to the maze file you want to use for the game.

Usage

Once the game is running, you can use the following controls to navigate through the maze:

W, A, S, D: Move the player character up, left, down, or right, respectively.
M: Display the current state of the maze.
H: Show the help screen with instructions.
Q: Quit the game.
Memory Allocation and Cleanup

The Maze Game dynamically allocates memory for maze data structures. Memory is allocated for the maze itself as well as for each row of the maze. To ensure proper memory cleanup and prevent memory leaks, the game provides a function freeMaze() to deallocate the memory allocated for the maze when it's no longer needed.

Makefile Rules

all: Builds the target executable maze.
clean: Removes the object files and the maze executable.
run: Runs the maze executable with a default maze file.
Example

Here's an example command to build and run the Maze Game:


make
./maze Files/MyMaze.txt