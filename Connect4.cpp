#include <iostream>

using namespace std;

const char redCol[] = "\033[1;31m";
const char blueCol[] = "\033[1;34m";
const char backCol[] = "\033[0m";

void takeTurn(int player, int board[6][7]);
void printColored(const char message[50], const char foreground[10], const char background[10]);
void resetBoard(int board[6][7]);
void printBoard(int board[6][7]);
bool isValidMove(int col);


enum Player {
  EMPTY,
  RED,
  BLUE
};

int main() {

  Player player = RED;
  int board[6][7];

  resetBoard(board);
  printBoard(board);
  takeTurn(player, board);

  board[5][0] = BLUE;
  printBoard(board);
  cout << "Normal text.";

  printColored("More red Text", redCol, backCol);
  printColored("Some blue text too.", blueCol, backCol);
  
  return 0;
}

void takeTurn(int player, int board[6][7]) {

  switch (player) {
    
  case RED:
    
    break;

  case BLUE:
    
    break;
  }
  
}


void printColored(const char message[50], const char foreground[10], const char background[10]) {

  cout << foreground << message << background;
}

void resetBoard(int board[6][7]) {
  for (int x = 0; x < 7; x++) {
    for (int y = 0; y < 6; y++) {
      board[y][x] = EMPTY;
    }
  }
}

void printBoard(int board[6][7]) {
  cout << "Board: " << endl;
  for (int x = 0; x < 7; x++) {
    for (int y = 0; y < 6; y++) {

      if (board[y][x] == EMPTY) {
	cout << "-";
      }
      else if (board[y][x] == RED) {
	printColored("O", redCol, backCol);
      }
      else if (board[y][x] == BLUE) {
	printColored("O", blueCol, backCol);
      }
      else {
	cout << " ";
      }

      cout << "  ";
    }
    cout << endl;
  }

  cout << endl;
}

bool isValidMove(int col, int board[6][7]) {
  if (col >= 6 || col < 0) {
    return false;
  }
  return checkColumnDepth(col, board) != -1;
}

bool checkColumnDepth(int col, int board[6][7]) {
  for (int i = 0; i < 6; i++) {
    if (board[i][col] != EMPTY) {
      return i - 1;
    }
  }

  return 5;
}
