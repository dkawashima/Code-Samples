/**
* @brief A tic-tac-toe game class, 
* allowing user to play a game of tic-tac-toe.
*/

class Game
{
private:
	Board board1;
	char turn;
public:
	Game(); 
	~Game();
	void Run();
};