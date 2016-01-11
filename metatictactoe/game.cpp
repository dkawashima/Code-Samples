/**
* @brief A tic-tac-toe game class
*/
#include "board.hpp"
#include <iostream>
#include <stdio.h>
#include "game.hpp"

/**
* @brief Constructs a new Game, with X starting first.
*/

Game::Game()
{
	turn = 'X';
	board1 = Board();
}

/**
* @brief Game destructor can be empty, no dynamically allocated memory.
*/

Game::~Game()
{

}

/**
* @brief Runs a game of Tic-Tac-Toe. Gameplay starts with player X and
* continues until one player wins or a draw is reached. 
*/
void Game::Run(){
	int horiz;
	int vert;
	bool notFilled = true;
	while (board1.CheckWin() == 'N' && board1.CheckDraw() == 'N'){ // Game continues 
		// until victory or draw
		board1.printBoard(); // Board reprinted before every move
		printf("Game Time: Player %c is up!\n", turn);
		while (notFilled == true){ // Makes sure square is empty before placing tile
			printf("Type in the horizontal coordinate (0, 1, 2): ");
			std::cin >> horiz;
			printf("Type in the vertical coordinate (0, 1, 2): ");
			std::cin >> vert;
			if (board1.Query(horiz, vert) == ' '){ // Square is empty
				board1.Place(horiz, vert, turn);
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
}
	board1.printBoard();
	if (board1.CheckDraw() == 'Y') { 
		printf("We have a draw!\n");
		return;
	}
	printf("Player %c has won!\n", board1.CheckWin());
	return;
}
