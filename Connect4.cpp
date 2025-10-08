#include <iostream>
#include <algorithm>

using namespace std;

const char redCol[] = "\033[1;31m";
const char blueCol[] = "\033[1;34m";
const char backCol[] = "\033[0m";


enum Player {
  EMPTY,
  RED,
  BLUE
};

struct MinimaxReturn {
  int score;
  int row;
  int col;
};


void takeTurn(int player, int (&board)[6][7]);
void printColored(const char message[50], const char foreground[10], const char background[10]);
void resetBoard(int (&board)[6][7]);
void printBoard(int (&board)[6][7]);
bool isValidMove(int col, int (&board)[6][7]);
int checkColumnDepth(int col, int (&board)[6][7]);
void placePlayer(int player, int row, int col, int (&board)[6][7]);
bool checkRowWinner(int player, int (&board)[6][7]);
bool checkColWinner(int player, int (&board)[6][7]);
bool checkDiagWinner(int player, int (&board)[6][7]);
bool checkWinner(int player, int (&board)[6][7]);
bool checkMovesLeft(int (&board)[6][7]);
MinimaxReturn* minimax(int truePlayer, int trueEnemy, int player, int depth, int alpha, int beta, int (&board)[6][7]);


int main() {

  Player player = RED;
  int board[6][7];

  resetBoard(board);
  printBoard(board);

  while (/*!checkWinner(RED, board) && !checkWinner(BLUE, board) &&*/ checkMovesLeft(board)) {
    cout << "Next move..." << endl;
    takeTurn(player, board);

    if (player == RED) {
      player = BLUE;
    }
    else {
      player = RED;
    }
  }
  


  
  return 0;
}

void takeTurn(int player, int (&board)[6][7]) {

  switch (player) {

  case RED: {
    int col = minimax(RED, BLUE, RED, 4, -10000, 10000, board) -> col;
    
    if (!isValidMove(col, board)) {

    }
    else {
      placePlayer(RED, checkColumnDepth(col, board), col, board);
    }
    
    break;
  }

  case BLUE: {
    int col = minimax(BLUE, RED, BLUE, 4, -10000, 10000, board) -> col;
    
    if (!isValidMove(col, board)) {

    }
    else {
      placePlayer(BLUE, checkColumnDepth(col, board), col, board);
    }
    
    break;
  }
  }

  printBoard(board);
  
}


void printColored(const char message[50], const char foreground[10], const char background[10]) {

  cout << foreground << message << background;
}

void resetBoard(int (&board)[6][7]) {
  for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 7; x++) {
      board[y][x] = EMPTY;
    }
  }
}

void printBoard(int (&board)[6][7]) {
  cout << "Board: " << endl;
  cout << "1  2  3  4  5  6  7" << endl;
  for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 7; x++) {

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

bool isValidMove(int col, int (&board)[6][7]) {
  if (col >= 6 || col < 0) {
    return false;
  }
  return checkColumnDepth(col, board) != -1;
}

int checkColumnDepth(int col, int (&board)[6][7]) {
  for (int i = 0; i < 6; i++) {
    if (board[col][i] != EMPTY) {
      cout << "Col depth: " << i - 1;
      return i - 1;
    }
  }

  return 5;
}

void placePlayer(int player, int row, int col, int (&board)[6][7]) {
  board[row][col] = player;
}

bool checkRowWinner(int player, int (&board)[6][7]) {
  int streak = 0;

  for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 6; x++) {

      if (board[y][x] == player && board[y][x] == board[y][x + 1]) {
	streak++;
      }
      else {
	streak = 0;
      }

      if (streak == 3) {
	return true;
      }
    }

    streak = 0;
  }

  return false;
}

bool checkColWinner(int player, int (&board)[6][7]) {
  int streak = 0;

  for (int y = 0; y < 5; y++) {
    for (int x = 0; x < 7; x++) {

      if (board[y][x] == player && board[y][x] == board[y + 1][x]) {
	streak++;
      }
      else {
	streak = 0;
      }

      if (streak == 3) {
	return true;
      }
    }

    streak = 0;
  }

  return false;
}

bool checkDiagWinner(int player, int (&board)[6][7]) {
  for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 7; x++) {

      //ascending diagonal
      //confirms that the complete potential diagonal is in the bounds
      if (y + 3 < 6 && x + 3 < 7) {
	if (board[y][x] == player && board[y + 1][x + 1] == player && board[y + 2][x + 2] == player && board[y + 3][x + 3] == player) {
	  return true;
	}
      }


      //descending diagonal
      //confirms that the complete potential diagonal is in the bounds
      if (y + 3 < 6 && x - 3 >= 0) {
	if (board[y][x] == player && board[y + 1][x - 1] == player && board[y + 2][x - 2] == player && board[y + 3][x - 3] == player) {
	  return true;
	}
      }
    }
  }

  return false;
}

bool checkWin(int player, int (&board)[6][7]) {
  return checkDiagWinner(player, board) || checkColWinner(player, board) || checkRowWinner(player, board);
}

bool checkMovesLeft(int (&board)[6][7]) {
  for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 7; x++) {
      if (board[y][x] == EMPTY) {
	return true;
      }
    }
  }

  return false;
}

//returns score, optimal row, and optimal col
MinimaxReturn* minimax(int truePlayer, int trueEnemy, int player, int depth, int alpha, int beta, int (&board)[6][7]) {
  int optimalRow = -1;
  int optimalCol = -1;

  //basecase
  if (checkWin(truePlayer, board)) {
    return new MinimaxReturn{1000, optimalRow, optimalCol};
  }
  else if (checkWin(trueEnemy, board)) {
    return new MinimaxReturn{-1000, optimalRow, optimalCol};
  }
  else if (!checkMovesLeft(board)) {
    return new MinimaxReturn{0, optimalRow, optimalCol};
  }
  else if (depth == 0) {
    return new MinimaxReturn{0, optimalRow, optimalCol};
  }

  //recursive case
  if (player == truePlayer) {

    int best = -10000;

    for (int y = 0; y < 6; y++) {
      if (isValidMove(y, board)) {

	int x = checkColumnDepth(y, board);
	placePlayer(player, y, x, board);

	int value = minimax(truePlayer, trueEnemy, trueEnemy, depth - 1, alpha, beta, board) -> score;

	if (value > best) {
	  best = value;
	  optimalRow = y;
	  optimalCol = x;
	}

	placePlayer(EMPTY, y, x, board);

	alpha = max(alpha, value);
	if (alpha >= beta) {
	  break;
	}
      }
    }

    return new MinimaxReturn{best, optimalRow, optimalCol};
  }

  if (player == trueEnemy) {

    int worst = 10000;

    for (int y = 0; y < 6; y++) {
      if (isValidMove(y, board)) {

	int x = checkColumnDepth(y, board);
	placePlayer(player, y, x, board);

	int value = minimax(truePlayer, trueEnemy, truePlayer, depth - 1, alpha, beta, board) -> score;

	if (value < worst) {
	  worst = value;
	  optimalRow = y;
	  optimalCol = x;
	}

	placePlayer(EMPTY, y, x, board);

	beta = min(beta, value);
	if (alpha >= beta) {
	  break;
	}
      }
    }

    return new MinimaxReturn{worst, optimalRow, optimalCol};
  }
}
