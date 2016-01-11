
#include "metaboard.hpp"
#include <iostream>
#include <stdio.h>
#include <string>
/** 
* @brief MetaBoard constructor initializing empty metaboard as 3 x 3 2-D array of boards
*/
MetaBoard::MetaBoard()
{

	for (int i= 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			metaboard[i][j] = Board(); // Initializes empty board
		}
	}
	for (int i= 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			winnersboard[i][j] = ' '; // Initializes empty board
		}
	}
}

/**
* @brief Board destructor can be empty, no dynamically allocated memory.
*/
MetaBoard::~MetaBoard(){

}

/**
* @brief Returns state of tic-tac-toe square, given its coordinates.
*
* @param horizb the horizontal coordinates of the board
* @param vertb the vertical coordinates of the board
* @param horiz the horizontal coordinates of the square in the board
* @param vert the vertical coordinates of the square in the board
*
* @return The array value representing the tic-tac-toe square
*/
char MetaBoard::MetaQuery(int horizb, int vertb, int horiz, int vert){
	return metaboard[horizb][vertb].Query(horiz, vert);
}

/**
* @brief Places X or O on board in specified square ina specified board.
*
* @param horizb the horizontal coordinates of the board
* @param vertb the vertical coordinates of the board
* @param horiz the horizontal coordinates of the square
* @param vert the vertical coordinates of the square
* @param tile the X or O to be placed in the square
*/
void MetaBoard::MetaPlace(int horizb, int vertb, int horiz, int vert, char tile){
	metaboard[horizb][vertb].Place(horiz, vert, tile);
	return;
}

/**
* @brief Checks to see if there is a winner, and if so, who it is.
*
* @return the character of the winning player, or 'N' if no winner
*/
char MetaBoard::CheckWin(){
	
	for (int i = 0; i < 3; i++){
			if (winnersboard[i][0] == winnersboard[i][1] && winnersboard[i][1] == winnersboard[i][2] && winnersboard[i][2] != ' '){
				return winnersboard[i][0];
			}
			if (winnersboard[0][i] == winnersboard[1][i] && winnersboard[1][i] == winnersboard[2][i] && winnersboard[2][i] != ' '){
				return winnersboard[0][i];
			}
		}
		if (winnersboard[0][0] == winnersboard[1][1] && winnersboard[2][2] == winnersboard[1][1] && winnersboard[1][1] != ' '){
			return winnersboard[0][0];
		}
		if (winnersboard[0][2] == winnersboard[1][1] && winnersboard[2][0] == winnersboard[1][1] && winnersboard[1][1] != ' '){
			return winnersboard[0][2];
		}
	
	return 'N'; // N for No winner
}

/**
* @brief Checks to see if there is a draw.
*
* @return Returns Y if there is a draw, N if there is not.
*/
char MetaBoard::CheckDraw(){
	for (int i= 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (metaboard[i][j].CheckDraw() == 'N'){
				return 'N';
			}
		}
	}
	char isWin = this->CheckWin();
	if (isWin == 'N'){
		return 'Y';
	}
	return 'N';
}

/**
* @brief Prints out board as it currently is, in easy-to-read format
*/
void MetaBoard::printBoard(){
	std::string board1 = "/---/---/---/-/---/---/---/-/---/---/---/\n";
	std::string board2 = board1;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			for (int k = 0; k < 3; k++){
				for (int l = 0; l < 3; l++){
					board2 += "/ ";
					board2.append(1, this->MetaQuery(k, i, l, j));
					board2 += " ";
											}
					board2 += "/-";
										}
					board2 += "\n";
									}
					board2 += board1;
								}
	std::cout << board2;
return;
}

/**
* @brief Checks to see if a board in the 3 x 3 grid can be active (if it is not completely filled)
* 
* @param horiz the horizontal coordinate of the 3 x 3 grid of boards
* @param vert the vertical coordinate of the 3 x 3 grid of boards
*
* @return 'Y' if the board is active, 'N' if the board is not.
*/
char MetaBoard::IsActive(int horiz, int vert){
	if (metaboard[horiz][vert].CheckDraw() == 'Y'){
		return 'N';
	}
		return 'Y';
}

/**
* @brief Fills 3 x 3 board with winners of 3 x 3 grid of boards
*/
void MetaBoard::fillWinnersBoard(){
	for (int i= 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if(metaboard[i][j].CheckWin() != 'N' && winnersboard[i][j] == ' '){
				winnersboard[i][j] = metaboard[i][j].CheckWin();
			}
		}
	}
}
