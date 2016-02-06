#include <iostream>
#define N 8
using namespace std;

//defines a structure for chess moves
typedef struct chess_moves {
	// 'x' and 'y' coordinates on chess board
	int x, y;
}chess_moves;

//displays the knight tour
void printTour(int tour[N][N]) {
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			cout << tour[i][j] << "   |   ";

		}
		cout << endl;
	}
}

//check if the next move (as per knight's constraints) is possible
bool isMovePossible(chess_moves next_move, int tour[N][N]) {
	int i = next_move.x;
	int j = next_move.y;
	if ((i >= 0 && i < N) && (j >= 0 && j < N) && (tour[i][j]) == 0) {
		return true;
	}
	return false;
}

bool findTour(int tour[N][N], chess_moves move_KT[], chess_moves curr_move, int move_count)
{
	int i;
	chess_moves next_move;
	if (move_count == N*N - 1) {
		//knight tour is completed i.e all cells on the 
		// chess board has been visited by knight once
		return true;
	}

	for (i = 0; i < N; i++)
	{
		next_move.x = curr_move.x + move_KT[i].x;
		next_move.y = curr_move.y + move_KT[i].y;

		if (isMovePossible(next_move, tour)) {
			tour[next_move.x][next_move.y] = move_count + 1;
			if (findTour(tour, move_KT, next_move, move_count + 1)) {
				return true;
			}
			else {
				tour[next_move.x][next_move.y] = 0;
			}
		}
	}
	return false;
}


void knightTour()
{
	int tour[N][N];
	int i, j;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			tour[i][j] = 0;
		}
	}

	chess_moves move_KT[8] = { {2,1},{1,2},{-1,2},{-2,1},
							{-2,-1},{-1,-2},{1,-2},{2,-1} };

	chess_moves curr_move = { 4,4 };

	if (!findTour(tour, move_KT, curr_move, 0))
	{
		cout << "\nknigth tour does not exits";
	}
	else {
		cout << "\ntour exits...\n";
		printTour(tour);
	}
}


int main() {
	knightTour();
	cout << endl;
	int i;
	cin >> i;
	return 0;
}