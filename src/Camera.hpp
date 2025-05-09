#pragma once

#include <SDL3/SDL.h>

#include "GameObject.hpp"

class Camera : public GameObject {
public:
	Camera(float width, float height);
	// Changes current position to be centered on target
	void follow(const SDL_FRect& target);
	// Changes current position to be centered on target with boundaries mapWidth and mapHeight
	void follow(const SDL_FRect& target, float mapWidth, float mapHeight);
};