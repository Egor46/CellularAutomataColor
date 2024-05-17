#pragma once
#include <raylib.h>

class SpawnerScreen
{
private:
	int selected = 0;

public:

	bool shouldShow = false;
	void init();

	void Show() {
		shouldShow = true;
	}

	void Hide() {
		shouldShow = false;
	}

	void Draw();

	void Update();

};

