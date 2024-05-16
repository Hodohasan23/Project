
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Including Bool.h to do Bool functions
#include <stdbool.h>


// Defining the constants
#define MAX_SIZE  100
#define MIN_SIZE  5
#define EXIT_SUCCESS 0
#define EXIT_ARG_ERROR 1
#define EXIT_FILE_ERROR 2
#define EXIT_MAZE_ERROR 3


// Struct to hold information about the Maze
typedef struct 
{
    int startPoint_x;
    int startPoint_y;
    // Pointer to pointer for the dynamic 2d array
    char **mazeGrid ;
    int width, length;

}Maze;

// Struct to hold information about the Gamer
typedef struct
{
    int x, y;

} Gamer;


/**
 * @brief Sets the Players position based on the coordinates supplied to it 
 *
 * @param x The X - Coordinate
 * @param y The Y - Coordinate
 * @param gamer The pointer to the gamer to change the Coordinates
 * @param firstTime If 1 it is first time, 0 is for any other time
 */
void setPlayerPosition(int x, int y, Maze *maze, Gamer *gamer, int firstTime){
    
    if (gamer != NULL) {

        gamer->x = x;
        gamer->y = y;

        // If its the first time setting then it sets it in Maze struct
        if (firstTime == 1){
            maze->startPoint_x = gamer->x ;
            maze->startPoint_y = gamer->y ;
        }
    }   
}


/**
 * @brief Checks if it is a valid character allowed within the maze
 *
 * @param c The current Character of the maze
 * @return True if it is allowed, False if not 
 */
bool isValidCharacter(char c) {

    // Returns true if acceptable character
    return c == 'S' || c == 'E' || c == '#' || c == ' ' || c == '\n';
}


/**
 * @brief Checks if the maze is acceptable, Consistent Heights and Widths within a Correct Range andn Has all and only the needed characters
 *
 * @param filename Pointer to the file to be checked
 * @return True if it is allowed, False if not 
 */
bool checkMaze(const char *filename){

    // Setup Variables
    FILE *file;
    char buffer[1024];
    int lineLength = 0;
    int currentLength;
    int lineNumber = 0;
    bool consistent = true;
    bool withinBounds = true;
    bool validCharacters = true;
    bool sFound = false;
    bool eFound = false;

    
    file = fopen(filename, "r");

    while (fgets(buffer, sizeof(buffer), file)) {

        // Remove the newline character at the end if it exists
        buffer[strcspn(buffer, "\n")] = 0;
        currentLength = strlen(buffer);

        // Check each character for validity
        for (int i = 0; i < currentLength; i++) {
            if (!isValidCharacter(buffer[i])) {
                validCharacters = false;
                break;
            }

            // Check if they found Start Point
            if ((buffer[i] == 'S') && sFound == false){
                sFound = true;
            }

            // Check if they find the End Point
            if ((buffer[i] == 'E') && eFound == false){
                eFound = true;
            }
        }
        // No need to check again if any violation found
        if (!validCharacters) {
            break;
        }
        if (lineNumber == 0) {
            // Set the initial line length
            lineLength = currentLength;  
        } else if (lineLength != currentLength) {
            // Set to false if any line length differs
            consistent = false;
            // No need to read further if inconsistency is found 
            break;  
        }

        // Increment the line counter
        lineNumber++;  
    }

    fclose(file);

    // Check the dimensions are within the specified bounds
    if (lineLength < MIN_SIZE || lineLength > MAX_SIZE || lineNumber < MIN_SIZE || lineNumber > MAX_SIZE) {
        withinBounds = false;
    }

    // Return true if the file is consistent and within bounds and All characters found and valid , else false
    return consistent && withinBounds && validCharacters && sFound && eFound ;

}


/**
 * @brief Checks if file exists and isnt empty, First round of checks before Checking the Maze
 *
 * @param filename the pointer to the file to be checked
 * @return True if it is allowed, False if not 
 */
bool startCheckMaze(const char *filename){

    FILE *file;
    file = fopen(filename, "r");

    if ( file == NULL){
        perror("the file does not exist please try again ");
        // Return false if file does not exist
        return false; 
        fclose(file);
    } else {
        // Move the file pointer to the end of the file
        fseek(file, 0, SEEK_END);

        // Check the position, which is the size of the file
        long fileSize = ftell(file);

        if (fileSize == 0) {
            printf("File '%s' is empty.\n", filename);
            fclose(file);
            // Return false if file is empty
            return false; 
        }else{
            // Return true if Validation passes
            return true;
        } 
    }
}


