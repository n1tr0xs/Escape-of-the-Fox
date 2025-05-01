#pragma once

#include "ResourceManager.h"
#include <SDL3/SDL.h>

enum class SceneResult {
	None,
	StartGame,
	Quit,
	Victory,
	GameOver,
};

class Scene {
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void handleEvent(const SDL_Event& event) = 0;
	virtual void update(Uint64 deltaTime) = 0;
	virtual void render(SDL_Renderer* renderer) = 0;
	// Getters
	virtual SceneResult getResult() const { return m_sceneResult; };
protected:
	SceneResult m_sceneResult = SceneResult::None;
};
