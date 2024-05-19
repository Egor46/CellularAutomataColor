#define RAYGUI_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include "ScreenHandler.h"
#include <iostream>
namespace rg {
#include <raygui.h>
};

static const int RecSize = 5;
static MyBoard& _board = ScreenHandler::getInstance().gameBoard;
static Vector2 tmp;
static const float hCP = 50;
static Vector2 beginCP;
static bool settings = false;

static void proceduralGen() {
	std::random_device rand;
	std::mt19937 mr;
	mr.seed(rand());
	std::uniform_int_distribution<int> ur(0, _board.colors.size() - 1);
	int curcol = ur(mr);
	for (auto it = ++_board.board.begin(); it != --_board.board.end(); it++) {
		std::fill(++(*it).begin(), --(*it).end(), _board.colors[curcol]);
	}
	const int mx = _board.getX() - 2;
	const int my = _board.getY() - 2;
	for (int i = 0; i < mx + my; i++) {
		std::uniform_int_distribution<int> ur1(1, mx), ur2(1, my);
		int rec1 = ur1(mr), rec2 = ur2(mr);
		int col = ur(mr);
		{
			decltype(ur1) ur3(rec1, mx), ur4(rec2, my);
			int rec3 = ur3(mr), rec4 = ur4(mr);
			for (int i = rec1; i <= rec3; i++) {
				for (int j = rec2; j <= rec4; j++) _board.board[i][j] = _board.colors[col];
			}
		}
	}
}

void SpawnerScreen::init()
{
	beginCP = { GetScreenWidth() / 2 - hCP * (_board.colors.size()) / 2 , 0 };
	tmp.x = sW / 2 - _board.getX() * RecSize / 2 + 1;
	tmp.y = sH / 2 - _board.getY() * RecSize / 2 + 1;
}

void SpawnerScreen::Draw()
{
	if (SettingsScreen::getInstance().settings) {
		SettingsScreen::getInstance().Tick();
		return;
	}
	// доска
	ClearBackground(WHITE);

	for (int i = 0; i < _board.getX(); i++) {
		for (int j = 0; j < _board.getY(); j++) {
			Rectangle re{ tmp.x + i * RecSize, tmp.y + j * RecSize, RecSize, RecSize };
			DrawRectangleRec(re, _board.board[i][j]);
		}
	}

	// выбор цвета


	for (int i = 0; i < _board.colors.size(); i++) {
		DrawRectangle(beginCP.x + hCP * i, 0, hCP, hCP, _board.colors[i]);
	}
	DrawRectangleLinesEx({ beginCP.x + hCP * selected, beginCP.y, hCP, hCP }, hCP / 10, BLACK);

	if (rg::GuiButton({ (float)GetScreenWidth() - 200, (float)GetScreenHeight() - 100, 200, 100 }, "START")) {
		ScreenHandler::getInstance().changeScreen(GAME);
	}
	if (rg::GuiButton({ 0, (float)GetScreenHeight() - 100, 200, 100 }, "RANDOM")) {
		proceduralGen();
	}
	if (rg::GuiButton({ sW / 2 - 100, (float)GetScreenHeight() - 50, 200, 50 }, "Settings")) {
		SettingsScreen::getInstance().settings = true;
	}
	if (rg::GuiButton({ 0,0, 100, 50 }, "Menu")) ScreenHandler::getInstance().changeScreen(MAIN);

	if (rg::GuiButton({ sW - 50, sH / 2 - 25, 50 , 50 }, ">")) ScreenHandler::getInstance().mg.Update();
}

void SpawnerScreen::Update()
{
	if (!SettingsScreen::getInstance().settings) {
		// обработка установки пикселей
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			Vector2 mp = GetMousePosition();
			if (mp.x > tmp.x && mp.x < tmp.x + RecSize * _board.getX() && mp.y > tmp.y && mp.y < tmp.y + RecSize * _board.getY()) {
				Vector2 local_c = { (int)(mp.x - tmp.x) / RecSize, (int)(mp.y - tmp.y) / RecSize };

				if ((Color)_board.board[local_c.x][local_c.y] != BLACK) {
					_board.board[local_c.x][local_c.y] = _board.colors[selected];
					if (IsKeyDown(KEY_LEFT_SHIFT)) {
						if (local_c.x > 1 && local_c.x < _board.getX() - 2 && local_c.y > 1 && local_c.y < _board.getY() - 2) {
							_board.board[local_c.x - 1][local_c.y] = _board.board[local_c.x + 1][local_c.y] =
								_board.board[local_c.x][local_c.y - 1] = _board.board[local_c.x][local_c.y + 1] =
								_board.board[local_c.x - 1][local_c.y - 1] = _board.board[local_c.x - 1][local_c.y + 1] =
								_board.board[local_c.x + 1][local_c.y - 1] = _board.board[local_c.x + 1][local_c.y + 1] = _board.colors[selected];
						}
					}

				}
			}
			// color picker & start button
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				Vector2 mp = GetMousePosition();
				if (mp.x > beginCP.x && mp.x < beginCP.x + hCP * (_board.colors.size()) && mp.y >= 0 && mp.y <= hCP) {
					selected = (int)(-beginCP.x + mp.x) / hCP;
				}
				if (CheckCollisionPointRec(mp, { (float)GetScreenWidth() - 100, (float)GetScreenHeight() - 50, 100, 50 })) {
					ScreenHandler::getInstance().changeScreen(GAME);
				}
			}
		}
	}
}