#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Class TicTacToeGame: 
// This class defines the gameplay for the tic tac toe game.
// This class stores the board information and the player symbols.
class TicTacToeGame {
public:
  // the default constructor
  TicTacToeGame();

  // reset all the variables and the board
  void reset();
  // check if the game is still playable
  bool isGameOver() const;
  // who's the current player
  int getCurrentPlayer() const;
  // the move of the current player
  bool move(int row, int col);
  // display of the board
  void consoleDisplayBoard() const;
  // display the result of the game
  void consoleDisplayResult() const;

private:
  // reset the values of the board
  void resetBoard();
  // update gameStatus based on the current move
  void updateGameStatus();
  // finds out if someone won the game or if the game is still playable
  void testAndUpdateStatus(char cell1, char cell2, char cell3, bool &stillPlayable);
  // changes the current player variable
  void toggleCurrentPlayer();

private:
  // Could have defined the size constants but the code should be updated to work 
  // with more than 2 players or for board size different from 3x3.

  // 2 players
  char player[2]; 
  // board is 3x3 size
  char board[3][3]; 
  // this is a status variable which indicates who the current player is
  // it can only be 0 or 1
  int currentPlayer; 
  // this is a status variable which indicates whether the game is over or still playable
  // it can be -1 (still playable), 0(player 1 won), 1(player 2 won), 2(draw)
  int gameStatus; 
};

// The default constructor resets all variables
TicTacToeGame::TicTacToeGame() {
  reset();
}

// reset variables - read the variable 
void TicTacToeGame::reset() {
  player[0] = 'x';
  player[1] = 'o';
  currentPlayer = 0; // player 1 plays first
  gameStatus = -1;
  resetBoard(); // initializes board cells to 0
}

bool TicTacToeGame::isGameOver() const {
  return gameStatus != -1; // game is over if its no playable
}

// who's the current player
int TicTacToeGame::getCurrentPlayer() const {
  return currentPlayer+1;
}

// make current players move
bool TicTacToeGame::move(int row, int col) {
  if(isGameOver()) // no move can be made if the game is over
    return false;

  if(row >= 0 && row < 3 
     && col >=0 && col < 3
     && !board[row][col]) // valid row and col value ?
    board[row][col] = player[currentPlayer]; // assign current player's symbol
  else 
    return false; // Could not move

  // update game status if it should be updated
  updateGameStatus();
  // next move by the next player
  toggleCurrentPlayer();

  // successful move
  return true;
}

/*
  Display the board in the format
   - - -
  |o| |x|
   - - -
  | |x| |
   - - -
  |x| |o|
   - - -
*/
void TicTacToeGame::consoleDisplayBoard() const {
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

// Displays a message based on the current gameStatus
void TicTacToeGame::consoleDisplayResult() const {
  if(isGameOver()) {
    if(gameStatus == 2)
      cout << "Game is a draw. No more winning moves left." << endl;
    else
      cout << "Player " << gameStatus + 1 << " won the game." << endl;
  }
  else
    cout << "Game is still playable!" << endl;
}

// initialize all the cells to 0
void TicTacToeGame::resetBoard() {
  for(int row = 0; row < 3; row++)
    for(int col = 0; col < 3; col++)
      board[row][col] = 0;
}

// check all possible winning moves and update the gameStatus
void TicTacToeGame::updateGameStatus() {
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
void TicTacToeGame::testAndUpdateStatus(char cell1, char cell2, char cell3, 
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

// change to next player
void TicTacToeGame::toggleCurrentPlayer() {
  currentPlayer = currentPlayer ? 0:1;
}


int main(int argc, char **argv) {
  TicTacToeGame tictactoe; // current game
  bool playAgain = false;
  do {
    playAgain = false;
    while(!tictactoe.isGameOver()) { // play till game is over
      tictactoe.consoleDisplayBoard();

      // identifies whether it was a valid move
      bool validMove;
      // user inputs / moves
      int row, col;
      // placeholder for the initial input to remove the dependency 
      // on the >> operator which has problems with invalid inputs
      string input;
      // identifies if the user input was valid
      bool validInput;
      do {
	row = 0; col = 0;
	input = "";
	validInput = false;
	validMove = true;

	cout << "Player " << tictactoe.getCurrentPlayer() 
	     << ", make your move (row col): " << flush;

	getline(cin,input);
	// we will use stringstream variable to spit out values to row and col
	stringstream stringInput(input);
	if(stringInput >> row && stringInput >> col) 
	  validInput = true;
	cin.clear(); // clear any bad state stored

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

    // user interaction to check if user wants to play again
    string playAgainInput;
    cout << endl;
    cout << "If you'd like to play again press 'y/Y'; or else press any key to exit" << endl;
    getline(cin,playAgainInput);
    if(playAgainInput.size() > 0 && playAgainInput[0] == 'y' || playAgainInput[0] == 'Y')
      playAgain = true;

    tictactoe.reset();
  }while(playAgain);

  return 0;
}

