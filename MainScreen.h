#pragma once
#include "Board.h"
#include <string>
#include "Consts.h"

static const int chatboxWidth = 100, chatboxHeight = 30, fontSize = 20;
#define SELECTED_X false
#define SELECTED_Y true

class MainScreen
{

private:
	Rectangle startButton{ sW / 2 - chatboxWidth, sH - chatboxHeight * 4, chatboxWidth * 2, chatboxHeight * 2};
	std::string x, y;
	int offsetX = 400, offsetY = 400;
	bool selection = SELECTED_X;

public:
	bool isMyScreen = true;
	MainScreen() {
		x = y = "";
	}

	void Draw();

	void Update();
};

