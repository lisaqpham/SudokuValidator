# Sudoku Validator

The **Sudoku Validator Program (SVP)** shall validate a 9x9 completed puzzle for correctness.

Each column and row contains all of the digits 1-9 once.

Each of the nine 3x3 sub-grids contains all of the digits 1-9 once.

The **sudoku.cpp** program:
* Accepts as input an ASCII .txt file with the elements separated by commas and structured as a 9x9 table
* The programs runs 3 threads to check the rows, columns, and sub-grids for errors
* Returns the row, column, and value at which an error is detected
* Identifies and returns the correct solution for all detected errors
* Feedback/labels are provided throughout the program through print statements to better explain the execution

## Identifying Information

* **Names:** Clarisse Bonang, Lisa Pham, Macy Werner
* **Email:** bonang@chapman.edu, thupham@chapman.edu, mwerner@chapman.edu
* **Course:** CPSC 380-01
* **Assignment:** Project 2 Sudoku Validator Program

## Source Files  
* sudoku.cpp
* README.md

## Test Files
* Testfile1.txt
* Testfile2.txt
* Testfile3.txt
* Testfile4.txt
* Testfile5.txt

## References
* *https://www.geeksforgeeks.org/multithreading-in-cpp/*

## Known Errors
* No known errors.

## Build Insructions
* `g++ sudoku.cpp`

## Execution Instructions
* `./a.out`
