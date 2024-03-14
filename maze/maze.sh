#!/bin/bash

# remove read permissions from this file to perfrom Bad permissions test
chmod -r Files/bad_permissions.txt

gcc maze.c -o maze


echo -e "~~ Maze Game Tests ~~"

echo -e "~~ File handling ~~"

# FirstMaze.txt is used to test that file loads succesfully
echo -n "Testing a succesfull file is loaded  - "
./maze FirstMaze.txt > tmp
if grep -q "File FirstMaze.txt has been loaded successfully" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#Testing a file with invalid data 
echo -n "Testing an invalid file- "
./maze invalid_file.txt > tmp
if grep -q "Error: txt file is in an incorrect format" tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

# This tests if the data has missing fields, No S ( Start Point ) - bad_data_missing_s has no start point
echo -n "Testing when there is a missing starting point - "
timeout 0.2s ./maze Missing_end.txt > tmp
if grep -q "Error: txt file is in an incorrect format" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi

# Testing to see if there are any other characters that not the correct # S E, which would make the maze invalid the file used in test has others than the default three.
echo -n "Testing bad data whith incorrect characters - "
timeout 0.2s ./maze Incorrect_Characters.txt  > tmp
if grep -q "Error: txt file is in an incorrect format" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

# This tests if the data has missing fields, No E ( End Point ) - bad_data_missing_e has no end point
echo -n "Testing when there is a missing ending point - "
timeout 0.2s ./maze Missing_start.txt  > tmp
if grep -q "Error: txt file is in an incorrect format" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi


# This tests a the file non_existent_file.txt which does not exist or has incorrect file name
echo -n "Testing a file that has incorrect name or doesn't exist- "
./maze non_existent_file.txt > tmp
if grep -q "Error: Incorrect filename " tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing a file that does not exist- "
./maze non_existent_file.txt > tmp
if grep -q "Error: Cannot open file" tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

# Testing loading an empty maze file
echo -n "Testing loading an empty maze file - "
./maze empty_file.txt > tmp
if grep -q "Error: File is empty" tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "~~ Argument Tests ~~"

echo -n "Testing no arguments - "
./maze > tmp
if grep -q "Usage: ./maze <maze_file>" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing 2 arguments - "
./maze x x > tmp
if grep -q "Usage: ./maze <maze_file>" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "~~ Movement testing ~~"

#This tests movement logic if user has multiple pathways to choose from
echo -n "Testing file with multiple path ways - "
./maze multiple_pathways.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests movement logic if user is in a maze with a reptitive structure
echo -n "Testing file with pathways that have a repetitive structure - "
./maze repetitive_pathway.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests multiple different exits in file to see how mulitple wining conditions are handled
echo -n "Testing maze file with multiple exits - "
./maze Multiple_exits.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#Testing when a user tries to move beyond the maze structure
echo -n "Testing user attempt to move beyond the maze - "
./maze Beyond_edge.txt > tmp
if grep -q "Error - cant move beyond the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This test is done to simulate a scenario where user runs into a wall
echo -n "Testing when user moves into a wall - "
./maze Wall.txt > tmp
if grep -q "Error - User moved in to a wall (#) cannot be done" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests movement logic if user enters they key 'A' in uppercase they should move leftwards and would be displayed a success message.
echo -n "Testing leftward movement 'A' - "
echo "A" | ./maze Leftward.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests movement logic if user enters they key 'D' in uppercase they should move rightwards and would be displayed a success message.
echo -n "Testing rightward movement 'D' - "
echo "D" | ./maze Rightward.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests movement logic if user enters they key 'W' in uppercase they should move upwards and would be displayed a success message.
echo -n "Testing upward movement'W'- "
echo "W" | ./maze Upward.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests movement logic if user enters they key 'S' in uppercase they should move downwards and would be displayed a success message.
echo -n "Testing downward movement 'S' - "
echo "S" | ./maze Downward.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests movement logic if user enters they key 'a' in lowercase they should move leftwards and would be displayed a success message.
echo -n "Testing leftward movement 'a' - "
echo "a" | ./maze Leftward.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests movement logic if user enters they key 'd' in lowercase they should move rightwards and would be displayed a success message.
echo -n "Testing rightward movement 'd'- "
echo "d" | ./maze Rightward.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests movement logic if user enters they key 'w' in lowercase they should move upwards and would be displayed a success message.
echo -n "Testing upward movement 'w' - "
echo "w" | ./maze Upward.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#This tests movement logic if user enters they key 's' in lowercase they should move downwards and would be displayed a success message.
echo -n "Testing downward movement 's' - "
echo "s" | ./maze Downward.txt > tmp
if grep -q "Congratulations - succefully exited the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


