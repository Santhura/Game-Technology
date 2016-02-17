using namespace std;

class Chessboard
{
public:
	array<pair<int, int>, 8> moves;			// The numbers of different moves you can make.
	array<array<int, 8>, 8> data;			// contains the value of each tile
	bool keepRunning = true;				// to see if the program has to keep running
	bool keepAsking = true;					// when program finish keep asking for another run

	//Pointers
	string *stringPointer;					// Pointer to change string values

	//constants
	const int boardSize = 8;				// fixed board size

	//constructor
	Chessboard();

	//methods
	array<int, 8> sortMoves(int x, int y, const int boardSize)const;
	void solve(string& start, const int boardSize);
	void printSolution(Chessboard b, const int boardSize);
};