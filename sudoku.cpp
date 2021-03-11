// Sudoku Validator Program
// The Sudoku Validator Program (SVP) shall validate a 9x9 completed puzzle for correctness.
//
// Names: Clarisse Bonang, Lisa Pham, Macy Werner
// Email: bonang@chapman.edu, thupham@chapman.edu, mwerner@chapman.edu
// Course: CPSC 380-01
// Assignment: Project 2 Sudoku Validator Program

#include <iostream>
#include <pthread.h>
#include <fstream>
#include <cstring>
#include <stdlib.h>     /* atoi */
#include <map>
using namespace std;

// NOTE: may need later?
// mutex lock - allows us to aquire one thread at a time, synchronizing data
// pthread_mutex_t myMutex; // will use this later
int sudokuArray[9][9] = {};
int countRow = 0;

// Check errors in individual row
void checkRow(int row)
{
  int curr_row = row;
  map<int, string> rOccupied;
  for (int col = 0; col < 9; col++)
  {
    // check if the key exists
    if(rOccupied.find(sudokuArray[curr_row][col]) == rOccupied.end())
    {
      // cout << "Not Occupied" << endl;
      // cout << "Adding to map" << endl;
      rOccupied[sudokuArray[curr_row][col]] = "Occupied";
    }
    else
    {
      // cout << "Occupied" << endl;
      // Specs: wants the row and colum to start at 1
      cout << "Row: " << curr_row + 1 << " Column: " << col + 1 << " Value: " ;
      cout << sudokuArray[curr_row][col] << endl;
    }

  }
}

// Check errors in individual column
void checkColumn(int col)
{
  int curr_col = col;
  map<int, string> cOccupied;
  for (int row = 0; row < 9; row++)
  {
    // check if the key exists
    if(cOccupied.find(sudokuArray[row][curr_col]) == cOccupied.end())
    {
      // cout << "Not Occupied" << endl;
      // cout << "Adding to map" << endl;
      cOccupied[sudokuArray[row][curr_col]] = "Occupied";
    }
    else
    {
      // cout << "Occupied" << endl;
      // Specs: wants the row and colum to start at 1
      cout << "Row: " << row + 1 << " Column: " << curr_col + 1 << " Value: " ;
      cout << sudokuArray[row][curr_col] << endl;
    }
  }
}

// Check errors in individual sub-grids
void checkGrid(int rgrid, int cgrid)
{
  map<int, string> gOccupied;

  for (int r = 0; r < 3; r++) // row
  {
    for (int c = 0; c < 3; c++) // col
    {
      if(gOccupied.find(sudokuArray[r + rgrid][c + cgrid]) == gOccupied.end())
      {
        // cout << "Not Occupied" << endl;
        // cout << "Adding to map" << endl;
        gOccupied[sudokuArray[r + rgrid][c + cgrid]] = "Occupied";
      }
      else
      {
        // cout << "Occupied" << endl;
        // Specs: wants the row and colum to start at 1
        cout << "Row: " << r + rgrid + 1 << " Column: " << c + cgrid + 1 << " Value: " ;
        cout << sudokuArray[r + rgrid][c + cgrid] << endl;
      }
    }
  }
}

// Checks all Rows
void *checkRows(void *tRowID)
{
  int rowLine = 0;

  while (rowLine < 9)
  {
    checkRow(rowLine);
    rowLine++;
  }
  return NULL;
}

// Checks all Columns
void *checkColumns(void *tColID)
{
  int colLine = 0;

  while (colLine < 9)
  {
    checkColumn(colLine);
    colLine++;
  }
  return NULL;
}

// Checks all Grids
void *checkGrids(void *tRowID)
{
  for (int i = 0; i < 9; i += 3)
  {
    for (int j = 0; j < 9; j += 3)
    {
      checkGrid(i,j);
    }
  }
  return NULL;
}

// updates the array
void myArray(string line)
{
  for(int col = 0; col < line.length(); col++)
  {
    // assign and convert character to number
    sudokuArray[countRow][col] = line[col] - 48;
  }
  countRow++;
  //Diag:
  //cout << "row: " << countRow << endl;
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
  fileInput.open(fileName);
  if(!fileInput.is_open())
  {
    cout << "Could not open file."<< endl;
  }
  else{
    while(!fileInput.eof())
    {
      fileInput >> line;
      // Diag:
      //cout << "line " << line << endl;
      // Removes ',' from the string
      line.erase(remove(line.begin(), line.end(), ','), line.end());
      // Passes string that excludes ','
      myArray(line);

    }
  }
  printmyArray();
}

int main(int argc, const char * argv[]) {
  string fileName = "";
  fileName = "Testfile5.txt";

  pthread_t rowThread;
  pthread_t columnThread;
  pthread_t gridThread;

  cout << "---------------------------------------------" << endl;
  cout << "Sudoku Validator Program" << endl;
  cout << "File Name: " << fileName << endl << endl;
  ReadFile(fileName);

  int rowID = 1;
  int colID = 2;
  int gridID = 3;

  cout << "\nErrors Found:" << endl;

  pthread_create(&rowThread, NULL, checkRows, (void *)(size_t)rowID);
  pthread_create(&columnThread, NULL, checkColumns, (void *)(size_t)colID);
  pthread_create(&gridThread, NULL, checkGrids, (void *)(size_t)gridID);

  pthread_join(rowThread, NULL);
  pthread_join(columnThread, NULL);
  pthread_join(gridThread, NULL);


  // STEP 1: Create threads

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


  cout << endl;
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
