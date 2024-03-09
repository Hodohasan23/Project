#!/bin/bash

echo -e "~~ Maze Game Tests ~~"

# Testing loading an empty maze file
echo -n "Testing loading an empty maze file - "
./mazeGame mazes/empty_file.txt > tmp
if grep -q "Error: File is empty" tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "~~ Argument Tests ~~"

echo -n "Testing no arguments - "
./mazeGame > tmp
if grep -q "Usage: ./mazeGame <maze_file>" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing 2 arguments - "
./mazeGame x x > tmp
if grep -q "Usage: ./mazeGame <maze_file>" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi



# Add additional tests here as your game development progresses

# Cleanup
rm -f tmp
