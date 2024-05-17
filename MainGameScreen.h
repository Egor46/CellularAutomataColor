#pragma once
#include "Board.h"
#include <raylib.h>

class MainGameScreen
{
private:

	std::mt19937 mt;
	std::uniform_int_distribution<int> Rand;
	std::vector<Color> prevup;
	Color prevleft;
	MainGameScreen() {

	}
	bool started = false;

public:

	static MainGameScreen& getInstance() {
		static MainGameScreen inst;
		return inst;
	}

	void create(int x, int y);

	void Draw();

	void Update();

};

