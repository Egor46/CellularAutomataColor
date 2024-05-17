#include "GameManager.h"

int main() {
	GameManager game = GameManager();
	while (!WindowShouldClose()) {
		game.Tick();
	}
}