#include <iostream>
#include <iomanip>
#include <array>
#include <string>
#include <tuple>
#include <algorithm>
using namespace std;

class Chessboard
{
public:
	array<pair<int, int>, 8> moves;			// The numbers of different moves you can make.
	array<array<int, 8>, 8> data;			// 

	Chessboard();

	array<int, 8> sortMoves(int x, int y, int& boardSize)const;
	void solve(string start, int& boardSize);
	void printSolution(Chessboard &b, int& boardSize);

	int boardSize;
	bool keepRunning = true;
	bool keepAsking = true;

};