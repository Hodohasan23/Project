#!/bin/bash

# remove read permissions from this file to perfrom Bad permissions test
chmod -r Files/bad_permissions.txt

gcc mazeGame.c -o mazeGame


echo -e "~~ Maze Game Tests ~~"

echo -e "~~ File handling ~~"

# FirstMaze.txt is used to test that file loads succesfully
echo -n "Testing a succesfull file is loaded  - "
./mazeGame Files/FirstMaze.txt > tmp
if grep -q "File Files/FirstMaze.txt has been loaded successfully" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#Testing a file with invalid data 
echo -n "Testing an invalid file- "
./mazeGame Files/invalid_file.txt > tmp
if grep -q "Error: txt file is in an incorrect format" tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

# This tests if the data has missing fields, No S ( Start Point ) - bad_data_missing_s has no start point
echo -n "Testing when there is a missing starting point - "
timeout 0.2s ./mazeGame Files/Missing_end.txt > tmp
if grep -q "Error: txt file is in an incorrect format" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi

# Testing to see if there are any other characters that not the correct # S E, which would make the maze invalid the file used in test has others than the default three.
echo -n "Testing bad data whith incorrect characters - "
timeout 0.2s ./mazeGame Files/Incorrect_Characters.txt  > tmp
if grep -q "Error: txt file is in an incorrect format" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

# This tests if the data has missing fields, No E ( End Point ) - bad_data_missing_e has no end point
echo -n "Testing when there is a missing ending point - "
timeout 0.2s ./mazeGame Files/Missing_start.txt  > tmp
if grep -q "Error: txt file is in an incorrect format" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi


# This tests a the file non_existent_file.txt which does not exist or has incorrect file name
echo -n "Testing a file that has incorrect name or doesn't exist- "
./mazeGame Files/non_existent_file.txt > tmp
if grep -q "Error: Incorrect filename " tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing a file that does not exist- "
./mazeGame Files/non_existent_file.txt > tmp
if grep -q "Error: Cannot open file" tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

# Testing loading an empty maze file
echo -n "Testing loading an empty maze file - "
./mazeGame Files/empty_file.txt > tmp
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

echo -e "~~ Movement testing ~~"

#This tests movement logic if user has multiple pathways to choose from
echo -n "Testing file with multiple path ways - "
./mazeGame Files/multiple_pathways.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests movement logic if user is in a maze with a reptitive structure
echo -n "Testing file with pathways that have a repetitive structure - "
./mazeGame Files/repetitive_pathway.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests multiple different exits in file to see how mulitple wining conditions are handled
echo -n "Testing maze file with multiple exits - "
./mazeGame Files/Multiple_exits.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#Testing when a user tries to move beyond the maze structure
echo -n "Testing user attempt to move beyond the maze - "
./mazeGame Files/Beyond_edge.txt > tmp
if grep -q "Error - cant move beyond the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This test is done to simulate a scenario where user runs into a wall
echo -n "Testing when user moves into a wall - "
./mazeGame Files/Wall.txt > tmp
if grep -q "Error - User moved in to a wall (#) cannot be done" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests movement logic if user enters they key 'A' in uppercase they should move leftwards and would be displayed a success message.
echo -n "Testing leftward movement 'A' - "
echo "A" | ./mazeGame Files/Leftward.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests movement logic if user enters they key 'D' in uppercase they should move rightwards and would be displayed a success message.
echo -n "Testing rightward movement 'D' - "
echo "D" | ./mazeGame Files/Rightward.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests movement logic if user enters they key 'W' in uppercase they should move upwards and would be displayed a success message.
echo -n "Testing upward movement'W'- "
echo "W" | ./mazeGame Files/Upward.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests movement logic if user enters they key 'S' in uppercase they should move downwards and would be displayed a success message.
echo -n "Testing downward movement 'S' - "
echo "S" | ./mazeGame Files/Downward.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests movement logic if user enters they key 'a' in lowercase they should move leftwards and would be displayed a success message.
echo -n "Testing leftward movement 'a' - "
echo "a" | ./mazeGame Files/Leftward.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests movement logic if user enters they key 'd' in lowercase they should move rightwards and would be displayed a success message.
echo -n "Testing rightward movement 'd'- "
echo "d" | ./mazeGame Files/Rightward.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests movement logic if user enters they key 'w' in lowercase they should move upwards and would be displayed a success message.
echo -n "Testing upward movement 'w' - "
echo "w" | ./mazeGame Files/Upward.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests movement logic if user enters they key 's' in lowercase they should move downwards and would be displayed a success message.
echo -n "Testing downward movement 's' - "
echo "s" | ./mazeGame Files/Downward.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This is another way of testing movement where all keys regardless of case that are inputed are tested
echo -n "User inputs correct letter for movement- "
./mazeGame FirstMaze.txt < Inputs/InputsUser.txt > tmp
if grep -q "Congratulations - successfully exited the maze" tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "~~ Display of map testing ~~"

# This tests searches for for a message of map being shown when user selects key 'M' and then presents success message
echo -n "Testing Viewing of Image of Map - "
echo "M" | ./mazeGame Files/FirstMaze.txt > tmp
if grep -q "Successfully displaying image of Map" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

# This tests searches for for a message of map being shown when user selects key 'm' and then presents success message
echo -n "Testing Viewing of Image of Map - "
echo "m" | ./mazeGame Files/FirstMaze.txt > tmp
if grep -q "Successfully displaying image of Map" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


echo -e "~~ User inputs bad data ~~"

echo -n "User inputs incorrect movement key - "
echo "" | ./mazeGame > tmp
if grep -q "Error: Movement character key is invalid" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#Test if user enters incorrect key that is not 'w a s d' they key 'l' is use for this test
echo -n "User does not input anything - "
echo "l" | ./mazeGame FirstMaze.txt > tmp
if grep -q "Error: Movement character key is invalid" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "User does not input anything - "
./mazeGame FirstMaze.txt < Inputs/noInput.txt > tmp
if grep -q "Error: Movement character key is invalid" tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "~~ User inputs correct data ~~"

# Add additional tests here as your game development progresses

# adding read perms back on to bad_permissions.txt
chmod +r Files/bad_permissions.txt

# Cleanup
rm -f tmp
