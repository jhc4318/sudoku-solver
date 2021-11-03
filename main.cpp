#include <iostream>
#include <cstdio>
#include <chrono>
#include "sudoku.h"

using namespace std;

/* Function to test make_move() and output parameter information. */
void test_move(const char position[], const char digit, char board[9][9]);

/* Function to test solve_board() and output success/failure state. */
void test_board(const char board_name[], char board[9][9]);

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============\n\n";

  cout << "Calling load_board():\n";
  load_board("easy.dat", board);

  cout << '\n';
	cout << "Displaying Sudoku board with display_board():\n";
  display_board(board);
  cout << "Done!\n\n";

  cout << "=================== Question 1 ===================\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  cout << "=================== Question 2 ===================\n\n";

  load_board("easy.dat", board);

  // Test position in bound (test I10?)
  test_move("@1", '6', board);
  test_move("A0", '6', board);
  test_move("A1", '6', board);
  test_move("J9", '8', board);
  test_move("I9", '8', board);

  // Test digit in bound
  test_move("B3", '0', board);
  test_move("B3", '1', board);
  test_move("A2", '9', board);

  // Test for digits in row/col/subgrid
  test_move("A3", '3', board);
  test_move("B9", '5', board);
  test_move("B9", '6', board);
  test_move("B9", '7', board);

  cout << "=================== Question 3 ===================\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful.\n";
  } else {
    cout << "Save board failed.\n";
  }
  cout << '\n';

  cout << "=================== Question 4 ===================\n\n";

  test_board("easy.dat", board);
  test_board("medium.dat", board);
  test_board("no-solution.dat", board);
  test_board("test1.dat", board);
  test_board("test2.dat", board);

  cout << "=================== Question 5 ===================\n\n";

  test_board("mystery1.dat", board);
  test_board("mystery2.dat", board);
  test_board("mystery3.dat", board);

  return 0;
}

void test_move(const char position[], const char digit, char board[9][9]) {
  cout << "Putting " << digit << " into " << position << " is ";
  if (!make_move(position, digit, board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << endl;
  display_board(board);
}

void test_board(const char board_name[], char board[9][9]) {
  load_board(board_name, board);
  int function_calls = 0, stack_size = 0, max_stack = 0;
  
  auto start = chrono::high_resolution_clock::now();
  if (solve_board_info(board, function_calls, stack_size, max_stack)) {
    cout << "The " << board_name << " board has a solution:" << endl;
  } else {
    cout << "A solution cannot be found for " << board_name << "." << endl;
  }
  auto finish = chrono::high_resolution_clock::now();

  display_board(board);

  chrono::duration<double> time_elapsed = finish - start;

  cout << "Function calls: " << function_calls << ", max stack size: " << max_stack << endl;
  cout << "Time elapsed: " << time_elapsed.count() << " seconds." << endl;
  cout << endl;
}