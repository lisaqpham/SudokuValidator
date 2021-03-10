//
//  main.cpp
//  OS_proj2
//
//  Created by cpsc on 3/9/21.
//
// Reference: https://www.tutorialspoint.com/read-file-line-by-line-using-cplusplus

#include <iostream>
#include <pthread.h>
#include <fstream>
#include <cstring>
using namespace std;
char sudokuArray[30][30] = {};
int countRow = 0;
// Check the row
void *checkRows(void *tRowID)
{
    // call checkRow
    // checkRow()
    return NULL;
}
void checkRow()
{
    // only checks one row and call it in a loop inside the thread function
    // check  duplicates
    // bool vector or array or a count. So if we get a
    //
    
    // 2,3,2 we have a 3 in row 1 and a 2 in row 3
    // create a data strucutre
}
void *checkColumns(void *tRowID)
{
    return NULL;
}
void *checkGrids(void *tRowID)
{
    return NULL;
}

// updates the array
void myArray(string line)
{
    for(int col = 0; col < line.length(); col++)
    {
        sudokuArray[countRow][col] = line[col];
    }
    countRow++;
    cout << "row: " << countRow << endl;
}
// prints the array
void printmyArray()
{
    for (int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            cout << sudokuArray[i][j] << " \n"[j == 8];
        }
    }
}
void ReadFile(string fileName)
{
    // read from file
    // Beware:
      // make sure to only pass in integers
      // check when the row stops!! (Recall : array[i][j] where i is the row and j is the column. So, make sure that once you hit the end of the row, increment the i.
    // assign grid to global variable: g_sudokuArray
    
    ifstream fileInput;
    string line = "";
    int row = 0;
    int col = 0;
    fileInput.open(fileName);
    if(!fileInput.is_open())
    {
        cout << "could not open file"<< endl;
    }
    else{
        cout << "HERE" << endl;
        while(!fileInput.eof())
        {
            fileInput >> line;
            // Diag:
            //cout << "line " << line << endl;
            line.erase(remove(line.begin(), line.end(), ','), line.end());
            myArray(line);
            
           
        }
    }
    printmyArray();
        
    
}

int main(int argc, const char * argv[]) {
    string fileName = "";
    fileName = "Testfile1.txt";
    // onFS - object of fstream to write to file
    
    // STEP 1: Create threads
    pthread_t row;
    pthread_t column;
    pthread_t grid;
    
    
    cout << "Welcome to SVP" << endl;
    cout << "Please enter the file: " << fileName << endl;
    ReadFile(fileName);
    
    // STEP 2: Read from the test file
               // call ReadFile()
    
    // STEP 3: Create the threads and call their designated functions
        // pthread_create(&threads[i], NULL, {inert function name}, (void *)i);
        
    // STEP 4: Check the row
        // checkRows
            // while loop
              // call check Row
        // checkRow
           // check if the row has any duplicates
    
    // STEP 5: Check the column
        // checkColumns
            // while loop
              // call check Column
        // checkColumn
           // check if the row has any duplicates
       

    
    return 0;
}



/*
 Meeting Notes:
 
 // Create 3 threads
 // Create 3 functions
 // Create a function that reads in the file and assign the 2 dimensional array
 // never going to write to it, just read from it
 // g_sudokuArray[9][9]
 // when parsing through the file, check when the row stops
 // makes sure it is a integer: 1-9
 //
 
 // Create a 2D array global variable
 
 // Create a function to read from the file
 // global variable
 // g_sudokuArray[9][9]
 
 
 */
