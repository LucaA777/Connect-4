#include <iostream>

using namespace std;

void takeTurn(int player, int board[6][7]);
bool isValidMove(int col, int board[6][7]);

enum Player {
  EMPTY,
  X,
  O
};

int main() {

  Player player = X;
  int board[6][7];

  takeTurn(player);
  
  return 0;
}

void takeTurn(int player, int board[6][7]) {

  switch (player) {
    
  case X:
    cout << "X's turn." << endl;

    //get input from player
    col = -1;
    do {
      if (cin.fail()) {
	cin.ignore();
	cin.clear(10000, '\n');
      }


    } while (cin.fail() || !isValidMove(col, board));
    
    break;

  case O:
    cout <<"O's turn." << endl;
    break;
  }
  
}

bool isValidMove(int col, int board[6][7]) {
  
}
