/**
* @brief A tic-tac-toe board class, creating a 3 x 3 board of Xs and Os
*/

class Board
{
private:
	char squares[3][3]; /** 3 x 3 2-Dimensional array representing board**/
public:
	Board();
	~Board();
	char Query(int horiz, int vert);
	void Place(int horiz, int vert, char tile);
	char CheckWin();
	char CheckDraw();
	void printBoard();
};