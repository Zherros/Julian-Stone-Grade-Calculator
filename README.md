# Grade Calculator (OOP Edition)

A C++ console application that tracks graded items (homework, quizzes, exams),
calculates points-based and weighted final grades, and persists data between sessions.
Built around an inheritance hierarchy with a menu-driven interface.

## Author
Julian Stone - COSC 1437, Spring 2026

## Description
This program takes entered grades for homework, quizzes, and exams and calculates what the overall grade would be with the given information, along with the options to undo and edit already entered assignments. This program is for people who want an easy way to calculate an overall grade for a class by entering assignments.

## Features
- Menu-driven interface (add / view / remove / calculate / exit)
- Three graded-item categories: Homework, Quiz, Exam
- Custom grading scheme: category weights + letter-grade cutoffs
- Two grade modes: points-based and weighted
- Save and load grades to/from a text file
- ANSI coloring system
- Undo function
- Edit already existing assignments
- Prevent non-numerical characters from being entered when numerical values are required

## Files
| File         | Purpose                                          |
|--------------|--------------------------------------------------|
| main.cpp     | Driver program: menu loop and orchestration     |
| GradedItem.h | Base class for all graded items                 |
| Homework.h   | Derived class - homework items                  |
| Quiz.h       | Derived class - quiz items                      |
| Exam.h       | Derived class - exam items                      |
| USER_GUIDE.md| End-user instructions                           |

## How to Build
Using g++ (Linux / macOS / WSL / MinGW):

    g++ -std=c++17 *.cpp -o GradeCalculator

## How to Run
    ./GradeCalculator        # macOS / Linux
    GradeCalculator.exe      # Windows

## Requirements
- C++17 or newer compiler (g++, clang, or MSVC)

## Course Concepts Demonstrated
Chapters 11-18 of Fundamentals of CPP Programming plus four UX enhancement sprints (Labs 19-22).
