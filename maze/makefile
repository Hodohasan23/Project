# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -std=c11

# Target executable
TARGET = maze

# Source files
SRCS = maze.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean the build
clean:
	rm -f $(OBJS) $(TARGET)

# Rule to run the program with a specified maze file
run: $(TARGET)
	./$(TARGET)

# This rule allows passing arguments to the `run` target
run-file: $(TARGET)
	./$(TARGET) $(file)

.PHONY: all clean run run-file

