#pragma once

#include <vector>

#include "Level.hpp"
#include "Player.hpp"
#include "ResourceManager.hpp"
#include "Scene.hpp"
#include "MenuScene.hpp"

class LevelScene : public Scene {
public:
	LevelScene(ResourceManager* resourceManager, int levelNum);
	void handleEvent(const SDL_Event& event) override;
	void update(const Uint64 deltaTime) override;
	void render(SDL_Renderer* renderer) override;
private:

	void resolveHorizontalCollision(Entity* entity, Uint64 deltaTime);

	std::unique_ptr<MenuScene> createPauseScene();

	ResourceManager* m_resourceManager;

	std::unique_ptr<Level> m_level;
	std::unique_ptr<Player> m_player;
	std::unique_ptr<MenuScene> m_pauseScene;
	std::unique_ptr<Camera> m_camera;

	bool m_isPaused = false;
	bool m_levelCompleted = false;
	bool m_playerDead = false;
};