echo -e "~~ Testing bad data ~~"

# Testing if the height of the file for the maze range is above the maximum 
echo -n "Testing if data is above maximum height - "
timeout 0.2s ./maze Bad_data_height_exceeds.txt > tmp
if grep -q "Error: txt file is in an incorrect format" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi
# Testing if the width of the file for the maze range is above the maximum 
echo -n "Testing if data is above the maximum width - "
timeout 0.2s ./maze Bad_data_width_exceeds.txt > tmp
if grep -q "Error: txt file is in an incorrect format" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi
# Testing if the height of the file for the maze range is below the minimum
echo -n "Testing if data is below minimum height - "
timeout 0.2s ./maze BadData_below_minHeight.txt > tmp
if grep -q "Error: txt file is in an incorrect format" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi

# Testing if the width of the file for the maze range is below the minimum
echo -n "Testing if data is below the minimum width - "
timeout 0.2s ./maze BadData_below_minWidth.txt > tmp
if grep -q "Error: txt file is in an incorrect format" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi

# Test how game handles files with varying lengths in height
echo -n "Testing if data has irregular height - "
timeout 0.2s ./maze IrregularHeight.txt > tmp
if grep -q "Error: txt file is in an incorrect format" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi

# Test how game handles files with varying lengths in width
echo -n "Testing if data has irregular width - "
timeout 0.2s ./maze IrregularWidth.txt > tmp
if grep -q "Error: txt file is in an incorrect format" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "~~ Display of map testing ~~"

# This tests searches for for a message of map being shown when user selects key 'M' and then presents success message
echo -n "Testing Viewing of Image of Map - "
echo "M" | ./maze FirstMaze.txt > tmp
if grep -q "Successfully displaying image of Map" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

# This tests searches for for a message of map being shown when user selects key 'm' and then presents success message
echo -n "Testing Viewing of Image of Map - "
echo "m" | ./maze FirstMaze.txt > tmp
if grep -q "Successfully displaying image of Map" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


echo -e "~~ User inputs bad data ~~"

echo -n "User inputs incorrect movement key - "
echo "" | ./maze > tmp
if grep -q "Error: Movement character key is invalid" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

#Test if user enters incorrect key that is not 'w a s d' they key 'l' is use for this test
echo -n "User does not input anything - "
echo "l" | ./maze FirstMaze.txt > tmp
if grep -q "Error: Movement character key is invalid" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "User does not input anything - "
./maze FirstMaze.txt < noInput.txt > tmp
if grep -q "Error: Movement character key is invalid" tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "~~ User inputs correct data ~~"

#This is another way of testing movement where all keys regardless of case that are inputed are tested
echo -n "User inputs correct letter for movement- "
./maze FirstMaze.txt < InputsUser.txt > tmp
if grep -q "Congratulations - successfully exited the maze" tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

#Test when user successfully completes maze by using correct keys
echo -n "Testing completed maze so full run - "
./maze FirstMaze.txt < Completed_15X8.txt > tmp
if grep -q "Congratulations - successfully exited the maze" tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

#Test when user successfully completes maze (15X8) by using correct keys
echo -n "Testing completed maze so full run (15X8)- "
./maze Maze_15X8.txt < Completed_15X8.txt > tmp
if grep -q "Congratulations - successfully exited the maze" tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

#Test when user successfully completes maze (20X20) by using correct keys
echo -n "Testing completed maze so full run (20X20)- "
./maze Maze_15X8.txt < Completed_20X20.txt > tmp
if grep -q "Congratulations - successfully exited the maze" tmp; then
    echo "PASS"
else
    echo "FAIL"
fi

# adding read perms back on to bad_permissions.txt
chmod +r bad_permissions.txt

# Cleanup
rm -f tmp
