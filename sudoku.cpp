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

/* a Boolean function to check whether a sudoku board is completed (all positions occupied by digits) */
bool is_complete(char board[9][9]){
    for (int r=0; r<9; r++) { // rows //
        for (int c=0; c<9; c++) { // columns //
            if (board[r][c]=='.' || board[r][c]=='0'){
                // if not occupied by digits or 0s //
                return false;
            }
        } // columns //
    }// rows //
    return true;
}

/* a Boolean function that places a digit onto a Sudoku board at a given position */
/* the board will be updated if placing of the digit at position is valid, and unaltered otherwise */
bool make_move(const char* position,const char digit,char board[9][9]){
    // converting position into array coordinates //
    const int row = position[0] - 'A', column = position[1] - '1';
    int num = digit - '0';
    
    // check the validity of position and placing of the digit at position //
    if (row < 0 || row > 8 || column < 0 || column > 8 ){ // if position invalid //
        return false;
    }else if (num < 1 || num > 9){
        return false;
    }else if (board[row][column]!='.'){ //already occupied, don't overwrite! //
        return false;
    }else if (!is_valid(row,column,digit,board)){
        // continue if position is valid and empty //
        return false;
    }
    
    // update board if the move is valid//
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
  if (is_complete(board)){
      return true;
  }
  
  for (int r = 0; r < 9; r++){      // rows //
      for (int c = 0; c < 9; c++){  // columns //
            
            if (board[r][c]=='.'){
                //try placing digit at position//
                for (char digit = '1'; digit <= '9'; digit ++){
                    if (is_valid(r,c,digit,board)){
                        board[r][c]=digit;
                        if (solve_board(board)){
                            return true;
                        }
                    }
                    board[r][c]='.';
                }
                return false;
            }
            
      }  // columns //
  }  // rows //
  
  return false;
}

/* helper function to check validity of move without passing char parameters*/
/* assuming position valid and position empty */
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