/**
 * @brief Checks if the file is allowed, by splitting up the tasks into 2
 *
 * @param filename The pointer to the file to be checked
 * @return True if it is allowed, False if not 
 */
bool checkFile(const char *filename){
    
    // Get values of both checks for validation
    bool firstCheck = startCheckMaze(filename);
    bool secondCheck = checkMaze(filename);

    // Exit with error code if validation fails
    if (firstCheck == false){
        // File Check
        exit(EXIT_FILE_ERROR);
    }

    if (secondCheck == false){
        // Maze Check
        exit(EXIT_MAZE_ERROR);
    }

    // If both true return true else false
    return firstCheck && secondCheck ;
    
}


/**
 * @brief Reads in the maze and assigns attributes to both structs
 *
 * @param maze The pointer to the maze to be initialised
 * @param filename The pointer to the file for the maze to be read from 
 * @param gamer the pointer to the gamer to be initialised
 */
void readMaze(Maze *maze, const char *filename, Gamer *gamer){

    // Call Checkfile to see if file meets the minimum requirements to proceed
    checkFile(filename);
    FILE *file = fopen(filename, "r");
    
    // Initialise variable to Loop
    char buffer[MAX_SIZE + 1];  
    int y = 0;

    // Read file line and assing each character to 2d Array
    while (fgets(buffer, sizeof(buffer), file) && y < maze->length) {

        // Remove the newline character
        buffer[strcspn(buffer, "\n")] = '\0'; 

        // Length of line is width of Maze 
        int lineLength = strlen(buffer);
        // Iterate over each character in the line
        for (int x = 0; x < lineLength && x < MAX_SIZE; x++) {
            maze->mazeGrid[y][x] = buffer[x];
            if (maze->mazeGrid[y][x] == 'S'){
                // calling setPlayerPosition to set start Point
                setPlayerPosition(x,y,maze,gamer,1); 
            }
        }
        y++;
    }
    fclose(file);

}


/**
 * @brief Free the allocated memory to the Maze Struct
 *
 * @param maze The pointer to the maze to be freed
 */
void freeMaze(Maze *maze) {
    // Frees every single Point and row
    if (maze) {
        for (int i = 0; i < maze->length; i++) {
            free(maze->mazeGrid[i]);
        }
        free(maze->mazeGrid);
    }
}


/**
 * @brief Sets the Width and length of the maze ready for memeory allocation
 *
 * @param maze The pointer to the Maze for memory to be allocated to
 * @param filename The pointer to the file to be looped through
 */
void setLengthWidth(Maze *maze, const char *filename){

    // Open the file to be read
    FILE *file = fopen(filename, "r");
    if ( file == NULL){
        perror("the file does not exist please try again");
        exit(EXIT_FILE_ERROR);
    }
    char buffer[MAX_SIZE + 1];  // Buffer to hold each line
    int y = 0;

    // Loop through file to find the width and length of the maze to dynamically allocate the memory
    while (fgets(buffer, sizeof(buffer), file) && y < MAX_SIZE) {
        // Removing newline character
        buffer[strcspn(buffer, "\n")] = '\0';  
        int lineLength = strlen(buffer);
        if ( y== 0 ){
            // Assign width using pointers
            maze->width = lineLength;
        }
        y++;
    }
    // Assign length using pointers
    maze->length = y ; 
    fclose(file);
}


/**
 * @brief Creates the maze and Allocates memory dynamically to the 2d grid
 *
 * @param maze The pointer to the Maze for memory to be allocated to
 */
void createMaze(Maze *maze){

    // Allocate the maze grid dynamically as it can vary in size, this is for the length
    maze->mazeGrid = malloc(maze->length * sizeof(char*));
    if (maze->mazeGrid == NULL) {
        fprintf(stderr, "Failed to allocate memory for maze grid\n");
        // Cleanup if error occurs
        free(maze);
        exit(EXIT_MAZE_ERROR);
    }

    // This is for allocating memory for the width, dynamically
    for (int i = 0; i < maze->length; i++) {
        maze->mazeGrid[i] = malloc((maze->width + 1) * sizeof(char)); // +1 for '\0'
        if (maze->mazeGrid[i] == NULL) {
            fprintf(stderr, "Failed to allocate memory for grid row %d\n", i);
            // Cleanup previously allocated rows by freeing the memory if error occurs
            for (int j = 0; j < i; j++) {
                free(maze->mazeGrid[j]);
            }
            free(maze->mazeGrid);
            free(maze);
            exit(EXIT_MAZE_ERROR);
        }
    }
}


