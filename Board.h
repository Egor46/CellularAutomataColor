#pragma once
#include <vector>
#include <raylib.h>

enum CELL_COLORS {
	CRED, CGREEN, CBLUE, CPURPLE, CMAGENTA, CBLACK, CWHITE, CCYAN
};

class Board
{
private:
	int x, y;
	const int colorcount = 8;
public:
	std::vector<std::vector<CELL_COLORS>> board;

	Board() {
		x = y = 0;
	}

	Board& operator=(const Board&& other) noexcept {
		board = other.board;
		return *this;
	}

	Board(int _x, int _y) {
		x = _x;
		y = _y;
		board.resize(_x);
		for (int i = 0; i < _x; i++) {
			board[i].resize(_y);
		}
	}
};

