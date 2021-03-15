// Sudoku Validator Program
// sudoku.cpp

#include <iostream>
#include <pthread.h>
#include <fstream>
#include <cstring>
#include <utility>
#include <stdlib.h>
#include <map>
using namespace std;

// Global Variables
int sudokuArray[9][9] = {};
int zeroArray[9][9]={};
int countRow = 0;
int controller = 0;
map<pair<int, int>, int> rcgMap;
map<pair<int, int>, int> fixedMap;

// HELPER FUNCTIONS

// checkRow: Checks individual rows for duplicates
bool checkRow(int row, int col) {
  bool noDuplicates = true;
  int curr_row = row;
  int curr_col = col;
  for (int i = 0; i <= 8; i++) {
    if (sudokuArray[curr_row][i] != sudokuArray[curr_row][curr_col]) {
      noDuplicates = true;
    } else if (i == curr_col) {
      noDuplicates = true;
    } else {
      noDuplicates = false;
      break;
    }
  }
  return noDuplicates;
}

// checkColumn: Checks individual columns for duplicates
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

// checkGrid: Checks individual grids for duplicates
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

// checkRows: Checks all rows and returns row errors
void * checkRows(void *arg) {
  int x = 0;
  while (1) {
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
        cout << endl;
    }
      break;
  }
  controller = 1;
  pthread_exit(NULL);
}

// checkCols: Checks all columns and returns column errors
void * checkCols(void *arg) {
  while (1) {
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
            zeroArray[i][j] = 1;
          }
        }
      }
      cout << endl;
      break;
    }
  }
  controller = 2;
  pthread_exit(NULL);
}

// checkGrids: Checks all grids and returns grid errors
void * checkGrids(void *arg) {
  while (1) {
    if (controller == 2) {
      cout << "GRID ERRORS" << endl;
      int x = 0;
      for (int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
          pair<int, int> coordinate(i,j);
          x = sudokuArray[i][j];
          if (checkGrid(i,j) == false) {
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
      cout << endl;
      break;
    }
  }
  controller = 0;
  pthread_exit(NULL);
}

// myArray: Updates the array after reading from file
void myArray(string line) {
  for (int col = 0; col < line.length(); col++) {
    sudokuArray[countRow][col] = line[col] - 48;
  }
  countRow++;
}

// printmyArray: Prints the array
void printmyArray(int arr[][9], int size) {
  for (int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      cout << arr[i][j] << " \n"[j == 8];
    }
  }
}

// readFile: Reads from file
void readFile(string fileName) {
  ifstream fileInput;
  string line = "";
  fileInput.open(fileName);
  if (!fileInput.is_open()) {
    cout << "Could not open file."<< endl;
  } else {
    while(!fileInput.eof()) {
      fileInput >> line;
      line.erase(remove(line.begin(), line.end(), ','), line.end());
      myArray(line);
    }
  }
  printmyArray(sudokuArray, 9);
}

// eraseNonRCG: Erase errors not present in all three checks (row, column, grid)
void eraseNonRCG() {
  for (auto it = rcgMap.cbegin(); it != rcgMap.cend();) {
    if (it->second != 3) {
      rcgMap.erase(it++);
    } else {
      ++it;
    }
  }
}

// isValid: Checks the associated row, column, and grid, for validity of proposed number
bool isValid(int val, int row, int col) {
  bool valid = true;

  // Check row for validity
  for (int c = 0; c < 9; c++) {
    if (sudokuArray[row][c] == val && c != col) {
      return false;
    }
  }

  // Check column for validity
  for (int r = 0; r < 9; r++) {
    if (sudokuArray[r][col] == val && r != row) {
      return false;
    }
  }

  // Check grid for validity
  for (int rg = 0; rg < 3; rg++) {
    for (int cg = 0; cg < 3; cg++) {
      if (sudokuArray[rg + row - (row % 3)][cg + col - (col % 3)] == val && ((rg + row - (row % 3)) != row) && ((cg + col - (col % 3)) != col)) {
        return false;
      }
    }
  }

  return valid;
}

// backtracking: Backtracking algorithm to solve Sudoku
bool backtracking() {
  int r;
  int c;

  if (rcgMap.size() == 0) {
    return true;
  } else {
    for(map<pair<int,int>, int>::const_iterator it = rcgMap.begin(); it != rcgMap.end(); ++it) {
      r = it->first.first;
      c = it->first.second;
      break;
    }
  }

  for (int i = 1; i <= 9; i++) {
    if (isValid(i, r, c)) {
      sudokuArray[r][c] = i;
      pair<int,int> pos(r,c);
      fixedMap[pos] = i;
      rcgMap.erase(pos);
      if (backtracking()) {
        return true;
      }
      fixedMap.erase(pos);
      rcgMap[pos] = 3;
    }
  }
  return false;
}

// printFixed: Prints out corrected solutions
void printFixed() {
  cout << "CORRECT SOLUTIONS" << endl;
  for(map<pair<int,int>, int>::const_iterator it = fixedMap.begin(); it != fixedMap.end(); ++it) {
      cout << "Row: " << (it->first.first) + 1 << "    Column: " << (it->first.second) + 1 << "    Correct Value: " << it->second << endl;
  }
}

// MAIN FUNCTION

int main(int argc, const char * argv[]) {
  pthread_t tid1, tid2, tid3;
  string fileName = "Testfile1.txt";

  cout<< "\n---------Sudoku Validator Program---------" << endl << endl;

  cout << "<A default file will be used if no input is specified.>" << endl << endl;
  cout << "Please input a file name: ";
  cin >> fileName;

  cout << "\nFile Used: " << fileName << endl;
  cout << "\nGIVEN BOARD\n" << endl;
  readFile(fileName);
  cout << endl;

  cout << "---------------------------------------" << endl << endl;
  if( pthread_create(&tid1, NULL, checkRows, NULL) != 0 )
        printf("Failed to create thread1\n");
  if( pthread_create(&tid2, NULL, checkCols, NULL) != 0 )
        printf("Failed to create thread2\n");
  if( pthread_create(&tid3, NULL, checkGrids, NULL) != 0 )
        printf("Failed to create thread3\n");

  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_join(tid3,NULL);
  cout << "---------------------------------------" << endl << endl;

  eraseNonRCG();
  backtracking();
  printFixed();
  cout << "\n---------------------------------------" << endl;
  cout << "\nVALIDATED BOARD\n" << endl;
  printmyArray(sudokuArray, 9);
  cout << endl;

  exit(0);
}
