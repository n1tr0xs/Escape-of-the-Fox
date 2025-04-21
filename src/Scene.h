#pragma once

#include <SDL3/SDL.h>

#include "ResourceManager.h"

enum class SceneResult {
	None,
	StartGame,
	Quit,
	Victory,
};

class Scene {
public:
	Scene() = default;
	virtual void handleEvent(const SDL_Event& event) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(SDL_Renderer* renderer) = 0;
	virtual SceneResult getResult() const { return SceneResult::None; }
	virtual ~Scene() = default;
};
