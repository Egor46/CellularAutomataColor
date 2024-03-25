#include "ScreenHandler.h"

void ScreenHandler::Update()
{
	switch (currentScreen) {
	case MAIN:
		ms.Update();
		if (!ms.isMyScreen) currentScreen = GAME;
		break;
	case GAME:
		mg.Update();
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
	}

	EndDrawing();
}
