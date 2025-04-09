#include "Game.h"

int main() {
	int t = 256;
	Game game("Escape of the Fox", t*4, t*2);
	game.run();
	return 0;
}
