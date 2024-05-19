#pragma once
#include <vector>
#include <raylib.h>
#include <random>

class MyBoard
{
private:
	int x, y;
	const int colorcount = 8;
public:
	std::vector<std::vector<Color>> board;
	std::vector<Color> colors;

	MyBoard() {
		x = y = 0;
	}

	int getX() const { return x; }
	int getY() const { return y; }

	MyBoard& operator=(const MyBoard&& other) noexcept {
		board = other.board;
		x = other.x;
		colors = other.colors;
		y = other.y;
		return *this;
	}

	MyBoard(int _x, int _y) {
		x = _x + 2;
		y = _y + 2;
		board.resize(x);
		for (int i = 0; i < x; i++) {
			board[i].resize(y);
		}
		for (int i = 0; i < y; i++) {
			board[0][i] = board[x - 1][i] = BLACK;
		}
		for (int i = 0; i < x; i++) {
			board[i][0] = board[i][y - 1] = BLACK;
		}

		for (int i = 1; i < x-1; i++) {
			for (int j = 1; j < y-1; j++) {
				board[i][j] = WHITE;
			}
		}

		std::random_device rand;
		std::mt19937 mt(rand());
		std::uniform_int_distribution<int> ra(0, 255);
		for (int i = 0; i < colorcount; i++) colors.push_back(Color{ (uint8_t)ra(mt), (uint8_t)ra(mt), (uint8_t)ra(mt), 255 });
	}
};

