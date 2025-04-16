#pragma once

#include <SDL3/SDL.h>

#include "ResourceManager.h"

class Scene {
public:
	Scene() = default;
	virtual void update(float deltaTime) = 0;
	virtual void render(SDL_Renderer* renderer) = 0;
	virtual ~Scene() = default;
};
