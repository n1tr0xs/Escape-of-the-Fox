#pragma once

#include <vector>

#include "Scene.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "ResourceManager.hpp"
#include "MenuScene.hpp"

class LevelScene : public Scene {
public:
	LevelScene(ResourceManager* resourceManager, int levelNum);
	void handleEvent(const SDL_Event& event) override;
	void update(const Uint64 deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	// Calls other collision resolvers for entity
	void resolveCollision(Entity* entity, Uint64 deltaTime);
	// Resolves horizontal collision for entity
	void resolveHorizontalCollision(Entity* entity, Uint64 deltaTime);
	// Resolves vertical collision for entity
	void resolveVerticalCollision(Entity* entity, Uint64 deltaTime);
private:
	// Creates player
	std::unique_ptr<Player> createPlayer();
	// Creates pause scene
	std::unique_ptr<MenuScene> createPauseScene();
	// Create camera
	std::unique_ptr<Camera> createCamera();

	ResourceManager* m_resourceManager;

	std::unique_ptr<Level> m_level;
	std::unique_ptr<Player> m_player;
	std::unique_ptr<MenuScene> m_pauseScene;
	std::unique_ptr<Camera> m_camera;

	bool m_isPaused{ false };
	bool m_levelCompleted{ false };
	bool m_playerDead{ false };
};
