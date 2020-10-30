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
    for (int r=0; r<9; r++) { /* rows */
        for (int n=0; n<9; n++) { /* columns */
            if (board[r][n]=='.'){
                complete = false;
                break;
            }
        } /* columns */
    }/* rows */
      return complete;
}

/* a Boolean function that places a digit onto a Sudoku board at a given position */
/* the board will be updated if placing of the digit at position is valid, and unaltered otherwise */
bool make_move(const char* position,char digit,char board[9][9]){
    /* converting position into array coordinates*/
    //char pos = position;
    int row = position[0] - 'A';
    int column = position[1] - '1';
    
    /* if the position is valid then check whether placing of the digit at position is valid*/
    //if (row < 0 || row > 8 || column < 0 || column > 8 ){
    //    return false;
    //} else{
    //    if(any_of(board[row].begin(), board[row].end(), [](int i){return i==digit;})){
    //        return false;
    //    }else{
            return true;
    //    }
    //}
}

/* a Boolean function to save the sudoku board ( in a 2D character array) to a file named filename */
bool save_board(const char* filename, char board[9][9]){
  //ofstream boardTOsave;
  //boardTOsave.open("filename");
  return true;
}

/* a Boolean function to check whether a solution can be found for a given sudoku board */
/* updates board if solution is found */
bool solve_board(char board[9][9]){
  return true;
}

