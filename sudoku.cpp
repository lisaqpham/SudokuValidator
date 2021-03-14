//
//  main.cpp
//  mutexLock
//
//  Created by cpsc on 3/11/21.
//
//#include <unistd.h.>
// https://dzone.com/articles/how-can-we-controlschedule-execution-of-threads-in
#include <iostream>
#include <pthread.h>
#include <fstream>
#include <cstring>
#include <stdlib.h>     /* atoi */
#include <map>
using namespace std;
int sudokuArray[9][9] = {};
int zeroArray[9][9]={};
int countRow = 0;
int controller = 0;
void findErrors();
void printmyArray(int arr[][9], int size);
bool checkRow(int row, int col);
bool checkColumn(int row, int col);

void * checkRows(void *arg)
{
    int x = 0;
  while(1)
  {
    if(controller == 0){
      // findErrors();
      for (int i = 0; i < 9; i++)
      {
        for(int j = 0; j < 9; j++)
        {
          x = sudokuArray[i][j];
          if (checkRow(i,j) == false){
            zeroArray[i][j] = 0;
          }
          else{
              // temporary: b/f it was = x
            zeroArray[i][j] = 1;
          }
           
        }
      }
        // Diag: check if the grid includes corrections
        printmyArray(zeroArray, 9);
    }
      break;
  }
    cout << "check rows\n" << endl;
  controller = 1;
  pthread_exit(NULL);
}

void * checkCols(void *arg)
{
  while(1)
  {
    if(controller == 1){
      int x = 0;
      for (int i = 0; i < 9; i++)
      {
        for(int j = 0; j < 9; j++)
        {
          x = sudokuArray[i][j];
          if (checkColumn(i,j) == false)
          {
             zeroArray[i][j] = 0;
          }
          else
          {
            // temporary: b/f it was = x
            zeroArray[i][j] = 1;
          }
        }
      }
        // Diag: check if the grid includes corrections
      printmyArray(zeroArray, 9);
      break;
    }
  }
  cout << "check columns\n"<< endl;
  controller = 2;
  pthread_exit(NULL);
}

void * checkGrids(void *arg)
{
  while(1)
  {
    if(controller == 2)
      break;
  }
    cout << "check grids\n" << endl;
  controller = 0;
  pthread_exit(NULL);
}

bool checkRow(int row, int col)
{
    //needs to take in exact position
      //now just checking through row to match position
      bool noDuplicates = true;
      int curr_row = row;
      int curr_col = col;
    // if the column is at position 8
  for (int i = 0; i <= 8; i++){
    
    if ( sudokuArray[curr_row][i] !=  sudokuArray[curr_row][curr_col])
        {
          noDuplicates = true;
        }
      // check if it reaches
    else if (i == curr_col)
    {
        noDuplicates = true;
    }
    else{
          noDuplicates = false;
          break;
        }
      }
    return noDuplicates;
}

bool checkColumn(int row, int col)
{
  bool noDuplicates = true;
  int curr_row = row;
  int curr_col = col;
    if(zeroArray[curr_row][curr_col] == 0){
        return noDuplicates = false;
    }
    else{
      for (int i = 0; i <= 8; i++){
        if ( sudokuArray[i][curr_col] != sudokuArray[curr_row][curr_col] ){
          noDuplicates = true;
        }
        else if (i == curr_row)
        {
            noDuplicates = true;
        }
        else
        {
          noDuplicates = false;
            break;
        }
      }
        return noDuplicates;
    }
}

bool checkGrid(int row, int col)
{
  bool noDuplicates = true;
  int curr_row = row;
  int curr_col = col;
  for (int i = 1; i <= 3; i++){
      // if the curr_col is 1,4,7 then add ( [curr_col + i])
      // if the curr_col is 3,6,9 then subtract ([curr_col - i]
      // if the curr_col is 2,5,8 then add one and subtract 1 [col + i] [col - i]
      // do something similar to the rows
    if ( sudokuArray[curr_row][i] != sudokuArray[curr_row][curr_col] )
    {
      noDuplicates = true;
    }
    else
    {
      noDuplicates = false;
    }
  }
  for (int i = 1; i <= 3; i++){
    if ( sudokuArray[curr_row + 1][curr_col + i] != sudokuArray[curr_row][curr_col] )
    {
      noDuplicates = true;
    }
    else
    {
      noDuplicates = false;
    }
  }
  for (int i = 1; i <= 3; i++){
    if ( sudokuArray[curr_row + 2][curr_col + i] != sudokuArray[curr_row][curr_col] )
    {
      noDuplicates = true;
    }
    else
    {
      noDuplicates = false;
    }
  }
    return noDuplicates;
}

//make new array with x
void findErrors(){
    int x = 0;
  for (int i = 0; i < 9; i++)
  {
    for(int j = 0; j < 9; j++)
    {
      x = sudokuArray[i][j];
      if (checkRow(i,j) == false){
        zeroArray[i][j] = 0;
      }
      //else if (checkColumn(i,j) == false) {
         // zeroArray[i][j] = 0;
      //}
        /*
      else if (checkGrid(i,j) == false){
        zeroArray[i][j] = 0;
      }
       */
      else{
          // temporary: b/f it was = x
        zeroArray[i][j] = 1;
      }
       
    }
  }
    // Diag: check if the grid includes corrections
    printmyArray(zeroArray, 9);
    
}


//myArray(): updates the array after reading from file
void myArray(string line)
{
  for(int col = 0; col < line.length(); col++)
  {
    // assign and convert character to number
    sudokuArray[countRow][col] = line[col] - 48;
  }
  countRow++;
}

//printmyArray(): prints the array
void printmyArray(int arr[][9], int size)
{
  for (int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
    {
      cout << arr[i][j] << " \n"[j == 8];
    }
  }
}

//ReadFile(): reads from file
void ReadFile(string fileName)
{
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
  printmyArray(sudokuArray, 9);
}

int main(int argc, const char * argv[])
{
  pthread_t tid1, tid2, tid3;
  string fileName = "";
  fileName = "Testfile5.txt";
  printf("Sudoku Validator Program");
  cout << "File Name: " << fileName << endl;
  ReadFile(fileName);
    
    
  printf("Before creating the threads\n");
  if( pthread_create(&tid1, NULL, checkRows, NULL) != 0 )
        printf("Failed to create thread1\n");
  if( pthread_create(&tid2, NULL, checkCols, NULL) != 0 )
        printf("Failed to create thread2\n");
   //usleep(3);
  if( pthread_create(&tid3, NULL, checkGrids, NULL) != 0 )
        printf("Failed to create thread3\n");
 
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_join(tid3,NULL);
  //usleep(10);
 exit(0);
}
