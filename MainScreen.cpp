#include "MainScreen.h"
#include "ScreenHandler.h"
namespace rg2 {
#include <raygui.h>
};

auto& stngs = SettingsScreen::getInstance();

SettingsScreen::SettingsScreen() {

}

void MainScreen::Draw()
{
	if (stngs.settings) {
		stngs.Tick();
		return;
	}

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

	rg2::GuiSetStyle(rg2::DEFAULT, rg2::TEXT_SIZE, rg2::TEXT_SIZE * 2);
	rg2::GuiSetStyle(rg2::BUTTON, rg2::TEXT_COLOR_DISABLED, 0xffffff);
	rg2::GuiSetStyle(rg2::CHECKBOX, rg2::BORDER_COLOR_DISABLED, 0xffffff);
	if (rg2::GuiButton({ startButton.x, startButton.y - startButton.height, startButton.width, startButton.height }, "Settings")) {
		stngs.settings = true;
	}
}

constexpr int MAX_SYMBOLS = 3;

void MainScreen::Update()
{
	if (!stngs.settings) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			auto mp = GetMousePosition();
			if (mp.x >= offsetX && mp.x <= offsetX + 50 * 3 && mp.y >= offsetY && mp.y <= offsetY + 4 * 50) {
				mp.x = (int)(mp.x - offsetX) / 50;
				mp.y = (int)(mp.y - offsetY) / 50;
				if (mp.y < 3) {
					if (selection == SELECTED_X ? x.length() < MAX_SYMBOLS : y.length() < MAX_SYMBOLS)
						selection == SELECTED_X ? x += std::to_string(int(mp.x + mp.y * 3)) : y += std::to_string(int(mp.x + mp.y * 3));
				}
				else {
					if (mp.x == 0) {
						if (selection == SELECTED_X ? x.length() < MAX_SYMBOLS : y.length() < MAX_SYMBOLS)
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
						ScreenHandler::getInstance().simMode = SettingsScreen::getInstance().getNeigbMode() ? EIGHT_NEIGHBOORS : FOUR_NEIGHBOORS;
						ScreenHandler::getInstance().mut = SettingsScreen::getInstance().getMutateMode();
						ScreenHandler::getInstance().selfD = SettingsScreen::getInstance().getSelfDesMode();
						ScreenHandler::getInstance().mut_chance = SettingsScreen::getInstance().getMutChance();
						ScreenHandler::getInstance().mg.create(a, b);
						ScreenHandler::getInstance().sw.init();
						ScreenHandler::getInstance().changeScreen(SPAWNER);
					}
				}
			}
		}
	}
}

const int margin = 30;
const int checkBoxSize = 20;

void SettingsScreen::Tick() {
	ClearBackground({ 0xbb,0xbb,0xbb, 0xff });

	Rectangle rec{ margin, margin, checkBoxSize, checkBoxSize };
	if (rg2::GuiCheckBox(rec, "8 Neighboors", &neighboors_eight) == 1) {
		ScreenHandler::getInstance().simMode = ScreenHandler::getInstance().simMode == EIGHT_NEIGHBOORS ? FOUR_NEIGHBOORS : EIGHT_NEIGHBOORS;
	}
	rec.y += margin;
	if (rg2::GuiCheckBox(rec, "Cell Self-destruct", &self_destruction) == 1) {
		ScreenHandler::getInstance().selfD = !ScreenHandler::getInstance().selfD;
	}
	rec.y += margin;
	if (rg2::GuiCheckBox(rec, "Mutations", &mutations) == 1) {
		ScreenHandler::getInstance().mut = !ScreenHandler::getInstance().mut;
	}
	if (mutations) {
		Rectangle r = rec;
		r.y += margin;
		r.width += 4 * margin;
		rg2::GuiSlider(r, "", ("Mutation chance (" + std::to_string(mut_chance).substr(0, 4) + ")").c_str(), &mut_chance, 0, 1);
	}

	if (rg2::GuiButton({ (float)GetScreenWidth() / 2 - 100, (float)GetScreenHeight() - margin - 75, 200, 75 }, "BACK")) {
		settings = false;
		ScreenHandler::getInstance().mut_chance = mut_chance;
	}
}

#undef _CRT_SECURE_NO_WARNINGS
#undef _CRT_SECURE_NO_DEPRECATE
#undef RAYGUI_IMPLEMENTATION

