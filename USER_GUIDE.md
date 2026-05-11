## Introduction:
This is a program that takes entered grades for homework, quizzes, and exams and calculates what the overall grade would be with the given information, along with having the options to undo and edit already entered assignments.

## Getting Started:
In order to properly build the program, use g++ for Linux, MacOs, Wsl, and MinGW: g++ -std=c++17 *.cpp -o GradeCalculator
As for running it, use ./GradeCalculator for MacOs / Linux, and GradeCalculator.exe for Windows

## Menu Walkthrough
1. Set Grading Scheme ||Allows the user to set percentage weights for each assignment category, along with minimum requirements for each letter grade||
3. Add Graded Item ||Allows the user to add assignments, total points possible, and points earned into the program||
4. View All Items ||Shows all of the currently listed assignments||
5. Edit Item ||Allows the user to edit a previously entered assignment
6. Remove Item ||Removes a specific item from the list||
7. Calculate Grade (Points-Based) ||Calculates the overall grade based on the total number of points and total number of points earned|| 
8. Calculate Grade (Weighted) ||Calculates the overall grade based on percentage||
9. Undo Last Action ||Undoes the last action done by the user||
0. Exit ||Exits the program||

## Sample Session:
