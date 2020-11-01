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
    bool complete = true;
    for (int r=0; r<9; r++) { // rows //
        for (int c=0; c<9; c++) { // columns //
            if (board[r][c]=='.' || board[r][c]=='0'){
                // if not occupied by digits or 0s //
                complete = false;
                break;
            }
        } // columns //
    }// rows //
    return complete;
}

/* a Boolean function that places a digit onto a Sudoku board at a given position */
/* the board will be updated if placing of the digit at position is valid, and unaltered otherwise */
bool make_move(const char* position,const char digit,char board[9][9]){
    bool validity = true;
    // converting position into array coordinates //
    const int row = position[0] - 'A', column = position[1] - '1';
    
    // check the validity of position and placing of the digit at position //
    if (row < 0 || row > 8 || column < 0 || column > 8 ){ // if position invalid //
        validity = false;
    }else if (board[row][column]!='.'){ //already occupied //
        validity = false;
    }else{ // continue if position is valid and empty //
        // a sanity check: //
        // whether the position row and column already contain this digit //
        for (int i = 0; i < 9; i++){
            if (board[row][i]==digit || board[i][column]==digit){
                validity = false;
                break;
            }
        }
        
        // continue if passed sanity check //
        if (validity!=false){
            //check the 3x3 sub-board //
            int row1 = row-row%3, column1 = column - column%3;
            for (int r = row1; r < row1+3; r++){ // rows //
                for (int c = column1; c < column1+3; c++){ // columns //
                    if (board[r][c]==digit){
                        validity = false;
                        break;
                    }
                } // rows//
            } // columns//
        }
        
    }
    
    // update board if the move is valid//
    if (validity != false){
        board[row][column] = digit;
    }
    
    return validity;
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
  }else{ //failed to open file for writing
      return false;
  }
}

/* a Boolean function to check whether a solution can be found for a given sudoku board */
/* updates board if solution is found */
bool solve_board(char board[9][9]){
  bool solution = true;
  if (is_complete(board)){
      solution = true;
  }else{
      for (int r = 0; r < 9; r++){      // rows //
          for (int c = 0; c < 9; c++){  // columns //
              
              if (board[r][c]=='.'){
                  const char position[3] = {(char)('A'+ r),(char)('1'+c),'\0'};
                  //try placing digit at position//
                  for (char digit = '1'; digit <= '9'; digit ++){
                      if (make_move(position,digit,board)){
                          if (solve_board(board)){
                              solution = true;
                          //}else{
                              //board[r][c]='.';
                          }
                      }
                  }
                  solution = false;
                  break;
              }
              
          }  // rows //
      }  // columns //
  }
  return solution;
}


