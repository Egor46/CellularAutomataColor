#include "MainScreen.h"
#include "ScreenHandler.h"

void MainScreen::Draw()
{
	ClearBackground(Color{ 0xbb, 0xbb, 0xbb });

	DrawText("X", offsetX / 2 + chatboxWidth / 2 - fontSize, offsetY / 2 - fontSize, fontSize, WHITE);
	DrawRectangle(offsetX / 2, offsetY / 2, chatboxWidth, chatboxHeight, WHITE);
	DrawText(x.c_str(), offsetX / 2 + 4, offsetY / 2 + chatboxHeight / (fontSize / 2), fontSize, BLACK);

	DrawText("Y", offsetX / 2 + offsetX + chatboxWidth / 2, offsetY / 2 - fontSize, fontSize, WHITE);
	DrawRectangle(offsetX / 2 + offsetX, offsetY / 2, chatboxWidth, chatboxHeight, WHITE);
	DrawText(y.c_str(), offsetX / 2 + offsetX + 4, offsetY / 2 + chatboxHeight / (fontSize / 2), fontSize, BLACK);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			DrawRectangle(offsetX + j * 50, offsetY + i * 50, 50, 50, WHITE);
			DrawRectangleLines(offsetX + j * 50, offsetY + i * 50, 50, 50, BLACK);
			DrawText(std::to_string(i * 3 + j).c_str(), offsetX + j * 50 + fontSize / 2, offsetY + i * 50 + fontSize / 4, 50, BLACK);
		}
	}
	DrawRectangle(offsetX + 0 * 50, offsetY + 3 * 50, 50, 50, WHITE);
	DrawRectangleLines(offsetX + 0 * 50, offsetY + 3 * 50, 50, 50, BLACK);
	DrawText("9", offsetX + 0 * 50 + fontSize / 2, offsetY + 3 * 50 + fontSize / 4, 50, BLACK);

	DrawRectangle(offsetX + 1 * 50, offsetY + 3 * 50, 50, 50, WHITE);
	DrawRectangleLines(offsetX + 1 * 50, offsetY + 3 * 50, 50, 50, BLACK);
	DrawText(selection == SELECTED_X ? "X" : "Y", offsetX + 1 * 50 + fontSize / 2, offsetY + 3 * 50 + fontSize / 4, 50, BLACK);

	DrawRectangle(offsetX + 2 * 50, offsetY + 3 * 50, 50, 50, WHITE);
	DrawRectangleLines(offsetX + 2 * 50, offsetY + 3 * 50, 50, 50, BLACK);
	DrawText("C", offsetX + 2 * 50 + fontSize / 2, offsetY + 3 * 50 + fontSize / 4, 50, BLACK);

	if (x != "" && y != "") {
		DrawRectangleRec(startButton, RED);
		DrawRectangleLinesEx(startButton, 4, BLACK);
		DrawText("START", startButton.x + fontSize * 1.5, startButton.y + fontSize / 2, fontSize * 2, BLACK);
	}
}

void MainScreen::Update()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		auto mp = GetMousePosition();
		if (mp.x >= offsetX && mp.x <= offsetX + 50 * 3 && mp.y >= offsetY && mp.y <= offsetY + 4 * 50) {
			mp.x = (int)(mp.x - offsetX) / 50;
			mp.y = (int)(mp.y - offsetY) / 50;
			if (mp.y < 3) {
				if (selection == SELECTED_X ? x.length() <= 5 : y.length() <= 5)
					selection == SELECTED_X ? x += std::to_string(int(mp.x + mp.y * 3)) : y += std::to_string(int(mp.x + mp.y * 3));
			}
			else {
				if (mp.x == 0) {
					if (selection == SELECTED_X ? x.length() <= 5 : y.length() <= 5)
						selection == SELECTED_X ? x += '9' : y += '9';
				}
				else if (mp.x == 1) selection = !selection;
				else if (mp.x == 2) {
					if (selection == SELECTED_X) {
						if (x.length() != 0) x.pop_back();
					}
					else {
						if (y.length() != 0) y.pop_back();
					}
				}
			}
		}
		else if (x != "" && y != "") {
			if (CheckCollisionPointRec(mp, startButton)) {
				int a = std::stoi(x), b = std::stoi(y);
				if (a != 0 && b != 0) {
					isMyScreen = false;
					ScreenHandler::getInstance().mg.create(a,b);
				}
			}
		}
	}
}