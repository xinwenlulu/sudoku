#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctype.h>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!" << '\n';
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
    cout << "  +===========+===========+===========+" << '\n';
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
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

/* a Boolean function to check whether a sudoku board is completed (all positions occupied by decimal digits from 1 to 9 ) */
bool is_complete(char board[9][9]){
    for (int r=0; r<9; r++) { // rows //
        for (int c=0; c<9; c++) { // columns //
            
            if (!isdigit(board[r][c])){ //not a decimal digit: 0,1,2,3,4,5,6,7,8,9//
                return false;
            }
            
            if ( board[r][c] == '0'){ // if occupied by 0 //
                return false;
            }
            
        } // columns //
    }// rows //
    return true;
}

/* a Boolean function that places a digit onto a Sudoku board at a given position */
/* the board will be updated if placing of the digit at position is valid, and unaltered otherwise */
bool make_move(const char* position,const char digit,char board[9][9]){
    // converting position into int coordinates for easy comparison //
    int row = position[0] - 'A', column = position[1] - '1';
    
    // sanity checks //
    if (row < 0 || row > 8 || column < 0 || column > 8 ){ // position reasonable?//
        return false;
    }
    
    if (!isdigit(digit)||digit == '0'){ // illegal content for sudoku? //
        return false;
    }
    
    if (board[row][column]!='.'){ //already occupied, don't overwrite! //
        return false;
    }
    
    // continue if position is reasonable and empty and digit is legal //
    if (!is_valid(row,column,digit,board)){
        return false;
    }
    
    // update board if the move is valid (after passing all the checks) //
    board[row][column] = digit;
    return true;
}

/* a Boolean function to save the sudoku board ( in a 2D character array) to a file named filename */
bool save_board(const char* filename, char board[9][9]){
  ofstream boardTOsave(filename);
  if (boardTOsave.is_open()){
      for (int r = 0; r < 9; r++){ // rows //
          for (int c = 0; c < 9; c++){ // columns //
              boardTOsave << board[r][c];
          } // columns //
          boardTOsave << endl; // move to the next row //
      } // rows //
      boardTOsave.close();
      return true;
  }
      
  //failed to open file for writing
  return false;
}

/* a Boolean function to check whether a solution can be found for a given sudoku board */
/* updates board if solution is found */

bool solve_board(char board[9][9]){
  // base case to exit recursion //
  if (is_complete(board)){
      return true;
  }
  
  for (int r = 0; r < 9; r++){      // rows //
      for (int c = 0; c < 9; c++){  // columns //
            
            if (board[r][c]=='.'){  // if position is empty //
                //try placing digit at position//
                for (char digit = '1'; digit <= '9'; digit ++){
                    if (is_valid(r,c,digit,board)){
                        board[r][c]=digit;  // update board if valid //
                        recursion++; // increment recursion count //
                        if (solve_board(board)){ // try solving updated board //
                            return true;
                        }
                    }
                    // remove the assigned digit if the move is not valid //
                    // restore the board to its previous state //
                    // before trying the next digit//
                    board[r][c]='.';
                }
                // exhausted all possible digits and no solution //
                return false;
            }
            
      }  // columns //
  }  // rows //
    
  return false; // reached the end of the board and somehow still not completed//
}

/* helper function to check validity of move without passing position in const char */
/* assuming position valid, position empty and digit valid */
bool is_valid(int row,int column,char digit,char board[9][9]){
    
    // check row //
    for (int c = 0; c < 9; c++){
        if (board[row][c] == digit){
            return false;
        }
    }
    
    // check column //
    for (int r = 0; r < 9; r++){
        if(board[r][column] == digit){
            return false;
        }
    }
    
    //check the 3x3 sub-board //
    int row1 = row-row%3, column1 = column - column%3;
    for (int r = row1; r < row1+3; r++){ // rows //
        for (int c = column1; c < column1+3; c++){ // columns //
            if (board[r][c] == digit){
                return false;
            }
        } // rows//
    } // columns//
    
    return true;
}

/* a helper function to fetch the number of recursions excuted */
int print_recursion(){
    return recursion;
}

/* a helper function to set the recursion count back to 0 when attempting a new baord */
void reset_recursion(){
    recursion = 0;
}
