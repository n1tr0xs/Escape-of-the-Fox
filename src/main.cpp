#include "Engine.hpp"

#if defined(_WIN32) && !(defined(_DEBUG) || defined(DEBUG) || defined(_CONSOLE))
// Release build on Windows
#include <windows.h>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Engine game("Escape of the Fox");
	game.run();
	return 0;
}
#else
int main() {
	Engine game("Escape of the Fox");
	game.run();
	return 0;
}
#endif
