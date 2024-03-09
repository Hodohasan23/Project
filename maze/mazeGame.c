#include <stdio.h>
#include <stdlib.h>

// Function to load the maze from a file
int loadMaze(char *filename) {
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
        return -1; // Indicate failure due to empty file
    }
    
    // Reset the file position indicator to the beginning of the file
    fseek(file, 0, SEEK_SET);

    // Placeholder for actual maze loading logic
    printf("Maze loaded successfully from %s\n", filename);
    
    fclose(file);
    return 0; // Indicate success
}

// Main function
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <maze_file>\n", argv[0]);
        return -1; // Indicate failure due to incorrect usage
    }
    
    char *mazeFile = argv[1];
    if (loadMaze(mazeFile) != 0) {
        // If loadMaze returns -1, an error has occurred (file not found or empty)
        return -1; // Indicate failure to load the maze
    }
    
    // Placeholder for game loop and handling user input
    printf("Game started. (Add game loop and user input handling here)\n");
    
    return 0; // Indicate success
}
