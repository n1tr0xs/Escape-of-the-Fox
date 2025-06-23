#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <random>


namespace utils {

	[[noreturn]]
	void SDL_Fail(const std::string& message, int statusCode = -1);

	bool isCollide(SDL_FRect rect1, SDL_FRect rect2);
	[[nodiscard]]
	float getRandom(const float low = 0.0f, const float high = 1.0f);
}