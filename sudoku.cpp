
#include <iostream>
#include <pthread.h>
using namespace std;
int g_sudokuArray[9][9] = {};
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

void ReadFile()
{
    // read from file
    // Beware:
      // make sure to only pass in integers
      // check when the row stops!! (Recall : array[i][j] where i is the row and j is the column. So, make sure that once you hit the end of the row, increment the i.
    // assign grid to global variable: g_sudokuArray
}


int main(int argc, const char * argv[]) {
    // STEP 1: Create threads
    pthread_t row;
    pthread_t column;
    pthread_t grid;
    
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
