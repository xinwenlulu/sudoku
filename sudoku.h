#ifndef SUDOKU_H
#define SUDOKU_H

void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

/* FUNCTION TO CHECK WHETHER A SUDOKU BOARD IS COMPLETE */
bool is_complete(char board[9][9]);

/* FUNCTION TO CHECK WHETHER PLACING A GIVEN DIGIT AT GIVEN POSITION ON A GIVEN SUDOKU BOARD IS VALID */
bool make_move(const char* position,const char digit,char board[9][9]);

/* FUNCTION TO SAVE A SUDOKU BOARD IN A 2D CHARACTER ARRAY TO A FILE NAMED FILENAME*/
bool save_board(const char* filename, char board[9][9]);

/* RECURSIVE FUNCTION TO SOLVE A GIVEN SUDOKU BOARD UNTIL REACHING A CONCLUSION*/
bool solve_board(char board[9][9]);

/* HELPER FUNCTION TO CHECK VALIDITY OF PLACING GIVEN DIGIT AT GIVEN POSITION ON GIVEN BOARD */
/* ASSUMES THE POSITION IS REASONABLE AND EMPTY AND THE DIGIT IS LEGAL */
bool is_valid(int row,int column,char digit,char board[9][9]);

/* FUNCTION TO FETCH THE NUMBER OF RECURSIONS EXECUTED */
int print_recursion();

/* FUNCTION TO RESET THE RECURSION COUNT TO 0 BEFORE ATTEMPTING A NEW SUDOKU */
void reset_recursion();

#endif
