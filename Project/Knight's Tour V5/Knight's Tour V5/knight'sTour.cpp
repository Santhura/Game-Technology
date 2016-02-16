#include <iostream>
#include <iomanip>
#include <array>
#include <string>
#include <tuple>
#include <algorithm>
#include "knightstour.h"
using namespace std;

Chessboard::Chessboard()
{
	// all the moves a knight can make.
	moves[0] = make_pair(2, 1);
	moves[1] = make_pair(1, 2);
	moves[2] = make_pair(-1, 2);
	moves[3] = make_pair(-2, 1);
	moves[4] = make_pair(-2, -1);
	moves[5] = make_pair(-1, -2);
	moves[6] = make_pair(1, -2);
	moves[7] = make_pair(2, -1);
}

array<int, 8> Chessboard::sortMoves(int x, int y, const int boardSize) const
{
	array<tuple<int, int>, 8> moveCounts;
	for (int i = 0; i < boardSize; ++i)
	{
		//get move
		int dx = get<0>(moves[i]);
		int dy = get<1>(moves[i]);

		int c = 0;
		for (int j = 0; j < boardSize; ++j)
		{
			//calculate next move
			int x2 = x + dx + get<0>(moves[j]);
			int y2 = y + dy + get<1>(moves[j]);

			// check if out side the chess board
			if (x2 < 0 || x2 >= boardSize || y2 < 0 || y2 >= boardSize) 
				continue;
			// check if the tile is already filled
			if (data[y2][x2] != 0)
				continue;

			c++;
		}
		// contain all the moves that were made
		moveCounts[i] = make_tuple(c, i);
	}

	// sort the moves count
	sort(moveCounts.begin(), moveCounts.end());

	//return the new move
	array<int, 8> out;
	for (int i = 0; i < boardSize; ++i)
		out[i] = get<1>(moveCounts[i]);
	return out;
}

void Chessboard::solve(string &start, const int boardSize)
{
	//reset all values to 0
	for (int v = 0; v < boardSize; ++v)
		for (int u = 0; u < boardSize; ++u)
			data[v][u] = 0;

	// first start position of the knight
	int x0 = start[0] - 'a';
	int y0 = boardSize - (start[1] - '0');
	data[y0][x0] = 1;

	// a collection of the ordor for the movement
	array<tuple<int, int, array<int, 8>>, 8 * 8> order;
	order[0] = make_tuple(x0, y0, sortMoves(x0, y0, boardSize));

	int n = 0;
	while (n < boardSize * boardSize - 1)
	{
		//get start position
		int x = get<0>(order[n]);
		int y = get<1>(order[n]);

		bool ok = false;
		for (int i = 0; i < boardSize; ++i)
		{
			// set next move
			int dx = moves[get<2>(order[n])[i]].first;
			int dy = moves[get<2>(order[n])[i]].second;

			//check if move is out of bounds
			if (x + dx < 0 || x + dx >= boardSize || y + dy < 0 || y + dy >= boardSize)
				continue;
			// check if the next tile is already filled
			if (data[y + dy][x + dx] != 0)
				continue;

			++n;
			data[y + dy][x + dx] = n + 1;														//set new value at this tile
			order[n] = make_tuple(x + dx, y + dy, sortMoves(x + dx, y + dy, boardSize));		//set the new current position and look for next position
			ok = true;																			// success 
			break;
		}

		if (!ok) // Failed. Backtrack.
		{
			data[y][x] = 0;
			--n;
		}
	}
}

// print the solution that is found with a width field of 3
void Chessboard::printSolution(Chessboard b, const int boardSize)
{
	for (int v = 0; v < boardSize; ++v)
	{
		for (int u = 0; u < boardSize; ++u)
		{
			if (u != 0)
			{
				printf(" | ");
			}
			cout << setw(3) << b.data[v][u];
		}
		printf("\n");

		printf("----------------------------------------------\n");
	}
}

int main()
{
	Chessboard chessBoard;
	while (chessBoard.keepRunning)
	{
		printf("The Board Size is 8 x 8\n");
		string inputStart;
		bool chooseStart = false;
		do
		{
			chessBoard.stringPointer = &inputStart;

			printf("\nchoose a letter where you start from 'a' to 'h'\nand a number between 1 and 8: ");
			
			//put in start position
			cin >> *chessBoard.stringPointer;
			printf("\n");

			// check if the user put in right input
			if (inputStart.size() > 2 || inputStart.size() < 2){
				printf("\nError: The input you have given was to short or to long!\n");
				chooseStart = false;
			}
			else if (string::npos == inputStart.find_first_of("0123456789"))
			{
				printf("\nError: The input you have given did not contain a number\n");
				chooseStart = false;
			}
			else
			{
				chooseStart = true;
			}
		} while (!chooseStart);

		chessBoard.solve(inputStart, chessBoard.boardSize);				//Solve knight's tour
		chessBoard.printSolution(chessBoard, chessBoard.boardSize);		//print the solution
		
		do
		{
			printf("\n\nDo you want to do another one?\n");
			printf("press 'y' to keep going, press 'n' to stop\n");

			string y = "y";						//yes
			string n = "n";						//no
			string input;
			chessBoard.stringPointer = &input;
			cin >> *chessBoard.stringPointer;

			if (input == y) // do the tour again
			{
				chessBoard.keepAsking = false;
				chessBoard.keepRunning = true;
				printf("\n\n");
			}
			else if (input == n) // Stop application
			{
				return 0;
			}
			else // error message
			{
				printf("ERROR: wrong input!");
				chessBoard.keepAsking = true;
			}
		} while (chessBoard.keepAsking);
	}
	return 0;
}