#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>

#include "Utils.hpp"

namespace utils {
	[[noreturn]]
	void SDL_Fail(const std::string& message, int statusCode) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s %s", message.c_str(), SDL_GetError());

		// CleanUp
		Mix_Quit();
		TTF_Quit();
		SDL_Quit();

		// Exit
		exit(statusCode);
	}

	bool isCollide(SDL_FRect rect1, SDL_FRect rect2) {
		// AABB collision
		return !(rect2.x + rect2.w < rect1.x ||
			rect2.x > rect1.x + rect1.w ||
			rect2.y + rect2.h < rect1.y ||
			rect2.y > rect1.y + rect1.h);
	}

	float getRandom(const float low, const float high) {
		return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)));
	}

}