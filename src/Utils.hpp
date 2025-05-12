#pragma once

#include <string>

namespace utils {
	[[noreturn]]
	void SDL_Fail(const std::string& message, int statusCode = -1);
}