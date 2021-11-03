#ifndef SUDOKU_H
#define SUDOKU_H

const int ASCII_FACTOR = 65; // ASCII conversion factor to turn 'A' to 0

void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

/* Function to check if all squares of the board are filled in. */
bool is_complete(const char board[9][9]);

/* Function to try put a number in a specified position on the board. */
bool make_move(const char position[3], char digit, char board[9][9]);

/* Function to save board data to specified filename. */
bool save_board(const char filename[], const char board[9][9]);

/* Function to try and solve the board. */
bool solve_board(char board[9][9]);

/* Function to try and solve the board with runtime information. */
bool solve_board_info(char board[9][9], int &function_calls, int &stack_size, int &max_stack_size);

/* Function to set a char position[] based on the row and column selected. */
void set_position(char position[3], int row, int col);

#endif