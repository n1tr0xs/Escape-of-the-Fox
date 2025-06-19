#include "Engine.hpp"

#if defined(_WIN32)
	#if defined(_DEBUG) || defined(DEBUG) || defined(_CONSOLE)
		// Debug Windows
		int main()
	#else
		// Release Windows
		#include <windows.h>
		int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
	#endif
#else
	// Debug && Release Unix
	int main()
#endif
{
	Engine game("Escape of the Fox");
	game.run();
	return 0;
}