#pragma once
#include "SpawnerScreen.h"
#include "MainGameScreen.h"
#include "MainScreen.h"

enum SCREEN {
	MAIN,
	GAME,
	SPAWNER
};

class ScreenHandler
{
	friend class MainScreen;
private:
	SCREEN currentScreen = MAIN;
	MainGameScreen& mg = MainGameScreen::getInstance();
	MainScreen ms = MainScreen();
	ScreenHandler() {

	};

public:

	static ScreenHandler& getInstance() {
		static ScreenHandler inst;
		return inst;
	}

	void Update();

	void Draw();

	void Tick() {
		Update();
		Draw();
	}

};

