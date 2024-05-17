#pragma once
#include <raylib.h>
#include "ScreenHandler.h"

class GameManager
{
private:

	ScreenHandler& sh = ScreenHandler::getInstance();

public:

	GameManager() {
		InitWindow(sW, sH, "Game");
		SetTargetFPS(120);
	}

	~GameManager() {
		CloseWindow();
	}

	void Tick();

};

