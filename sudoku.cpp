#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!\n";
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+\n";
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|\n";
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

bool is_complete(const char board[9][9]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (!isdigit(board[i][j]) || board[i][j] == '0') return false;
    }
  }

  return true;
}

bool make_move(const char position[3], char digit, char board[9][9]) {
  int pos_x, pos_y, target;
  int centre_x, centre_y; // Target subgrid centre coordinates

  pos_x = position[0] - ASCII_FACTOR;
  pos_y = position[1] - '1'; // Conversion to integer and remapping 1-9 to 0-8
  target = digit - '0';
  centre_x = pos_x - (pos_x % 3) + 1; // Find subgrid centre
  centre_y = pos_y - (pos_y % 3) + 1;

  if (pos_x < 0 || pos_x > 8 || pos_y < 0 || pos_y > 8) return false; // Bounds checking
  if (target < 1 || target > 9) return false; 
  if (isdigit(board[pos_x][pos_y])) return false; // Position already filled
  
  // Digit exists in row/column
  for (int i = 0; i < 9; i++) {
    if (board[pos_x][i] == digit || board[i][pos_y] == digit) return false; 
  }

  // Digit exists in subgrid
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      if (board[centre_x + i][centre_y + j] == digit) return false;
    }
  }

  board[pos_x][pos_y] = digit;
  return true;
}

bool save_board(const char filename[], const char board[9][9]) {
  ofstream outStream;
  outStream.open(filename);

  if (!outStream.good()) return false;

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      outStream << board[i][j];
    }
    outStream << "\n";
  }

  outStream.close();
  return true;
}

bool solve_board(char board[9][9]) {
  int i = 0, j = 0;
  char digit = '1';
  char position[3];
  if (is_complete(board)) return true;

  // Find first empty square
  for (i = 0; i < 9; i++) { 
    for (j = 0; j < 9; j++) {
      if (!isdigit(board[i][j])) break;
    }
    if (j == 9) j = 8; // Reset column counter if it exceeds limits
    if (!isdigit(board[i][j])) break;
  }

  set_position(position, i, j);
  
  // Fill in with first possible number
  for (digit = '1'; digit <= '9'; digit++) {
    if (make_move(position, digit, board)) {
      if (solve_board(board)) {
        return true;
      }
      board[i][j] = '.';
    }
  }

  return false;
}

bool solve_board_info(char board[9][9], int &function_calls, int &stack_size, int &max_stack_size) {
  int i = 0, j = 0;
  char digit = '1';
  char position[3];
  if (is_complete(board)) return true;

  // Find first empty square
  for (i = 0; i < 9; i++) { 
    for (j = 0; j < 9; j++) {
      if (!isdigit(board[i][j])) break;
    }
    if (j == 9) j = 8; // Reset column counter if it exceeds limits
    if (!isdigit(board[i][j])) break;
  }

  set_position(position, i, j);
  
  // Fill in with first possible number
  for (digit = '1'; digit <= '9'; digit++) {
    if (make_move(position, digit, board)) {
      if (++stack_size > max_stack_size) { max_stack_size = stack_size; } 
      if (solve_board_info(board, ++function_calls, stack_size, max_stack_size)) {
        return true;
      }
      stack_size--;
      board[i][j] = '.';
    }
  }

  return false;
}

void set_position(char position[3], int row, int col) {
  position[0] = static_cast<char>(row + ASCII_FACTOR);
  position[1] = col + '1';
  position[2] = '\0';
}