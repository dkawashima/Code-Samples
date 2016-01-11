/**
* @brief A tic-tac-toe metagame class, 
* allowing user to play a game of meta-tic-tac-toe.
*/

class MetaGame
{
private:
	MetaBoard board1;
	char turn;
	int activBoardVert;
	int activBoardHoriz;
public:
	MetaGame(); 
	~MetaGame();
	void Run();
};