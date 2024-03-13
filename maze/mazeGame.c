#include <stdio.h>
#include <stdbool.h> // Neded to be include to do bool functions
#include <string.h>
#include <stdlib.h>

#define Minimum_size 5 
#define Maximum_size 100 


//Function prototypes

bool mazeValidation(const Mazes* mazes) {
    //First verify that dimensions of the maze are within bounds so width and length  5 <= size => 100
    // Check maze dimensions are within bounds (MIN_SIZE <= size <= MAX_SIZE)
    // Confirm there is precisely one start point ('S') AND one end point ('E')
    // Ensure there are only valid characters in each cell ('#', 'S', 'E')
    // If all conditions are satisfied True is returned else Flase is returned 
}

//Function to load the maze from a file 
//Only function partially completed to see if test script works
int loadMaze(Mazes* mazes, char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return -1; // Indicate failure to open the file
    }
    
    // Check if the file is empty
    fseek(file, 0, SEEK_END); // Move to the end of the file
    long fileSize = ftell(file); // Get the current byte offset in the file
    if (fileSize == 0) {
        printf("Error: File is empty %s\n", filename);
        fclose(file);
        return -1; 
    }
    
    // Reset the file position indicator to the beginning of the file
    fseek(file, 0, SEEK_SET);

    // Placeholder for actual maze loading logic
    printf("Maze loaded successfully from %s\n", filename);
    
    fclose(file);
    return 0; 
}

int determinePlayer(int a, int b, Player* player, Mazes* mazes ){
    //Determines players position with cooridinates x and y passed
}

void locateStart(const Player* player, Mazes* maze);{
//Starting point inside maze is found and the position of the player is initialized
//Player and maze game structure has a pointer that updates players position and point marked with 'S' is found by iterating maze grid

}
bool locateEnd(const Player* player, Mazes* maze);{
    //verifies if the point the player is moving towards is is the ending point
    //if true is returned (player reaches 'E') display success message
    //otherwise false is returned
    
}

bool PlayerMovement(Player* player, Mazes* mazes, char direction) {
    // Depending on the 'direction' the new position is calculated
    // Needs to verify new point is vaild and player hasnt moved beyond maze structure or hit a wall
    // If valid position of 'player' is updated true is returned
    //If not return false

}

void displayMap(Mazes* maze){
    //Map is shown on to screen for player
}
void mapUpdate(Mazes* maze, Player* player){
    //map is updated with and X in the current position of the player using there cooridinates
}

int displayMaze(const Mazes* mazes) {
    // Returns an integer which indicates whether maze logic was printed onto screen
    return 0; // Implies success
}

int helpScreen(){
    // Menu to help player know correct keys to press is displayed
}


// Main function
int main(int argc, char *argv[]) {

    //checks correct number of arguements
    if (argc != 2) {
        printf("Usage: %s <maze_file>\n", argv[0]);
        return -1; // Due to incorrect uusuage it fails
    }
    
    char *mazeFile = argv[1];
    if (loadMaze(mazeFile) != 0) {
        // If loadMaze returns -1, an error has occurred (file not found or empty)
        return -1; // Suggests there was failure when loading maze
    }

    // Game loop
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
                gameOver = PlayerMovement(&mazes, &player, turn);
                displayMaze(&mazes);
                break;
            case 'p':
            case 'P':
                displayMaze(&mazes);
                break;
            case 'P':
                displayMap(mazes);
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
    
    return 0; 
}
