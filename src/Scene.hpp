#pragma once

#include <SDL3/SDL.h>

#include "ResourceManager.hpp"

enum class SceneResult {
	None,
	StartGame,
	Quit,
	Victory,
	GameOver,
	QuitToMainMenu,
	Continue,
};

class Scene {
public:
	Scene() = default;
	virtual ~Scene() = default;
	// Handles events and input
	virtual void handleEvent(const SDL_Event& event) = 0;
	// Updates scene
	virtual void update(const Uint64 deltaTime) = 0;
	// Renders scene
	virtual void render(SDL_Renderer* renderer) = 0;
	// Resets scene result
	virtual void resetResult() { m_sceneResult = SceneResult::None; };
	// Getters
	virtual SceneResult getResult() const { return m_sceneResult; };
protected:
	SceneResult m_sceneResult = SceneResult::None;
};
