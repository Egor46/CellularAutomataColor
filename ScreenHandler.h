#pragma once
#include "SpawnerScreen.h"
#include "MainGameScreen.h"
#include "MainScreen.h"

bool operator==(const Color&, const Color&);
bool operator!=(const Color&, const Color&);

enum SCREEN {
	MAIN,
	GAME,
	SPAWNER
};

enum SIM_MODE {
	FOUR_NEIGHBOORS = 4,
	EIGHT_NEIGHBOORS = 8
};

class ScreenHandler
{
	friend class MainScreen;
	friend class SpawnerScreen;
private:
	SCREEN currentScreen = MAIN;
	MainGameScreen& mg = MainGameScreen::getInstance();
	MainScreen ms = MainScreen();
	SpawnerScreen sw = SpawnerScreen();
	ScreenHandler() {

	}

public:

	SIM_MODE simMode = FOUR_NEIGHBOORS;
	bool mut;
	bool random_mutations;
	double mut_chance;
	bool selfD;

	MyBoard gameBoard;

	void changeScreen(SCREEN scr) {
		if (scr == MAIN) SettingsScreen::getInstance().started = false;
		currentScreen = scr;
	}

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

