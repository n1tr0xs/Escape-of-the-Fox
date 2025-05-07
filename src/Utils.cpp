#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Utils.hpp"

void SDL_Fail(const std::string& message) {
	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s %s", message.c_str(), SDL_GetError());
	
	TTF_Quit();
	SDL_Quit();
	exit(1);
}