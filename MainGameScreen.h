#pragma once
#include "Board.h"
#include <raylib.h>
#include "SpawnerScreen.h"

class MainGameScreen
{
private:
	
	Board board;

	MainGameScreen() {

	}
	bool started = false;
	SpawnerScreen sw = SpawnerScreen();

public:

	static MainGameScreen& getInstance() {
		static MainGameScreen inst;
		return inst;
	}

	void create(int x, int y);

	void Draw();

	void Update();

};

