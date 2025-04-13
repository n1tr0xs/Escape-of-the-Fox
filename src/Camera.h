#pragma once

#include <SDL3/SDL.h>

class Camera {
public:
	SDL_FRect view;
	
	Camera(float width, float height);
	void follow(const SDL_FRect& target, float mapWidth, float mapHeight);
};