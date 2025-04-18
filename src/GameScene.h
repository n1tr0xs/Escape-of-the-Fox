#pragma once

#include "ResourceManager.h"
#include "Level.h"
#include "Player.h"
#include "Scene.h"
#include <vector>

class GameScene : public Scene {
public:
	GameScene(ResourceManager* resourceManager);
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

private:
	ResourceManager* m_resourceManager;

	std::unique_ptr<Level> m_level;
	std::unique_ptr<Player> m_player;
	std::unique_ptr<Camera> m_camera;

	bool m_levelCompleted = false;
};
