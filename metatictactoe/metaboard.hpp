/**
* @brief A tic-tac-toe board class, creating a 3 x 3 board of Xs and Os
*/
#include "board.hpp"

class MetaBoard
{
private:
	Board metaboard[3][3]; /** 3 x 3 2-Dimensional array of boards**/
	char winnersboard[3][3];
public:
	MetaBoard();
	~MetaBoard();
	char MetaQuery(int horizb, int vertb, int horiz, int vert);
	void MetaPlace(int horizb, int vertb, int horiz, int vert, char tile);
	char CheckWin();
	char CheckDraw();
	void printBoard();
	char IsActive(int horiz, int vert);
	void fillWinnersBoard();

};