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
	Rectangle startButton{ (float) sW / 2 - chatboxWidth,(float) sH - chatboxHeight * 4,(float) chatboxWidth * 2, (float)chatboxHeight * 2};
	std::string x, y;
	int offsetX = 400, offsetY = 400;
	bool selection = SELECTED_X;

public:

	MainScreen() {
		x = y = "";
	}

	void Draw();

	void Update();

};

class SettingsScreen
{
	SettingsScreen();
	bool neighboors_eight = false;
	bool self_destruction = true;
	bool mutations = false;
	float mut_chance = 0;
public:

	bool settings = false;

	static SettingsScreen& getInstance() {
		static SettingsScreen inst;
		return inst;
	}

	bool getNeigbMode() {
		return neighboors_eight;
	}

	bool getSelfDesMode() {
		return self_destruction;
	}

	bool getMutateMode() {
		return mutations;
	}

	float getMutChance() {
		return mut_chance;
	}
	
	void Tick();
};