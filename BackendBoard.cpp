#include "BackendBoard.h"
#include "NineManGame.h"
#include <iostream>
#include <iomanip>

bool BackendBoard::formsMill(int startRow, int startCol, int player) {
	// function to traverse array from given position in each direction to search for mill

	int i = startRow;
	int j = startCol;
	int oppPlayer;
	int result;					// stores result from each individual direction check
	int millCount = 1;			// used to count number of pieces "in line" of the same player, if it equals 3,
								// there is a mill. Initialized to 1 to include current piece.

	if (player == NineManGame::WHITE) {		// denote opposite player for array traversal
		oppPlayer = NineManGame::BLACK;
	}
	else { oppPlayer = NineManGame::WHITE; }


	// Vertical Mills
	while (--i >= NineManGame::ROWMIN) {	// check upwards
		result = millDirectionCheck(i, startCol, millCount, player, oppPlayer);	// check if position adds to mill
		if (result < 0) { break; }							// break if mill is impossible in that direction
		if (millCount == 3) { return true; }
	}
	i = startRow;			// reset row position
	while (++i < NineManGame::ROWMAX) {	// check downwards
		result = millDirectionCheck(i, startCol, millCount, player, oppPlayer);	// check if position adds to mill
		if (result < 0) { break; }							// break if mill is impossible in that direction
		if (millCount == 3) { return true; }
	}

	millCount = 1;			// reset millCount for search in other direction

	// Horizontal Mills
	while (--j >= NineManGame::COLMIN) {	// check leftwards
		result = millDirectionCheck(startRow, j, millCount, player, oppPlayer);	// check if position adds to mill
		if (result < 0) { break; }							// break if mill is impossible in that direction
		if (millCount == 3) { return true; }
	}
	j = startCol;			// reset column position
	while (++j < NineManGame::COLMAX) {	// check rightwards
		result = millDirectionCheck(startRow, j, millCount, player, oppPlayer);	// check if position adds to mill
		if (result < 0) { break; }							// break if mill is impossible in that direction
		if (millCount == 3) { return true; }
	}
	return false;
}

int BackendBoard::millDirectionCheck(int i, int j, int& millCount, int player, int oppPlayer) {
	// check if position in question contains a piece that can be used in player's mill

	if ((i == 3) && (j == 3)) {					// avoid crossing middle - impossible mill
		return -1;
	}
	else if (board[i][j] == player) {		// add to millCount if same player
		millCount++;
		return 1;
	}
	else if (board[i][j] == oppPlayer) {	// stop searching that direction if opposite player's piece is in way
		return -1;
	}
	return 0;								// no action, but keep searching
}

void BackendBoard::printBoard() {		//utility function to visualize backend logic "board"
	for (int i = 0; i < NineManGame::ROWMAX; i++) {
		std::cout << "{ ";
		for (int j = 0; j < NineManGame::COLMAX; j++) {
			std::cout << std::setw(2) << std::right << board[i][j] << " ";
		}
		std::cout << "}" << std::endl;
	}
	std::cout << std::endl;
}

BackendBoard::BackendBoard() {
	std::cout << "Backend Board Created." << std::endl;
	printBoard();	// show initial board
}

BackendBoard::~BackendBoard() {}