/**
 * @brief Prints the Maze in a grid format
 *
 * @param maze The pointer to the Maze to be printed
 * @param gamer The pointer to the gamers current location
 */
void printMaze(const Maze *maze, const Gamer *gamer) {

    // New leading line
    printf("\n");  

    for (int i = 0; i < maze->length; i++) {
        for (int j = 0; j < maze->width; j++) {
            // Check for player Position is on the Spot or not
            if (i == gamer->y && j == gamer->x) {
                printf("X");  
            } else {
                printf("%c", maze->mazeGrid[i][j]);  
            }
        }
        // Each row on a newline
        printf("\n");  
    }
}


/**
 * @brief Validates the Movement to see if the next position is allowed
 *
 * @param maze The pointer to the Maze to find the future position
 * @param x The x coordinate of the future position
 * @param y the y coordinate of the future position
 * @return True if possible to move false if not 
 */
bool validateMovement(Maze *maze, int x, int y){

    // If the user is trying to move beyond the edges
    if (x < 0 || x >= maze->width || y < 0 || y >= maze->length){
        printf("You cannot move this way, you cannot go beyond the edges - Please try again\n");
        // Return False as failiure
        return false;
    }

    // Movement depending on future position
    char future_pos = maze->mazeGrid[y][x];
    switch (future_pos){
        // If it is a Wall
        case '#':
            printf("Cannot move into a wall, # - Please try again \n");
            return false;
            break;
        // If it is the End Point
        case 'E':
            printf("Congratulations You have reached the end point and won the game !! \n");
            // Free memory if End point is found
            freeMaze(maze);
            exit(EXIT_SUCCESS);
            return false;
        // If it is a space and a legal movement
        case ' ':
            return true;
            break;
    }

    // Incase if all fails
    return false ;
}


/**
 * @brief Moves the Player and Validates the movement in a given direction
 *
 * @param maze The pointer to the Maze to be moved
 * @param gamer The pointer to the gamers current location
 * @param movement The direction in which the user wants to miove
 */
void movePlayer(Maze *maze, Gamer *gamer, char movement){

    // Setup variables
    int new_x = gamer->x;
    int new_y = gamer->y;
    bool validatedMovement = false;

    // Change in coordinates depending on input
    switch(movement){
        case 'W':
            new_y = gamer->y - 1;
            break;
        case 'A':
            new_x = gamer->x - 1 ;
            break;
        case 'S':
            new_y = gamer->y + 1;
            break;
        case 'D':
            new_x = gamer->x + 1 ;
            break;
    }

    // Validation to check future movement
    validatedMovement = validateMovement(maze, new_x, new_y);
    if(validatedMovement){
        // Complete the move
        setPlayerPosition(new_x, new_y, maze, gamer, 0);
    }
}


int main(int argc, char *argv[]){

    char userChar ;

    // Checking for correct number of command-line arguments
    if (argc != 2){
        printf("Usage: Maze <filename>");
        return EXIT_ARG_ERROR;
    }
    
    // we first allocate memory for the Maze and gamer structs
    Maze maze;
    Gamer gamer ;

    // Find out width and length to allocate dynamically
    setLengthWidth(&maze, argv[1]); 
    createMaze(&maze);

    // Call read maze to read in the maze and validate to setup the game
    readMaze(&maze, argv[1], &gamer);

    // Function will set up the game then the player will be requested to play
    // Will keep running until program quits
    while ( true )
    {
        // Print options for movement 
        printf("\nPlease enter W - A - S - D - M - Q(quit)");
        scanf(" %c", &userChar);

        // for movement based on input
        switch (userChar) {
            case 'w':
            case 'W':
                movePlayer(&maze, &gamer, 'W');
                break;
            case 'a':
            case 'A':
                movePlayer(&maze, &gamer, 'A');
                break;
            case 's':
            case 'S':
                movePlayer(&maze, &gamer, 'S');
                break;
            case 'd':
            case 'D':
                movePlayer(&maze, &gamer, 'D');
                break;
            case 'm':
            case 'M':
                printMaze(&maze, &gamer);
                break;
            case 'q':
            case 'Q':
                freeMaze(&maze);
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("Error\n");

        }
    }
    
    // Free allocated memory for Maze
    freeMaze(&maze);
    return EXIT_SUCCESS ;


    
}