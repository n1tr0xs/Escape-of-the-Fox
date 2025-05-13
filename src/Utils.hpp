#pragma once

#include <SDL3/SDL.h>
#include <string>

namespace utils {
	[[noreturn]]
	void SDL_Fail(const std::string& message, int statusCode = -1);

	bool isCollide(SDL_FRect rect1, SDL_FRect rect2);
}