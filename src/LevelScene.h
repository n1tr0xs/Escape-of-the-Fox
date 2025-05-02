#pragma once

#include "Level.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "MenuScene.h"
#include <vector>

class LevelScene : public Scene {
public:
	LevelScene(ResourceManager* resourceManager, int levelNum);
	void handleEvent(const SDL_Event& event) override;
	void update(Uint64 deltaTime) override;
	void render(SDL_Renderer* renderer) override;
private:
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
