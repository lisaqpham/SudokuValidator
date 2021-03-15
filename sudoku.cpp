#include <iostream>
#include <pthread.h>
#include <fstream>
#include <cstring>
#include <utility>
#include <stdlib.h>     /* atoi */
#include <map>
using namespace std;

int sudokuArray[9][9] = {};
int zeroArray[9][9]={};
int countRow = 0;
int controller = 0;
void printmyArray(int arr[][9], int size);
bool checkRow(int row, int col);
bool checkColumn(int row, int col);
bool checkGrid(int row, int col);
map<pair<int,int>, int> rcgMap;

void * checkRows(void *arg) {
  int x = 0;
  while(1) {
    if (controller == 0) {
      cout << "ROW ERRORS" << endl;
      for (int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
          pair<int, int> coordinate(i,j);
          x = sudokuArray[i][j];
          if (checkRow(i,j) == false) {
            if (rcgMap[coordinate] >= 1) {
              rcgMap[coordinate]++;
            } else {
              rcgMap[coordinate] = 1;
            }
            cout << "Row: " << i + 1 << "    Column: " << j + 1 << "    Wrong Value: " << sudokuArray[i][j] << endl;
            zeroArray[i][j] = 0;
          } else {
            zeroArray[i][j] = 1;
          }
        }
      }
        //printmyArray(zeroArray, 9);
        cout << endl;
    }
      break;
  }
  controller = 1;
  pthread_exit(NULL);
}

void * checkCols(void *arg) {
  while(1) {
    if (controller == 1) {
      cout << "COLUMN ERRORS" << endl;
      int x = 0;
      for (int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
          pair<int, int> coordinate(i,j);
          x = sudokuArray[i][j];
          if (checkColumn(i,j) == false) {
            if (rcgMap[coordinate] >= 1) {
              rcgMap[coordinate]++;
            } else {
              rcgMap[coordinate] = 1;
            }
            cout << "Row: " << i + 1 << "    Column: " << j + 1 << "    Wrong Value: " << sudokuArray[i][j] << endl;
            zeroArray[i][j] = 0;
          } else {
            // temporary: b/f it was = x
            zeroArray[i][j] = 1;
          }
        }
      }
      //printmyArray(zeroArray, 9);
      cout << endl;
      break;
    }
  }
  controller = 2;
  pthread_exit(NULL);
}

void * checkGrids(void *arg) {
  while(1) {
    if (controller == 2) {
      cout << "GRID ERRORS" << endl;
      int x = 0;
      for (int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
          pair<int, int> coordinate(i,j);
          x = sudokuArray[i][j];
          if (checkGrid(i,j) == false) {
            //cout << "Row: " << i << " Col: " << j << endl;
            if (rcgMap[coordinate] >= 1) {
              rcgMap[coordinate]++;
            } else {
              rcgMap[coordinate] = 1;
            }
            cout << "Row: " << i + 1 << "    Column: " << j + 1 << "    Wrong Value: " << sudokuArray[i][j] << endl;
            zeroArray[i][j] = 0;
          } else {
            // temporary: b/f it was = x
            zeroArray[i][j] = 1;
          }
        }
      }
      //printmyArray(zeroArray, 9);
      cout << endl;
      break;
    }
  }
  controller = 0;
  pthread_exit(NULL);
}

bool checkRow(int row, int col) {
  //needs to take in exact position
  //now just checking through row to match position
  bool noDuplicates = true;
  int curr_row = row;
  int curr_col = col;
  // if the column is at position 8
  for (int i = 0; i <= 8; i++) {
    if (sudokuArray[curr_row][i] != sudokuArray[curr_row][curr_col]) {
      noDuplicates = true;
    } else if (i == curr_col) {    // check if it reaches
      noDuplicates = true;
    } else {
      noDuplicates = false;
      break;
    }
  }
  return noDuplicates;
}

bool checkColumn(int row, int col) {
  bool noDuplicates = true;
  int curr_row = row;
  int curr_col = col;
    for (int i = 0; i <= 8; i++) {
      if (sudokuArray[i][curr_col] != sudokuArray[curr_row][curr_col]) {
        noDuplicates = true;
      } else if (i == curr_row) {
        noDuplicates = true;
      } else {
        noDuplicates = false;
        break;
      }
    }
    return noDuplicates;
}

bool checkGrid(int row, int col) {
  bool noDuplicates = true;
  int curr_row = row;
  int curr_col = col;

    for (int r = 0; r < 3; r++) {
      for (int c = 0; c < 3; c++) {
        if (((r + curr_row - (curr_row % 3)) == curr_row) && (c + curr_col - (curr_col % 3) == curr_col)) {
          noDuplicates = true;
        } else if ((sudokuArray[r + curr_row - (curr_row % 3)][c + curr_col - (curr_col % 3)]) != (sudokuArray[curr_row][curr_col])) {
          noDuplicates = true;
        } else {
          return noDuplicates = false;
        }
      }
    }
    return noDuplicates;

}

//myArray(): updates the array after reading from file
void myArray(string line) {
  for (int col = 0; col < line.length(); col++) {
    // assign and convert character to number
    sudokuArray[countRow][col] = line[col] - 48;
  }
  countRow++;
}

//printmyArray(): prints the array
void printmyArray(int arr[][9], int size) {
  for (int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      cout << arr[i][j] << " \n"[j == 8];
    }
  }
}

//readFile(): reads from file
void readFile(string fileName) {
  ifstream fileInput;
  string line = "";
  fileInput.open(fileName);
  if (!fileInput.is_open()) {
    cout << "Could not open file."<< endl;
  } else {
    while(!fileInput.eof()) {
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

void backtracking() {
  pair<int, int> coordinate(0,0);
  cout << rcgMap[coordinate] << endl;
}

int main(int argc, const char * argv[]) {
  pthread_t tid1, tid2, tid3;
  string fileName = "";
  fileName = "Testfile4.txt";
  cout<< "\nSudoku Validator Program" << endl;
  cout << "File Name: " << fileName << endl << endl;
  readFile(fileName);
  cout << endl;

  //printf("Before creating the threads\n");
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
