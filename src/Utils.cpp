#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>

#include "Utils.hpp"

namespace utils {

	void SDL_Fail(const std::string& message) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s %s", message.c_str(), SDL_GetError());

		// CleanUp
		Mix_CloseAudio();
		Mix_Quit();
		TTF_Quit();
		SDL_Quit();

		// Exit
		exit(1);
	}
	
}