#include "ScreenHandler.h"

bool operator==(const Color& x, const Color& y) {
	return x.r == y.r && x.g == y.g && x.b == y.b && x.a == y.a;
}
bool operator!=(const Color& x, const Color& y) {
	return !(x == y);
}

void ScreenHandler::Update()
{
	switch (currentScreen) {
	case MAIN:
		ms.Update();
		break;
	case GAME:
		mg.Update();
		break;
	case SPAWNER:
		sw.Update();
		break;
	}
}

void ScreenHandler::Draw()
{
	BeginDrawing();

	switch (currentScreen) {
	case MAIN:
		ms.Draw();
		break;
	case GAME:
		mg.Draw();
		break;
	case SPAWNER:
		sw.Draw();
		break;
	}

	EndDrawing();
}
