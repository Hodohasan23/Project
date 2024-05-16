In the straightforward text-based game The Maze Game, the goal is to find the exit by navigating a maze. The game shows the current condition of the maze and gives instructions on how to move the player character around it.

How to Construct and Operate

Using Makefile to Build Open your terminal, find the project directory, and type the following command to begin building the Maze Game:

create The source files will be compiled as a result, producing the maze executable.

Managing the Game Once the game has been built, use the following command to launch it:

./maze <maze_file> The path to the maze file you wish to use for the game should be substituted for <maze_file>.

Application

After the game launches, you can move through the maze using the following controls:

The player character can be moved up, left, down, or right with the keys W, A, S, and D.
M: Show the maze as it is right now.
H: Display the instructions on the help screen.
Q: End the game now.
Memory Allocation and Cleaning

Memory is dynamically allocated for maze data structures in the Maze Game. Both the maze and each of its rows have memory allotted to them. The game has a function called freeMaze() to deallocate the memory allotted for the maze when it's no longer needed, ensuring correct memory cleanup and preventing memory leaks.

Create File Guidelines

Builds the executable maze that is the target.
clean: Gets rid of the executable for Maze and the object files.

run: Uses the default maze file to launch the maze executable.

Example

Here's an example command to build and run the Maze Game:

make
./maze Files/MyMaze.txt