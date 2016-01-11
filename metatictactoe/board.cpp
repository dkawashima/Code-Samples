/**
* @brief A tic-tac-toe board class
*/
#include <iostream>
#include <stdio.h>
#include "board.hpp"
#include <string>

Board::Board()
{

	for (int i= 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			squares[i][j] = ' '; // Initializes empty board
		}
	}
}

/**
* @brief Board destructor can be empty, no dynamically allocated memory.
*/
Board::~Board(){

}

/**
* @brief Returns state of tic-tac-toe square given its coordinates.
*
* @param horiz the horizontal coordinates of the square
* @param vert the vertical coordinates of the square
*
* @return The array representing the tic-tac-toe board
*/
char Board::Query(int horiz, int vert){
	return squares[horiz][vert];
}

/**
* @brief Places X or O on board in specified square.
*
* @param horiz the horizontal coordinates of the square
* @param vert the vertical coordinates of the square
* @param tile the X or O to be placed in the square
*/
void Board::Place(int horiz, int vert, char tile){
	squares[horiz][vert] = tile;
	return;
}
/**
* @brief Checks to see if there is a winner, and if so, who it is.
*
* @return the character of the winning player, or 'N' if no winner
*/
char Board::CheckWin(){
	for (int i = 0; i < 3; i++){
			if (squares[i][0] == squares[i][1] && squares[i][1] == squares[i][2] && squares[i][2] != ' '){
				return squares[i][0];
			}
			if (squares[0][i] == squares[1][i] && squares[1][i] == squares[2][i] && squares[2][i] != ' '){
				return squares[0][i];
			}
		}
		if (squares[0][0] == squares[1][1] && squares[2][2] == squares[1][1] && squares[1][1] != ' '){
			return squares[0][0];
		}
		if (squares[0][2] == squares[1][1] && squares[2][0] == squares[1][1] && squares[1][1] != ' '){
			return squares[0][2];
		}
	
	return 'N'; // N for No winner
}

/**
* @brief Checks to see if there is a draw.
*
* @return Returns Y if there is a draw, N if there is not.
*/
char Board::CheckDraw(){
	for (int i= 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (squares[i][j] == ' '){
				return 'N';
			}
		}
	}
	char isWin = CheckWin();
	if (isWin == 'N'){
		return 'Y';
	}
	return 'N';
}

/**
* @brief Prints out board as it currently is, in easy-to-read format
*/
void Board::printBoard(){
	std::string board1 = "/---/---/---/\n";
	std::string board2;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			board2 += "/ ";
			board2.append(1, squares[j][i]);
			board2 += " ";
	}
	board2 += "/\n";
	}
	std::cout << board1;
	std::cout << board2;
	std::cout << board1;
return;
}
