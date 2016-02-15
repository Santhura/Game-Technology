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

array<int, 8> Chessboard::sortMoves(int x, int y, int& boardSize) const
{
	array<tuple<int, int>, 8> counts;
	for (int i = 0; i < boardSize; ++i)
	{
		int dx = get<0>(moves[i]);
		int dy = get<1>(moves[i]);

		int c = 0;
		for (int j = 0; j < boardSize; ++j)
		{
			int x2 = x + dx + get<0>(moves[j]);
			int y2 = y + dy + get<1>(moves[j]);

			if (x2 < 0 || x2 >= boardSize || y2 < 0 || y2 >= boardSize) // check if out side the chess board
				continue;
			if (data[y2][x2] != 0)
				continue;

			c++;
		}
		counts[i] = make_tuple(c, i);
	}

	// Shuffle to randomly break ties
	random_shuffle(counts.begin(), counts.end());

	// Lexicographic sort
	sort(counts.begin(), counts.end());

	array<int, 8> out;
	for (int i = 0; i < boardSize; ++i)
		out[i] = get<1>(counts[i]);
	return out;
}

void Chessboard::solve(string start, int& boardSize)
{
	//reset all values to 0
	for (int v = 0; v < boardSize; ++v)
		for (int u = 0; u < boardSize; ++u)
			data[v][u] = 0;

	// first start position of the knight
	int x0 = start[0] - 'a';
	int y0 = boardSize - (start[1] - '0');
	data[y0][x0] = 1;

	array<tuple<int, int, int, array<int, 8>>, 8 * 8> order;
	order[0] = make_tuple(x0, y0, 0, sortMoves(x0, y0, boardSize));

	int n = 0;
	while (n < boardSize * boardSize - 1)
	{
		int x = get<0>(order[n]);
		int y = get<1>(order[n]);

		bool ok = false;
		for (int i = get<2>(order[n]); i < boardSize; ++i)
		{
			// set next move
			int dx = moves[get<3>(order[n])[i]].first;
			int dy = moves[get<3>(order[n])[i]].second;

			//check if move is out of bounds
			if (x + dx < 0 || x + dx >= boardSize || y + dy < 0 || y + dy >= boardSize)
				continue;
			if (data[y + dy][x + dx] != 0)
				continue;

			++n;
			get<2>(order[n]) = i + 1;
			data[y + dy][x + dx] = n + 1;
			order[n] = make_tuple(x + dx, y + dy, 0, sortMoves(x + dx, y + dy, boardSize));
			ok = true;
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
void Chessboard::printSolution(Chessboard &b, int& boardSize)
{
	for (int v = 0; v < boardSize; ++v)
	{
		for (int u = 0; u < boardSize; ++u)
		{
			if (u != 0)
			{
				cout << " | ";
			}
			cout << setw(3) << b.data[v][u];
		}
		cout << endl;

		cout << "-------------------------------------------------" << endl;
	}
}

int main()
{
	Chessboard chessBoard;
	while (chessBoard.keepRunning)
	{
		int boardSizeValue = 1;

		cout << "Choose the board size: ";
		cin >> boardSizeValue;

		chessBoard.boardSize = boardSizeValue;

		char startLetter;
		cout << "choose a letter where you start from 'a' to the end of your board size (a=1, b=2 etc): ";
		cin >> startLetter;

		int startNumber;
		cout << "choose a number where you start from 1 to the board Size you filled in: ";
		cin >> startNumber;
		cout << "\n";

		string start = startLetter + to_string(startNumber);

		chessBoard.solve(start, chessBoard.boardSize);
		chessBoard.printSolution(chessBoard, chessBoard.boardSize);

		do
		{
			cout << "\n\nDo you want to do another one?" << endl;
			cout << "press 'y' to keep going, press 'n' to stop" << endl;

			char y = 'y'; //yes
			char n = 'n'; //no
			char input = NULL;
			cin >> input;

			if (input == y) // do the tour again
			{
				chessBoard.keepAsking = false;
				chessBoard.keepRunning = true;
				cout << "\n\n";
			}
			else if (input == n) // Stop application
			{
				return 0;
			}
			else // error message
			{
				cout << "ERROR: wrong input!";
				chessBoard.keepAsking = true;
			}
		} while (chessBoard.keepAsking);
	}
	return 0;
}