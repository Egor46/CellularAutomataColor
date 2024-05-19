#pragma once
#include "ScreenHandler.h"
namespace rg1 {
#include <raygui.h>
}

static const int RecSize = 5;
static MyBoard& _board = ScreenHandler::getInstance().gameBoard;
static Vector2 tmp;
static const float hCP = 50;
static Vector2 beginCP;

typedef std::uniform_int_distribution<int> uid;

static std::mt19937 mt(std::random_device());
static uid __rint;
bool selfD;
typedef std::uniform_real_distribution<> urd;
static urd _rrnd;

void MainGameScreen::create(int x, int y)
{
	ScreenHandler::getInstance().gameBoard = MyBoard(x, y);
	beginCP = { GetScreenWidth() / 2 - hCP * (_board.colors.size()) / 2 , 0 };
	tmp.x = sW / 2 - _board.getX() * RecSize / 2 + 1;
	tmp.y = sH / 2 - _board.getY() * RecSize / 2 + 1;
	prevup = _board.board[0];
	selfD = ScreenHandler::getInstance().selfD;
	__rint = uid(0, ScreenHandler::getInstance().simMode - 1 + (short)!selfD);
	if (ScreenHandler::getInstance().mut) _rrnd = urd(0, 1);
}

void MainGameScreen::Draw()
{
	ClearBackground(WHITE);
	for (int i = 0; i < _board.getX(); i++) {
		for (int j = 0; j < _board.getY(); j++) {
			Rectangle re{ tmp.x + i * RecSize, tmp.y + j * RecSize, RecSize, RecSize };
			DrawRectangleRec(re, _board.board[i][j]);
		}
	}
	if (rg1::GuiButton({ sW / 2 - 100, sH - 50, 100, 50 }, "EDIT")) {
		ScreenHandler::getInstance().changeScreen(SPAWNER);
	}
	if (rg1::GuiButton({ sW / 2, sH - 50, 100, 50 }, "MENU")) {
		ScreenHandler::getInstance().changeScreen(MAIN);
	}
}

static bool reroll;

inline Color average(const Color& c1, const Color& c2) {
	unsigned char r = c1.r / 2 + c2.r / 2, g = c1.g / 2 + c2.g / 2, b = c1.b / 2 + c2.b / 2;
	return { r, g, b, 0xff };
}
void MainGameScreen::Update()
{
	for (int i = 1; i < _board.getX() - 1; i++) {
		for (int j = 1; j < _board.getY() - 1; j++) {
			reroll = true;
			auto& cell = _board.board[i][j];
			while (reroll) {
				int randInt = __rint(mt);
				Color c;
				switch (randInt) {
				case 0:
					c = prevup[j];
					break;
				case 1:
					c = prevleft;
					break;
				case 2:
					c = _board.board[i][j + 1];
					break;
				case 3:
					c = _board.board[i + 1][j];
					break;
				case 4:
					c = prevup[j - 1];
					break;
				case 5:
					if (!selfD && ScreenHandler::getInstance().simMode == 4) {
						c = cell;
						break;
					}
					c = prevup[j + 1];
					break;
				case 6:
					c = _board.board[i + 1][j - 1];
					break;
				case 7:
					c = _board.board[i + 1][j + 1];
					break;
				case 8:
					c = cell;
					break;
				} // end switch

				if (c != BLACK) {
					prevleft = _board.board[i][j];
					reroll = false;
					if (ScreenHandler::getInstance().mut) {
						double de = _rrnd(mt);
						if (de < ScreenHandler::getInstance().mut_chance) {
							if (ScreenHandler::getInstance().random_mutations) {
								uid tmp(0, 255);
								unsigned char r = tmp(mt), g = tmp(mt), b = tmp(mt);
								c = { r, g, b, 0xff };
							}
							else c = average(_board.board[i][j], c);
						}
					}
					cell = c;
				}
			}
		}
		prevup = _board.board[i];
	}
}

#undef _CRT_SECURE_NO_WARNINGS
#undef _CRT_SECURE_NO_DEPRECATE
#undef RAYGUI_IMPLEMENTATION