#pragma once
class SpawnerScreen
{
private:

public:

	bool shouldShow = false;

	void Show() {
		shouldShow = true;
	}

	void Hide() {
		shouldShow = false;
	}

	void Draw();

	void Update();

};

