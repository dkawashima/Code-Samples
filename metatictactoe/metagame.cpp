/**
* @brief A tic-tac-toe game class
*/
#include "metaboard.hpp"
#include "metagame.hpp"
#include <iostream>
#include <stdio.h>
#include "game.hpp"

/**
* @brief Constructs a new MetaGame, with X starting first, and no current active board.
*/

MetaGame::MetaGame()
{
	turn = 'X';
	board1 = MetaBoard();
	activBoardHoriz = 3;
	activBoardVert = 3;
}

/**
* @brief MetaGame destructor can be empty, no dynamically allocated memory.
*/

MetaGame::~MetaGame()
{

}

/**
* @brief Runs a game of Tic-Tac-Toe. Gameplay starts with player X and
* continues until one player wins or a draw is reached. 
*/
void MetaGame::Run(){
	int horizb;
	int vertb;
	int horiz;
	int vert;
	bool notFilled = true;
	while (board1.CheckWin() == 'N' && board1.CheckDraw() == 'N'){ // Game continues 
		// until victory or draw
		board1.printBoard(); // Board reprinted before every move
		printf("Game Time: Player %c is up!\n", turn);
		while (notFilled == true){ // Makes sure square is empty before placing tile
			if (activBoardHoriz == 3 && activBoardVert == 3){
			printf("There is no active board!\n");
			printf("Type in the horizontal coordinate (0, 1, 2) of the board: ");
			std::cin >> horizb;
			printf("Type in the vertical coordinate (0, 1, 2) of the board: ");
			std::cin >> vertb;
		} else {
			if (board1.IsActive(activBoardHoriz, activBoardVert) == 'N'){
				printf("There is no active board!\n");
				printf("Type in the horizontal coordinate (0, 1, 2) of the board: ");
				std::cin >> horizb;
				printf("Type in the vertical coordinate (0, 1, 2) of the board: ");
				std::cin >> vertb;
			} else {
				printf("The Active Board is (horiz, vert): (%d, %d)\n", activBoardHoriz, activBoardVert);
				horizb = activBoardHoriz;
				vertb = activBoardHoriz;
			}
		}
			printf("Type in the horizontal coordinate (0, 1, 2) of the square: ");
			std::cin >> horiz;
			activBoardHoriz = horiz;
			printf("Type in the vertical coordinate (0, 1, 2) of the square: ");
			std::cin >> vert;
			activBoardVert = vert;
			if (board1.MetaQuery(horizb, vertb, horiz, vert) == ' '){ // Square is empty
				board1.MetaPlace(horizb, vertb, horiz, vert, turn);
				notFilled = false; 
			} else {
				printf("Sorry! That square is already filled!\n");
		}
		}
		if (turn == 'X'){ // Switches player's turns after each move
			turn = 'O';
		} else {
			turn = 'X';
		}
		notFilled = true;
		board1.fillWinnersBoard();
}
	board1.printBoard();
	if (board1.CheckDraw() == 'Y') { 
		printf("We have a draw!\n");
		return;
	}
	printf("Player %c has won!\n", board1.CheckWin());
	return;
}
