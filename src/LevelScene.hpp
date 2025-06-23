#pragma once

#include <vector>
#include <cmath>

#include "Scene.hpp"
#include "Level.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Utils.hpp"
#include "ResourceManager.hpp"
#include "MenuScene.hpp"
#include "PauseMenu.hpp"

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
	void resolveEnemyPlayerCollision(Entity* player, Entity* entity);
private:
	// Creates level
	std::unique_ptr<Level> createLevel(int levelNum);
	// Creates camera
	std::unique_ptr<Camera> createCamera();
	// Creates player
	std::unique_ptr<Player> createPlayer();
	// Creates simple enemy
	std::unique_ptr<Entity> createSimpleEnemy();
	// Creates Bee Swarm
	std::unique_ptr<Entity> createBeeSwarm();
	// Creates Cock
	std::unique_ptr<Entity> createCock();
	// Creates Mushroom enemy
	std::unique_ptr<Entity> createMushroom();
	// Creates pause scene
	std::unique_ptr<PauseMenu> createPauseScene();
	
	ResourceManager* m_resourceManager;

	std::unique_ptr<Level> m_level;
	std::unique_ptr<Camera> m_camera;
	std::unique_ptr<Player> m_player;
	std::vector<std::unique_ptr<Entity>> m_enemies;
	std::unique_ptr<PauseMenu> m_pauseScene;

	bool m_isPaused{ false };
	bool m_levelCompleted{ false };
	bool m_playerDead{ false };
};
