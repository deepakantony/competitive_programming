#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class TicTacToeGame {
public:
  TicTacToeGame() {
    reset();
  }

  void reset() {
    player[0] = 'x';
    player[1] = 'o';
    currentPlayer = 0;
    gameStatus = -1;
    resetBoard();
  }

  bool isGameOver() const {
    return gameStatus != -1;
  }

  int getCurrentPlayer() const {
    return currentPlayer+1;
  }

  bool move(int row, int col) {
    if(isGameOver())
      return false;
    if(row >= 0 && row < 3 
       && col >=0 && col < 3
       && !board[row][col])
      board[row][col] = player[currentPlayer];
    else 
      return false; // Could not move

    updateGameStatus();
    toggleCurrentPlayer();
    return true;
  }

  void consoleDisplayBoard() const {
    for(int col = 0; col < 3; col++) {
      cout << " -";
    }
    cout << endl;
    for(int row = 0; row < 3; row++) {
      cout << "|";
      for(int col = 0; col < 3; col++) {
	if(board[row][col])
	  cout << board[row][col] << "|";
	else
	  cout << " |";
      }
      cout << endl;
      for(int col = 0; col < 3; col++)
	cout << " -";
      cout << endl;
    }
  }

  void consoleDisplayResult() const {
    if(isGameOver()) {
      if(gameStatus == 2)
	cout << "Game is a draw. No more winning moves left." << endl;
      else
	cout << "Player " << gameStatus + 1 << " won the game." << endl;
    }
    else
      cout << "Game is still playable!" << endl;
  }

private:
  void resetBoard() {
    for(int row = 0; row < 3; row++)
      for(int col = 0; col < 3; col++)
	board[row][col] = 0;
  }

  void updateGameStatus() {
    bool stillPlayable = false;

    // need to check all the possible combinations from first row and column
    // diagonal from (0,0)
    testAndUpdateStatus(board[0][0], board[1][1], 
			board[2][2], stillPlayable);
    // across from (0,0)
    testAndUpdateStatus(board[0][0], board[0][1], 
			board[0][2], stillPlayable);
    // down from (0,0)
    testAndUpdateStatus(board[0][0], board[1][0], 
			board[2][0], stillPlayable);
    // down from (0,1)
    testAndUpdateStatus(board[0][1], board[1][1], 
			board[2][1], stillPlayable);
    // diagonal from (0,2)
    testAndUpdateStatus(board[0][2], board[1][1], 
			board[2][0], stillPlayable);
    // down from (0,2)
    testAndUpdateStatus(board[0][2], board[1][2], 
			board[2][2], stillPlayable);
    // across from (1,0)
    testAndUpdateStatus(board[1][0], board[1][1], 
			board[1][2], stillPlayable);
    // across from (2,0)
    testAndUpdateStatus(board[2][0], board[2][1], 
			board[2][2], stillPlayable);
    // update if its still playable
    if(!stillPlayable && !isGameOver())
      gameStatus = 2; // draw
  }
  
  // Tests the status of 3 cells. A cell is a position in the board.
  // Updates:
  // stillPlayable if game is still playable i.e. no draw/win
  // gameStatus variable if a game is won
  void testAndUpdateStatus(char cell1, char cell2, char cell3, 
			  bool &stillPlayable) {
    if(isGameOver())
      return; // no need to test if the game is over

    if(cell1 && cell1 == cell2 &&
       cell2 == cell3) {
      gameStatus = currentPlayer;
      stillPlayable = false;
      return;
    }

    if(!cell1) {
      if(cell2 == cell3)
	stillPlayable = true;
      if(!cell2 || !cell3)
	stillPlayable = true;
    }
    if(!cell2) {
      if(cell3 == cell1)
	stillPlayable = true;
      if(!cell3)
	stillPlayable = true;
    }
    if(!cell3 && cell1 == cell2)
      stillPlayable = true;
  }

  void toggleCurrentPlayer() {
    currentPlayer = currentPlayer ? 0:1;
  }

private:
  char player[2];
  char board[3][3];
  int currentPlayer;
  int gameStatus;
};

int main(int argc, char **argv) {
  TicTacToeGame tictactoe;

  while(!tictactoe.isGameOver()) {
    tictactoe.consoleDisplayBoard();
    bool validMove;
    int row, col;
    string input;
    bool validInput;
    do {
      row = 0; col = 0;
      input = "";
      validInput = false;
      validMove = true;

      cout << "Player " << tictactoe.getCurrentPlayer() 
	   << ", make your move (row col): " << flush;

      getline(cin,input);
      stringstream stringInput(input);
      if(stringInput >> row && stringInput >> col) 
	validInput = true;
      cin.clear();

      if(validInput)
	validMove = tictactoe.move(row-1,col-1);
      else
	cout << "Please enter valid inputs." << endl;
      if(!validMove) {
	cout << "Could not make this move; please try again." << endl;
      }
    }while(!validMove || !validInput);
  }
  tictactoe.consoleDisplayBoard();
  tictactoe.consoleDisplayResult();

  return 0;
}

